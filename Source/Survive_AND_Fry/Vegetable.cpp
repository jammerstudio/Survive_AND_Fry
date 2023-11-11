#include "Vegetable.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer_CC.h"
#include "Components/WidgetComponent.h"
#include "ChoppedVegetable.h"
#include "ChoppingDesk.h"

AVegetable::AVegetable()
{
	PrimaryActorTick.bCanEverTick = true;

	ProgressWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ProgressWidgetComponent"));
	ProgressWidgetComponent->SetupAttachment(RootSceneComponent);
}

void AVegetable::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PlayerCharacter != nullptr)
	{
		MainPlayer = Cast<AMainPlayer_CC>(PlayerCharacter);
	}

	if (ProgressWidgetComponent != nullptr)
	{
		ProgressWidgetComponent->SetVisibility(false);
	}
}

void AVegetable::ChopItem(float Delta)
{
	Super::ChopItem(Delta);
	if (Progress < 1.0f)
	{
		Progress = Progress + Delta * ChoppingSpeed;
		
		if (MainPlayer != nullptr && ProgressWidgetComponent != nullptr)
		{
			ProgressWidgetComponent->SetWorldLocation(RootSceneComponent->GetComponentLocation());
			ProgressWidgetComponent->SetVisibility(true);
			MainPlayer->Progress = Progress;
		}
		UE_LOG(LogTemp, Display, TEXT("Progres Is : %f"), Progress);
	}
	else
	{
		if (ProgressWidgetComponent != nullptr)
		{
			ProgressWidgetComponent->SetVisibility(false);
		}
		if (MainPlayer != nullptr)
		{
			MainPlayer->HoldingItem = nullptr;
		}
		AActor* ChoppingDeskPointer = GetAttachParentActor();
		if (ChoppingDeskPointer != nullptr)
		{
			ChoppingDesk = Cast<AChoppingDesk>(ChoppingDeskPointer);
			if (ChoppingDesk != nullptr && ChoppingDesk->SpawnChoppedActor == true)
			{
				ChoppingDesk->ItemOnDesk = GetWorld()->SpawnActor<AActor>(ChoppedItemReference, GetActorTransform());
			}
		}
		Destroy();
	}
}