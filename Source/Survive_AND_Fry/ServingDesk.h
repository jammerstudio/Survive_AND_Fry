#pragma once

#include "CoreMinimal.h"
#include "ItemDesk.h"
#include "ServingDesk.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AServingDesk : public AItemDesk
{
	GENERATED_BODY()

public:
	AServingDesk();

	void ServeItem();

	void EnlargeItem(float ScaleAmount);

	float ScaleValue = 1.f;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* ServingBoard;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	class USoundBase* SuccessSound;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	class USoundBase* FailSound;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UNiagaraComponent* SuccessfullServeEffect;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UNiagaraComponent* UnSuccessfullServeEffect;

	class ABread* Bread;

	class AMainPlayer_PC* MainPlayer_PC;

	int32 RandomScale;

	class FTimerManager* TimerManager;

	FTimerHandle EffectTimerHandle;

	void DisableEffects();
};