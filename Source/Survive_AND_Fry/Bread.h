#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Bread.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API ABread : public AItem
{
	GENERATED_BODY()
public:
	ABread();

protected:
	virtual void BeginPlay() override;
public:
	class AItem* Item;
	
	virtual void CombineItems(class AMainPlayer_CC* MainPlayer, class AActor* SecondItem) override;

	bool HasVegetable = false;

	bool HasAntiDote = false;
private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* BreadTop;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* BreadBottom;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* VegetableMesh;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* AntiDoteMesh;

	class AChoppedVegetable* ChoppedVegetable;

	class AAntiDote* AntiDote;
};
