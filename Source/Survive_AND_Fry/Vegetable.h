#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Vegetable.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AVegetable : public AItem
{
	GENERATED_BODY()
public:
	AVegetable();

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class USceneComponent* RootSceneComponent;
};