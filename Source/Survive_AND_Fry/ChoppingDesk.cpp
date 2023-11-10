#include "ChoppingDesk.h"

AChoppingDesk::AChoppingDesk()
{
	SetRootComponent(AItemDesk::DefaultSceneRoot);

	ChoppingBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chopping Board"));
	ChoppingBoard->SetupAttachment(AItemDesk::DefaultSceneRoot);
}
