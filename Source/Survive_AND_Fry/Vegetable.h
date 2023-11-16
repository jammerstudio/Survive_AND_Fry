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

	virtual void ChopItem(float Delta) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float ChoppingSpeed = 2.f;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* ProgressWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> ChoppedItemReference;

	class AMainPlayer_CC* MainPlayer;

	class AChoppingDesk* ChoppingDesk;
};