#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ChoppedVegetable.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AChoppedVegetable : public AItem
{
	GENERATED_BODY()
public:
	AChoppedVegetable();
protected:
	virtual void BeginPlay() override;
};