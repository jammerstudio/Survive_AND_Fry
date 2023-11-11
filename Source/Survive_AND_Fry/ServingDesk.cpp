#include "ServingDesk.h"
#include "Bread.h"

AServingDesk::AServingDesk()
{
	PrimaryActorTick.bCanEverTick = true;

	ServingBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ServingBoard"));
	ServingBoard->SetupAttachment(DefaultSceneRoot);
}

void AServingDesk::BeginPlay()
{
	Super::BeginPlay();
}

void AServingDesk::ServeItem()
{
	Bread = Cast<ABread>(ItemOnDesk);
	if (Bread != nullptr)
	{
		if (Bread->HasVegetable == true && Bread->HasAntiDote == true)
		{
			ItemOnDesk = nullptr;
			UE_LOG(LogTemp, Display, TEXT("Food Served!"));
			Bread->Destroy();
		}
	}
}
