#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayer_PC.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AMainPlayer_PC : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int TimeLeft;
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf <class AActor> WorldCameraClass;

	FTimerHandle WaveTimer;

	void WaveTimerDelegate();
};