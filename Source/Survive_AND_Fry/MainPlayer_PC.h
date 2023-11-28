#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayer_PC.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AMainPlayer_PC : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TimeLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int ZombiesSaved = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int ZombiesNeedToBeSaved = 20;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString TaskDescription;

	void SetTaskDescription(int32 TaskNumber, int32 IngredientNumber);
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> GameWinWidgetClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf <class AActor> WorldCameraClass;

	FTimerHandle WaveTimer;

	UUserWidget* GameWinWidget;
	UUserWidget* GameOverWidget;

	void WaveTimerDelegate();

	void CreateGameWinWidget();
	void CreateGameOverWidget();
};