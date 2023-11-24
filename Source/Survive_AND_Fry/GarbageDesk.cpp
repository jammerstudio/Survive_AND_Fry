#include "GarbageDesk.h"
#include "TimerManager.h"

AGarbageDesk::AGarbageDesk()
{
	SetRootComponent(DefaultSceneRoot);
}

void AGarbageDesk::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ActorRemoverTimer, this, &AGarbageDesk::DeleteActor, 3.f, true);
}

void AGarbageDesk::DeleteActor()
{
	if (ItemOnDesk != nullptr)
	{
		ItemOnDesk->Destroy();
		ItemOnDesk = nullptr;
	}
}