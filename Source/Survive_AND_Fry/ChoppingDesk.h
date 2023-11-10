#pragma once

#include "CoreMinimal.h"
#include "ItemDesk.h"
#include "ChoppingDesk.generated.h"

UCLASS()
class SURVIVE_AND_FRY_API AChoppingDesk : public AItemDesk
{
	GENERATED_BODY()

public:
	AChoppingDesk();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* ChoppingBoard;
};