#include "Vegetable.h"

AVegetable::AVegetable()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootSceneComponent->SetupAttachment(RootComponent);
}

void AVegetable::BeginPlay()
{
	Super::BeginPlay();
}
