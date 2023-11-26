#pragma once

#include "CoreMinimal.h"
#include "ItemDesk.h"
#include "GarbageDesk.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AGarbageDesk : public AItemDesk
{
	GENERATED_BODY()
	
public:
	AGarbageDesk();

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle ActorRemoverTimer;

	void DeleteActor();

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	class USoundBase* GarbageSound;
};
