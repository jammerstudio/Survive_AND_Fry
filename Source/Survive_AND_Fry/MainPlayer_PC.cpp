#include "MainPlayer_PC.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainPlayer_CC.h"
#include "Components/AudioComponent.h"

void AMainPlayer_PC::SetTaskDescription(int32 TaskNumber, int32 IngredientNumber)
{
	if (TaskNumber == 1)
	{
		if (IngredientNumber == 1)
		{
			TaskDescription = ("TASK\n1x Tomato Sandwich");
		}
		if (IngredientNumber == 2)
		{
			TaskDescription = ("TASK\n1x Lettuce Sandwich");
		}
	}
	if (TaskNumber == 2)
	{
		if (IngredientNumber == 1)
		{
			TaskDescription = ("TASK\n2x Tomato Sandwich");
		}
		if (IngredientNumber == 2)
		{
			TaskDescription = ("TASK\n2x Lettuce Sandwich");
		}
	}
	if (TaskNumber == 3)
	{
		if (IngredientNumber == 1)
		{
			TaskDescription = ("TASK\n3x Tomato Sandwich");
		}
		if (IngredientNumber == 2)
		{
			TaskDescription = ("TASK\n3x Lettuce Sandwich");
		}
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

	if (TimeLeft <= 0 && ZombiesSaved > 0)
	{
		DisableInput(this);
		CreateGameOverWidget();
		GetWorldTimerManager().PauseTimer(WaveTimer);
	}
	else if (TimeLeft > 0 && ZombiesSaved <= 0)
	{
		DisableInput(this);
		CreateGameWinWidget();
		GetWorldTimerManager().PauseTimer(WaveTimer);
	}
}

void AMainPlayer_PC::CreateGameWinWidget()
{
	GameWinWidget = CreateWidget(this, GameWinWidgetClass);

	if (GameWinWidget != nullptr)
	{
		SetShowMouseCursor(true);
		GameWinWidget->AddToViewport();
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