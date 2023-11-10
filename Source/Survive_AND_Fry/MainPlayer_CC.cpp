#include "MainPlayer_CC.h"
#include "Engine/World.h"
#include "Components/ArrowComponent.h"
#include "Components/MeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "ItemDesk.h"
#include "Item.h"

AMainPlayer_CC::AMainPlayer_CC()
{
	PrimaryActorTick.bCanEverTick = true;

	HoldingLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Holding Location"));
	HoldingLocation->SetupAttachment(RootComponent);
}

void AMainPlayer_CC::BeginPlay()
{
	Super::BeginPlay();
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
	PlayerInputComponent->BindAction(TEXT("Chop"), EInputEvent::IE_Pressed, this, &AMainPlayer_CC::StartChopping);
	PlayerInputComponent->BindAction(TEXT("Chop"), EInputEvent::IE_Released, this, &AMainPlayer_CC::StopChopping);
	PlayerInputComponent->BindAction(TEXT("RemoveItem"), EInputEvent::IE_Pressed, this, &AMainPlayer_CC::RemoveItem);

	FRotator RotationFromMovement = GetVelocity().Rotation();
	SetActorRotation(RotationFromMovement);
}

void AMainPlayer_CC::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AMainPlayer_CC::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AMainPlayer_CC::GrabORRelease()
{
	if (TraceObject())
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			AItemDesk* ItemDeskReference = Cast<AItemDesk>(HitActor);
			if (ItemDeskReference != nullptr)
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

}

void AMainPlayer_CC::StopChopping()
{

}

void AMainPlayer_CC::RemoveItem()
{
	if (HoldingItem != nullptr)
	{
		HoldingItem->Destroy();
		HoldingItem = nullptr;
	}
	else
		return;
}

bool AMainPlayer_CC::TraceObject()
{
	UArrowComponent* PlayerTracePointer = GetArrowComponent();
	PlayerTracePointer->GetComponentLocation();

	UMeshComponent* CharacterMesh = GetMesh();

	if (PlayerTracePointer != nullptr && CharacterMesh != nullptr && TraceMaterial != nullptr && NormalMaterial != nullptr)
	{
		FVector Start = PlayerTracePointer->GetComponentLocation();
		FVector End = PlayerTracePointer->GetComponentLocation() + PlayerTracePointer->GetForwardVector() * TraceDistance;

		bool IsHit = GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(SphereSize));

		if (IsHit == true)
		{
			CharacterMesh->SetMaterial(0, TraceMaterial);
			
			return true;
		}
		else
		{
			CharacterMesh->SetMaterial(0, NormalMaterial);
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
				ItemDesk->ItemOnDesk = nullptr;

				ItemDesk->ItemOnDesk = GetWorld()->SpawnActor<AActor>(ItemDesk->ItemOnDeskReference,
					ItemDesk->ItemLocation->GetComponentLocation(),
					ItemDesk->ItemLocation->GetComponentRotation());
			}
		}
		else
		{
			if (HoldingItem != nullptr)
			{
				HoldingItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				HoldingItem->AttachToComponent(ItemDesk->ItemLocation, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				ItemDesk->ItemOnDesk = HoldingItem;
				HoldingItem = nullptr;
			}
		}
	}
}
