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

	class ABread* Bread;

	int32 RandomScale;
};