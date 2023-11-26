#include "GarbageDesk.h"
#include "Kismet/GameplayStatics.h"
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
	if (ItemOnDesk != nullptr && GarbageSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), GarbageSound);
		ItemOnDesk->Destroy();
		ItemOnDesk = nullptr;
	}
}