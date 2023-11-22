#include "Bread.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer_CC.h"
#include "ChoppedTomato.h"
#include "ChoppedLettuce.h"
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
	
	GetWorldTimerManager().SetTimer(AntiDoteTimerHandle, this, &ABread::DisableEffects, 1.f, true);
	GetWorldTimerManager().PauseTimer(AntiDoteTimerHandle);
}

void ABread::CombineItems(AMainPlayer_CC* MainPlayer, AActor* SecondItem)
{
	Super::CombineItems(MainPlayer, SecondItem);

	ChoppedTomato = Cast<AChoppedTomato>(SecondItem);
	
		if (HasTomato == true)
		{
			UE_LOG(LogTemp, Display, TEXT("Bread Has Tomato Already"));
		}
		else
		{
			if (ChoppedTomato != nullptr)
			{
				ChoppedTomato->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				MainPlayer->HoldingItem = nullptr;
				MainPlayer->IsHolding = false;
				HasTomato = true;
				ChoppedTomato->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				ChoppedTomato->Destroy();
				if (VegetableMesh != nullptr)
				{
					VegetableMesh->SetVisibility(true, true);
				}
			}
		}

	ChoppedLettuce = Cast<AChoppedLettuce>(SecondItem);
		if (HasLettuce == true)
		{
			UE_LOG(LogTemp, Display, TEXT("Bread Has Tomato Already"));
		}
		else
		{
			if (ChoppedLettuce != nullptr)
			{
				ChoppedLettuce->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				MainPlayer->HoldingItem = nullptr;
				MainPlayer->IsHolding = false;
				HasLettuce = true;
				ChoppedLettuce->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				ChoppedLettuce->Destroy();
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
			if (AntiDote != nullptr)
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
						GetWorldTimerManager().UnPauseTimer(AntiDoteTimerHandle);
					}
					AntiDoteMesh->SetVisibility(true, true);
				}
			}
		}
}

void ABread::DisableEffects()
{
	TimeOut = TimeOut + 1.f;
	if (TimeOut <= 3.f)
	{
		if (AntiDoteEffect != nullptr)
		{
			AntiDoteEffect->Deactivate();
			GetWorldTimerManager().ClearTimer(AntiDoteTimerHandle);
		}
	}
}
