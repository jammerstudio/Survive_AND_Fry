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

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	AActor* HoldingItem;
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float TurnRate;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float TraceDistance = 30.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float SphereSize = 15.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USceneComponent* HoldingLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UMaterialInterface* NormalMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UMaterialInterface* TraceMaterial;

	FHitResult Hit;

	class AItemDesk* ItemDesk;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void GrabORRelease();

	bool TraceObject();
	void DeskFunctions(class AActor* Desk);
};