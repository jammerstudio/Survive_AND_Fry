#include "Bread.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer_CC.h"
#include "ChoppedVegetable.h"
#include "AntiDote.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ABread::ABread()
{
	PrimaryActorTick.bCanEverTick = true;

	BreadTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BreadTop"));
	BreadTop->SetupAttachment(RootSceneComponent);

	BreadBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BreadBottom"));
	BreadBottom->SetupAttachment(RootSceneComponent);

	VegetableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Vegetable"));
	VegetableMesh->SetupAttachment(RootSceneComponent);

	AntiDoteMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AntiDote"));
	AntiDoteMesh->SetupAttachment(RootSceneComponent);

	AntiDoteEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("AntiDoteEffect"));
	AntiDoteEffect->SetupAttachment(RootSceneComponent);
}

void ABread::BeginPlay()
{
	Super::BeginPlay();

	if (VegetableMesh != nullptr)
	{
		VegetableMesh->SetVisibility(false, true);
	}
	if (AntiDoteMesh != nullptr)
	{
		AntiDoteMesh->SetVisibility(false, true);
	}
	if (AntiDoteTimerManager != nullptr)
	{
		AntiDoteTimerManager->SetTimer(AntiDoteTimerHandle, this, &ABread::DisableEffects, 1.f, false);
		AntiDoteTimerManager->PauseTimer(AntiDoteTimerHandle);
	}
}

void ABread::CombineItems(AMainPlayer_CC* MainPlayer, AActor* SecondItem)
{
	Super::CombineItems(MainPlayer, SecondItem);

	ChoppedVegetable = Cast<AChoppedVegetable>(SecondItem);
	if (HasVegetable == true)
	{
		UE_LOG(LogTemp, Display, TEXT("Bread Has Vegetable Already"));
	}
	else
	{
		if (ChoppedVegetable != nullptr)
		{
			ChoppedVegetable->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			MainPlayer->HoldingItem = nullptr;
			MainPlayer->IsHolding = false;
			HasVegetable = true;
			ChoppedVegetable->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			ChoppedVegetable->Destroy();
			if (VegetableMesh != nullptr)
			{
				VegetableMesh->SetVisibility(true, true);
			}
		}
	}
	AntiDote = Cast<AAntiDote>(SecondItem);
	if (HasAntiDote == true)
	{
		UE_LOG(LogTemp, Display, TEXT("Bread Has AntiDote Already"));
	}
	else
	{
		if (AntiDote != nullptr && HasVegetable == true)
		{
			AntiDote->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			MainPlayer->HoldingItem = nullptr;
			MainPlayer->IsHolding = false;
			HasAntiDote = true;
			AntiDote->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			AntiDote->Destroy();
			if (AntiDoteMesh != nullptr)
			{
				if (AntiDoteEffect != nullptr)
				{
					AntiDoteEffect->Activate();
					AntiDoteTimerManager->UnPauseTimer(AntiDoteTimerHandle);
				}
				AntiDoteMesh->SetVisibility(true, true);
			}
		}
	}
}

void ABread::DisableEffects()
{
	float TimeOut = 0.f;
	TimeOut = TimeOut + 1.f;
	if (TimeOut <= 3.f)
	{
		if (AntiDoteTimerManager != nullptr && AntiDoteEffect != nullptr)
		{
			AntiDoteEffect->Deactivate();
			AntiDoteTimerManager->ClearTimer(AntiDoteTimerHandle);
		}
	}
}
