#include "Bread.h"
#include "Item.h"
#include "Vegetable.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer_CC.h"

ABread::ABread()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootSceneComponent);

	BreadTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BreadTop"));
	BreadTop->SetupAttachment(RootSceneComponent);

	BreadBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BreadBottom"));
	BreadBottom->SetupAttachment(RootSceneComponent);

	VegetableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Vegetable"));
	VegetableMesh->SetupAttachment(RootSceneComponent);
}

void ABread::BeginPlay()
{
	Super::BeginPlay();

	if (VegetableMesh != nullptr)
	{
		VegetableMesh->SetVisibility(false);
	}
}

void ABread::CombineItems(AMainPlayer_CC* MainPlayer, AActor* SecondItem)
{
	Super::CombineItems(MainPlayer, SecondItem);

	Vegetable = Cast<AVegetable>(SecondItem);
	if (HasVegetable == true)
	{
		UE_LOG(LogTemp, Display, TEXT("Bread Has Vegetable Already"));
	}
	else
	{
		if (Vegetable != nullptr)
		{
			Vegetable->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			MainPlayer->HoldingItem = nullptr;
			HasVegetable = true;
			Vegetable->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Vegetable->Destroy();
			if (VegetableMesh != nullptr)
			{
				VegetableMesh->SetVisibility(true);
			}
		}
	}
}