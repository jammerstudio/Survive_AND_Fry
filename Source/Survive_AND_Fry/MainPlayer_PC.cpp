#include "MainPlayer_PC.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void AMainPlayer_PC::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* HUDWidget = CreateWidget(this, HUDWidgetClass);

	if (HUDWidget != nullptr)
	{
		HUDWidget->AddToViewport();
	}
	GetWorldTimerManager().SetTimer(WaveTimer, this, &AMainPlayer_PC::WaveTimerDelegate, 1.f, true);
}

void AMainPlayer_PC::WaveTimerDelegate()
{
	TimeLeft -= 1;
}