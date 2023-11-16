#include "MainPlayer_PC.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainPlayer_CC.h"

void AMainPlayer_PC::SetTaskDescription(int32 TaskNumber)
{
	if (TaskNumber == 1)
	{
		TaskDescription = ("TASK DESCRIPTION\nSingle Scale Sandwich");
	}
	if (TaskNumber == 2)
	{
		TaskDescription = ("TASK DESCRIPTION\nDouble Scale Sandwich");
	}
	if (TaskNumber == 3)
	{
		TaskDescription = ("TASK DESCRIPTION\nTriple Scale Sandwich");
	}
}

void AMainPlayer_PC::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(false);

	UUserWidget* HUDWidget = CreateWidget(this, HUDWidgetClass);

	if (HUDWidget != nullptr)
	{
		HUDWidget->AddToViewport();
	}
	GetWorldTimerManager().SetTimer(WaveTimer, this, &AMainPlayer_PC::WaveTimerDelegate, 1.f, true);

	AActor* CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), WorldCameraClass);

	if (CameraActor != nullptr)
	{
		SetViewTargetWithBlend(CameraActor, 3.f, EViewTargetBlendFunction::VTBlend_Linear);
	}
}
void AMainPlayer_PC::WaveTimerDelegate()
{
	TimeLeft -= 1;

	if (TimeLeft <= 0)
	{
		DisableInput(this);
		CreateGameOverWidget();
	}
}

void AMainPlayer_PC::CreateGameOverWidget()
{
	GameOverWidget = CreateWidget(this, GameOverWidgetClass);

	if (GameOverWidget != nullptr)
	{
		SetShowMouseCursor(true);
		GameOverWidget->AddToViewport();
	}
}

void AMainPlayer_PC::RestartMainLevel()
{
	UGameplayStatics::OpenLevel(this, "Main");
}

void AMainPlayer_PC::QuitToMainMenu()
{
	if (GameOverWidget != nullptr)
	{
		GameOverWidget->RemoveFromParent();
		UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, true);
	}
}