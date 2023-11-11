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

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* ServingBoard;

	class ABread* Bread;
};