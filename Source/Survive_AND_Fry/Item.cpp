#include "Item.h"
#include "Blueprint/UserWidget.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootSceneComponent);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AItem::CombineItems(class AMainPlayer_CC* MainPlayer, class AActor* SecondItem)
{
	UE_LOG(LogTemp, Display, TEXT("Time To Combine Items"));
}

void AItem::ChopItem(float Delta)
{
	
}