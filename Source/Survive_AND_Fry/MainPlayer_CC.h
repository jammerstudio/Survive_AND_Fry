#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer_CC.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AMainPlayer_CC : public ACharacter
{
	GENERATED_BODY()

public:
	AMainPlayer_CC();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	AActor* HoldingItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Progress;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool IsHolding = false;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool IsChopping = false;

	void SetTaskDescription(float CurrentScale);
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float TurnRate;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float TraceDistance = 30.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float SphereSize = 15.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* Knife;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USceneComponent* HoldingLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UArrowComponent* PlayerTracePointer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UMaterialInterface* NormalMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UMaterialInterface* TraceMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USoundBase* ChoppingSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MoveSpeed = 300.f;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString CurrentScaleDescription;

	FHitResult Hit;

	bool IsHit;

	class AItemDesk* ItemDesk;

	class AChoppingDesk* ChoppingDesk;

	class AServingDesk* ServingDesk;

	FTimerHandle ChoppingHandle;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void GrabORRelease();
	void StartChopping();

	bool TraceObject();
	void DeskFunctions(class AActor* Desk);
	void ProcessChopping();
	void ProcessServing();
	void EnlargeItem();
};