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

	class ABread* Bread;

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

	class AMainPlayer_PC* MainPlayer_PC;

	class AMainPlayer_CC* MainPlayer_CC;

	int32 RandomScale;

	int32 RandomIngredients;

	float TimeOut = 0.f;

	FTimerHandle EffectTimerHandle;

	void DisableEffects();
};