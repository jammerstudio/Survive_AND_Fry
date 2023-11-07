#include "MainPlayer_PC.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void AMainPlayer_PC::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* HUDWidget = CreateWidget(this, HUDWidgetClass);

	if (HUDWidget != nullptr)
	{
		HUDWidget->AddToViewport();
	}
	GetWorldTimerManager().SetTimer(WaveTimer, this, &AMainPlayer_PC::WaveTimerDelegate, 1.f, true);

	AActor* CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), WorldCameraClass);

	if (CameraActor != nullptr)
	{
		SetViewTargetWithBlend(CameraActor, 2.f, EViewTargetBlendFunction::VTBlend_Linear);
	}
}
void AMainPlayer_PC::WaveTimerDelegate()
{
	TimeLeft -= 1;
}