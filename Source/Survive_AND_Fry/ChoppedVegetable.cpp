#include "ChoppedVegetable.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AChoppedVegetable::AChoppedVegetable()
{
	PrimaryActorTick.bCanEverTick = true;

	ChoppingEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ChoppingEffect"));
	ChoppingEffect->SetupAttachment(RootSceneComponent);
}

void AChoppedVegetable::BeginPlay()
{
	Super::BeginPlay();

	if (ChoppingTimerManager != nullptr && ChoppingEffect != nullptr)
	{
		ChoppingEffect->Activate();
		ChoppingTimerManager->SetTimer(ChoppingTimerHandle, this, &AChoppedVegetable::DisableEffects, 1.f, false);
	}
}

void AChoppedVegetable::DisableEffects()
{
	float TimeOut = 0.f;
	TimeOut = TimeOut + 1.f;
	if (TimeOut <= 3.f)
	{
		if (ChoppingTimerManager != nullptr && ChoppingEffect != nullptr)
		{
			ChoppingEffect->Deactivate();
			ChoppingTimerManager->ClearTimer(ChoppingTimerHandle);
		}
	}
}
