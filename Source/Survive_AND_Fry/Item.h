#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void CombineItems(class AMainPlayer_CC* MainPlayer, class AActor* SecondItem);
private:
};
