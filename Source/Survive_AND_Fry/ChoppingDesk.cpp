#include "ChoppingDesk.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer_CC.h"

AChoppingDesk::AChoppingDesk()
{
	SetRootComponent(AItemDesk::DefaultSceneRoot);

	ChoppingBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chopping Board"));
	ChoppingBoard->SetupAttachment(AItemDesk::DefaultSceneRoot);

	Knife = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Knife"));
	Knife->SetupAttachment(AItemDesk::DefaultSceneRoot);
}