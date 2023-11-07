#include "ItemDesk.h"
#include "Components/StaticMeshComponent.h"

AItemDesk::AItemDesk()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(RootComponent);
	
	Desk = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Desk"));
	Desk->SetupAttachment(DefaultSceneRoot);

	ItemLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Item Location"));
	ItemLocation->SetupAttachment(DefaultSceneRoot);
}

void AItemDesk::BeginPlay()
{
	Super::BeginPlay();
}

void AItemDesk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

