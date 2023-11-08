#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
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
