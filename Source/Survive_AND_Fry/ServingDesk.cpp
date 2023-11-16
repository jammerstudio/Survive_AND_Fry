#include "ServingDesk.h"
#include "Bread.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer_PC.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundBase.h"
#include "MainPlayer_CC.h"
#include "TimerManager.h"

AServingDesk::AServingDesk()
{
	PrimaryActorTick.bCanEverTick = true;

	ServingBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ServingBoard"));
	ServingBoard->SetupAttachment(DefaultSceneRoot);

	SuccessfullServeEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SuccessFullEffect"));
	SuccessfullServeEffect->SetupAttachment(DefaultSceneRoot);

	UnSuccessfullServeEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("UnSuccessFullEffect"));
	UnSuccessfullServeEffect->SetupAttachment(DefaultSceneRoot);
}

void AServingDesk::BeginPlay()
{
	Super::BeginPlay();

	if (TimerManager != nullptr)
	{
		TimerManager->SetTimer(EffectTimerHandle, this, &AServingDesk::DisableEffects , 1.f, false);
		TimerManager->PauseTimer(EffectTimerHandle);
	}

	RandomScale = FMath::RandRange(1, 3);
	APlayerController* PlayerCharacterReference = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerCharacterReference != nullptr)
	{
		MainPlayer_PC = Cast<AMainPlayer_PC>(PlayerCharacterReference);
		if (MainPlayer_PC != nullptr)
		{
			MainPlayer_PC->SetTaskDescription(RandomScale);
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Random Scale : %d"), RandomScale);
	if (SuccessfullServeEffect != nullptr && UnSuccessfullServeEffect != nullptr)
	{
		SuccessfullServeEffect->Deactivate();
		UnSuccessfullServeEffect->Deactivate();
	}
}

void AServingDesk::DisableEffects()
{
	float TimeOut = 0.f;
	TimeOut = TimeOut + 1.f;
	if (TimeOut <= 3.f)
	{
		if (SuccessfullServeEffect != nullptr && UnSuccessfullServeEffect != nullptr && TimerManager != nullptr)
		{
			SuccessfullServeEffect->Deactivate();
			UnSuccessfullServeEffect->Deactivate();
			TimerManager->PauseTimer(EffectTimerHandle);
			TimeOut = 0.f;
		}
	}
}

void AServingDesk::ServeItem()
{
	Bread = Cast<ABread>(ItemOnDesk);
	if (Bread != nullptr)
	{
		if (Bread->HasVegetable == true && Bread->HasAntiDote == true && RandomScale == ScaleValue)
		{
			ItemOnDesk = nullptr;
			UE_LOG(LogTemp, Display, TEXT("Food Served!"));
			RandomScale = FMath::RandRange(1, 3);
			UE_LOG(LogTemp, Display, TEXT("Random Scale : %d"), RandomScale);
			ScaleValue = 1.f;
			if (MainPlayer_PC != nullptr)
			{
				MainPlayer_PC->SetTaskDescription(RandomScale);
				MainPlayer_PC->ZombiesSaved = MainPlayer_PC->ZombiesSaved + 1;
				if (SuccessfullServeEffect != nullptr && SuccessSound != nullptr && TimerManager!= nullptr)
				{
					UGameplayStatics::PlaySound2D(GetWorld(), SuccessSound);
					SuccessfullServeEffect->Activate();

					TimerManager->UnPauseTimer(EffectTimerHandle);
				}
			}
			Bread->Destroy();
		}
		else
		{
			ItemOnDesk = nullptr;
			UE_LOG(LogTemp, Display, TEXT("Wrong Food Served!"));
			RandomScale = FMath::RandRange(1, 3);
			UE_LOG(LogTemp, Display, TEXT("Random Scale : %d"), RandomScale);
			ScaleValue = 1.f;
			if (MainPlayer_PC != nullptr)
			{
				MainPlayer_PC->SetTaskDescription(RandomScale);
				MainPlayer_PC->TimeLeft = MainPlayer_PC->TimeLeft - 10.f;
				if (UnSuccessfullServeEffect != nullptr && FailSound != nullptr && TimerManager != nullptr)
				{
					UGameplayStatics::PlaySound2D(GetWorld(), FailSound);
					UnSuccessfullServeEffect->Activate();

					TimerManager->UnPauseTimer(EffectTimerHandle);
				}
			}
			Bread->Destroy();
		}
	}
}

void AServingDesk::EnlargeItem(float ScaleAmount)
{
	Bread = Cast<ABread>(ItemOnDesk);
	if (Bread != nullptr)
	{
		if (Bread->HasVegetable == true && Bread->HasAntiDote == true)
		{
			Bread->SetActorScale3D(FVector(ScaleAmount, ScaleAmount, 1));
			UE_LOG(LogTemp, Log, TEXT("Scale Is : %f"), ScaleAmount);
		}
	}
}