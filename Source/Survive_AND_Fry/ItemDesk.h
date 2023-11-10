#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDesk.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AItemDesk : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemDesk();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* Desk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class AActor* ItemOnDesk;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class USceneComponent* ItemLocation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> ItemOnDeskReference;

private:
};
