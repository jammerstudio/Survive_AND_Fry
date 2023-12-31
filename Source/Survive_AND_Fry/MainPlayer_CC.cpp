#include "MainPlayer_CC.h"
#include "Engine/World.h"
#include "Components/ArrowComponent.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "ItemDesk.h"
#include "Item.h"
#include "ChoppingDesk.h"
#include "ServingDesk.h"
#include "MainPlayer_PC.h"
#include "Math/UnrealMathUtility.h"
#include "Bread.h"
#include "TimerManager.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"

AMainPlayer_CC::AMainPlayer_CC()
{
	PrimaryActorTick.bCanEverTick = true;

	Knife = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Knife"));
	Knife->SetupAttachment(GetMesh());

	HoldingLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Holding Location"));
	HoldingLocation->SetupAttachment(RootComponent);

	PlayerTracePointer = CreateDefaultSubobject<UArrowComponent>(TEXT("TracePointer"));
	PlayerTracePointer->SetupAttachment(GetMesh());
}

void AMainPlayer_CC::BeginPlay()
{
	Super::BeginPlay();

	if (Knife != nullptr)
	{
		Knife->SetVisibility(false);
		Knife->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Knife"));
	}

	SetTaskDescription(0.f);

	GetWorldTimerManager().SetTimer(ChoppingHandle, this, &AMainPlayer_CC::StartChopping, 0.3, true);
}

void AMainPlayer_CC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceObject();
}

void AMainPlayer_CC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainPlayer_CC::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainPlayer_CC::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Grab/Release"), EInputEvent::IE_Pressed, this, &AMainPlayer_CC::GrabORRelease);
	PlayerInputComponent->BindAction(TEXT("ConfirmOrder"), EInputEvent::IE_Pressed, this, &AMainPlayer_CC::ProcessServing);
	PlayerInputComponent->BindAction(TEXT("ScaleItem"), EInputEvent::IE_Pressed, this, &AMainPlayer_CC::EnlargeItem);

	FRotator MovementRotation = GetVelocity().Rotation();
	SetActorRotation(MovementRotation);
}

void AMainPlayer_CC::MoveForward(float AxisValue)
{
	AddMovementInput(FVector(1, 0, 0) * GetWorld()->DeltaTimeSeconds * MoveSpeed, AxisValue);
}

void AMainPlayer_CC::MoveRight(float AxisValue)
{
	AddMovementInput(FVector(0, 1, 0) *GetWorld()->DeltaTimeSeconds * MoveSpeed, AxisValue);
}

void AMainPlayer_CC::GrabORRelease()
{
	if (TraceObject())
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			AItemDesk* ItemDeskReference = Cast<AItemDesk>(HitActor);
			if (ItemDeskReference != nullptr && IsChopping == false)
			{
				DeskFunctions(ItemDeskReference);
			}
		}
	}
	else
	{
		return;
	}
}

void AMainPlayer_CC::StartChopping()
{
	if (TraceObject())
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			ChoppingDesk = Cast<AChoppingDesk>(HitActor);
			if (ChoppingDesk != nullptr)
			{
				ProcessChopping();
			}
		}
	}
}

bool AMainPlayer_CC::TraceObject()
{
	UMeshComponent* CharacterMesh = GetMesh();

	if (PlayerTracePointer != nullptr && CharacterMesh != nullptr && TraceMaterial != nullptr && NormalMaterial != nullptr)
	{
		FVector Start = PlayerTracePointer->GetComponentLocation();
		FVector End = PlayerTracePointer->GetComponentLocation() + PlayerTracePointer->GetForwardVector() * TraceDistance;

		IsHit = GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(SphereSize));

		DrawDebugSphere(GetWorld(), End, SphereSize, 12, FColor::Red, false);

		if (IsHit == true)
		{
			ItemDesk = Cast<AItemDesk>(Hit.GetActor());
			if (ItemDesk != nullptr)
			{
				ItemDesk->Desk->SetRenderCustomDepth(true);
			}
			return true;
		}
		else
		{
			if (ItemDesk != nullptr)
			{
				ItemDesk->Desk->SetRenderCustomDepth(false);
			}
			return false;
		}
	}
	else { return false; };
}

void AMainPlayer_CC::DeskFunctions(AActor* Desk)
{
	ItemDesk = Cast<AItemDesk>(Desk);
	if (ItemDesk != nullptr)
	{
		if (ItemDesk->ItemOnDesk != nullptr)
		{
			if (HoldingItem != nullptr)
			{
				//If There Is A Item On The Player & On Another Desk Then This Part Of The Logic Runs
				AItem* Item = Cast<AItem>(ItemDesk->ItemOnDesk);
				if (Item != nullptr)
				{
					Item->CombineItems(this, HoldingItem);
				}
				UE_LOG(LogTemp, Display, TEXT("Already Equipped With An Item"));
			}
			else
			{
				ItemDesk->ItemOnDesk->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				HoldingItem = ItemDesk->ItemOnDesk;
				HoldingItem->AttachToComponent(HoldingLocation, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				IsHolding = true;

				if (ItemDesk->NeedToRespawn == true)
				{
					ItemDesk->ItemOnDesk = GetWorld()->SpawnActor<AActor>(ItemDesk->ItemOnDeskReference,
						ItemDesk->ItemLocation->GetComponentLocation(),
						ItemDesk->ItemLocation->GetComponentRotation());
				}
				else
				{
					ItemDesk->ItemOnDesk = nullptr;
				}
			}
		}
		else
		{
			if (HoldingItem != nullptr)
			{
				HoldingItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				HoldingItem->AttachToComponent(ItemDesk->ItemLocation, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				ItemDesk->ItemOnDesk = HoldingItem; 
				if (ItemDesk == ServingDesk && (ServingDesk->Bread = Cast<ABread>(ItemDesk->ItemOnDesk)))
				{
					SetTaskDescription(1.f);
					if (ServingDesk != nullptr)
					{
						ServingDesk->ScaleValue = 1.f;
						ServingDesk->EnlargeItem(1.f);
					}
				}
				HoldingItem = nullptr;
				IsHolding = false;
			}
		}
	}
	else
	{
		return;
	}
}

void AMainPlayer_CC::ProcessChopping()
{
	if (ChoppingDesk != nullptr)
	{
		AItem* ItemToBeChopped = Cast<AItem>(ChoppingDesk->ItemOnDesk);
		if (ItemToBeChopped != nullptr)
		{
			APlayerController* MainPlayer_PC_Reference = UGameplayStatics::GetPlayerController(this, 0);
			if (MainPlayer_PC_Reference != nullptr)
			{
				AMainPlayer_PC* MainPlayer_PC = Cast<AMainPlayer_PC>(MainPlayer_PC_Reference);
				if (MainPlayer_PC != nullptr)
				{
					if (ChoppingSound != nullptr && ItemToBeChopped->CanBeChopped == true && MainPlayer_PC->IsInputKeyDown(EKeys::LeftControl) && Knife != nullptr && ChoppingDesk->Knife != nullptr)
					{

						UAudioComponent* ChopSoundReference = UGameplayStatics::SpawnSound2D(GetWorld(), ChoppingSound);
						if (ChopSoundReference != nullptr)
						{
							if (ChopSoundReference->IsPlaying() == false)
							{
								ChopSoundReference->Play();
							}
						}
						ChoppingDesk->Knife->SetVisibility(false);
						Knife->SetVisibility(true);
						IsChopping = true;
						ItemToBeChopped->ChopItem(GetWorld()->DeltaTimeSeconds * 5.f);
					}
					else
					{
						if (Knife != nullptr && ChoppingDesk->Knife != nullptr)
						{
							Knife->SetVisibility(false);
							ChoppingDesk->Knife->SetVisibility(true);
						}
						IsChopping = false;
					}
				}
			}
		}
	}
	else return;
}

void AMainPlayer_CC::ProcessServing()
{
	if (TraceObject())
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			ServingDesk = Cast<AServingDesk>(HitActor);
			if (ServingDesk != nullptr)
			{
				ServingDesk->ServeItem();
			}
		}
	}
}

void AMainPlayer_CC::EnlargeItem()
{
	if (TraceObject())
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			ServingDesk = Cast<AServingDesk>(HitActor);
			if (ServingDesk != nullptr)
			{
				if (ServingDesk->Bread = Cast<ABread>(ServingDesk->ItemOnDesk))
				{
					SetTaskDescription(1.f);
					APlayerController* MainPlayer_PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
					if (MainPlayer_PC != nullptr)
					{
						if (MainPlayer_PC->IsInputKeyDown(EKeys::Left))
						{
							ServingDesk->ScaleValue = FMath::Clamp(ServingDesk->ScaleValue - 1.f, 1, 3);
							SetTaskDescription(ServingDesk->ScaleValue);
							ServingDesk->EnlargeItem(ServingDesk->ScaleValue);
						}
						if (MainPlayer_PC->IsInputKeyDown(EKeys::Right))
						{
							ServingDesk->ScaleValue = FMath::Clamp(ServingDesk->ScaleValue + 1.f, 1, 3);
							SetTaskDescription(ServingDesk->ScaleValue);
							ServingDesk->EnlargeItem(ServingDesk->ScaleValue);
						}
						if (MainPlayer_PC->IsInputKeyDown(EKeys::LeftShift))
						{
							ServingDesk->ServeItem();
						}
					}
				}
				else
				{
					SetTaskDescription(0.f);
				}
			}
		}
	}
}

void AMainPlayer_CC::SetTaskDescription(float CurrentScale)
{
	if (CurrentScale == 0.f)
	{
		CurrentScaleDescription = ("CURRENT SCALE\n");
	}
	if (CurrentScale == 1.f)
	{
		CurrentScaleDescription = ("CURRENT SCALE\n1x");
	}
	if (CurrentScale == 2.f)
	{
		CurrentScaleDescription = ("CURRENT SCALE\n2x");
	}
	if (CurrentScale == 3.f)
	{
		CurrentScaleDescription = ("CURRENT SCALE\n3x");
	}
}
