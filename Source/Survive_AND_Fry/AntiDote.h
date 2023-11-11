#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "AntiDote.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AAntiDote : public AItem
{
	GENERATED_BODY()

public:
	AAntiDote();

protected:
	virtual void BeginPlay() override;
};