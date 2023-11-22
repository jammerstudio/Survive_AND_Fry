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

	if (ChoppingEffect != nullptr)
	{
		ChoppingEffect->Activate();
		GetWorldTimerManager().SetTimer(ChoppingTimerHandle, this, &AChoppedVegetable::DisableEffects, 1.f, true);
	}
}

void AChoppedVegetable::DisableEffects()
{
	TimeOut = TimeOut + 1.f;
	if (TimeOut >= 3.f)
	{
		if (ChoppingEffect != nullptr)
		{
			ChoppingEffect->Deactivate();
			GetWorldTimerManager().ClearTimer(ChoppingTimerHandle);
		}
	}
}
