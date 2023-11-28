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

	SetRootComponent(DefaultSceneRoot);

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

	GetWorldTimerManager().SetTimer(EffectTimerHandle, this, &AServingDesk::DisableEffects , 1.f, true);
	GetWorldTimerManager().PauseTimer(EffectTimerHandle);

	RandomScale = FMath::RandRange(1, 3);
	RandomIngredients = FMath::RandRange(1, 2);
	APlayerController* PlayerControllerReference = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerControllerReference != nullptr)
	{
		MainPlayer_PC = Cast<AMainPlayer_PC>(PlayerControllerReference);
		if (MainPlayer_PC != nullptr)
		{
			MainPlayer_PC->SetTaskDescription(RandomScale, RandomIngredients);
		}
	}
	ACharacter* PlayerCharacterReference = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (PlayerCharacterReference != nullptr)
	{
		MainPlayer_CC = Cast<AMainPlayer_CC>(PlayerCharacterReference);
	}
	UE_LOG(LogTemp, Display, TEXT("Random Scale : %d"), RandomScale);
	UE_LOG(LogTemp, Display, TEXT("Random Ingredients : %d"), RandomIngredients);
}

void AServingDesk::DisableEffects()
{
	TimeOut = TimeOut + 1.f;
	UE_LOG(LogTemp, Display, TEXT("Timeout : %f"), TimeOut);
	if (TimeOut >= 3.f)
	{
		if (SuccessfullServeEffect != nullptr && UnSuccessfullServeEffect != nullptr)
		{
			SuccessfullServeEffect->Deactivate();
			UnSuccessfullServeEffect->Deactivate();
			GetWorldTimerManager().PauseTimer(EffectTimerHandle);
			TimeOut = 0.f;
		}
	}
}

void AServingDesk::ServeItem()
{
	Bread = Cast<ABread>(ItemOnDesk);
	if (Bread != nullptr)
	{
		if (MainPlayer_CC != nullptr)
		{
			MainPlayer_CC->SetTaskDescription(0.f);
		}
		if (RandomIngredients == 1)
		{
			if (Bread->HasTomato == true && Bread->HasAntiDote == true && RandomScale == ScaleValue)
			{
				ItemOnDesk = nullptr;
				UE_LOG(LogTemp, Display, TEXT("Food Served!"));
				RandomScale = FMath::RandRange(1, 3);
				RandomIngredients = FMath::RandRange(1, 2);
				UE_LOG(LogTemp, Display, TEXT("Random Scale : %d"), RandomScale);
				ScaleValue = 1.f;
				if (MainPlayer_PC != nullptr)
				{
					MainPlayer_PC->SetTaskDescription(RandomScale, RandomIngredients);
					MainPlayer_PC->ZombiesSaved = MainPlayer_PC->ZombiesSaved + 1;
					MainPlayer_PC->TimeLeft = MainPlayer_PC->TimeLeft + 5.f;
					if (SuccessfullServeEffect != nullptr)
					{
						SuccessfullServeEffect->Activate();
						GetWorldTimerManager().UnPauseTimer(EffectTimerHandle);
					}
					if (SuccessSound != nullptr)
					{
						UGameplayStatics::PlaySound2D(GetWorld(), SuccessSound);
					}
				}
				Bread->Destroy();
			}
			else
			{
				ItemOnDesk = nullptr;
				UE_LOG(LogTemp, Display, TEXT("Wrong Food Served!"));
				RandomScale = FMath::RandRange(1, 3);
				RandomIngredients = FMath::RandRange(1, 2);
				UE_LOG(LogTemp, Display, TEXT("Random Scale : %d"), RandomScale);
				ScaleValue = 1.f;
				if (MainPlayer_PC != nullptr)
				{
					MainPlayer_PC->SetTaskDescription(RandomScale, RandomIngredients);
					MainPlayer_PC->TimeLeft = MainPlayer_PC->TimeLeft - 10.f;
					if (UnSuccessfullServeEffect != nullptr)
					{
						UnSuccessfullServeEffect->Activate();
						GetWorldTimerManager().UnPauseTimer(EffectTimerHandle);
					}
					if (FailSound != nullptr)
					{
						UGameplayStatics::PlaySound2D(GetWorld(), FailSound);
					}
				}
				Bread->Destroy();
			}
		}
		else if (RandomIngredients == 2)
		{
			if (Bread->HasLettuce == true && Bread->HasAntiDote == true && RandomScale == ScaleValue)
			{
				ItemOnDesk = nullptr;
				UE_LOG(LogTemp, Display, TEXT("Food Served!"));
				RandomScale = FMath::RandRange(1, 3);
				RandomIngredients = FMath::RandRange(1, 2);
				UE_LOG(LogTemp, Display, TEXT("Random Scale : %d"), RandomScale);
				ScaleValue = 1.f;
				if (MainPlayer_PC != nullptr)
				{
					MainPlayer_PC->SetTaskDescription(RandomScale, RandomIngredients);
					MainPlayer_PC->ZombiesSaved = MainPlayer_PC->ZombiesSaved + 1;
					MainPlayer_PC->TimeLeft = MainPlayer_PC->TimeLeft + 5.f;
					if (SuccessfullServeEffect != nullptr)
					{
						SuccessfullServeEffect->Activate();
						GetWorldTimerManager().UnPauseTimer(EffectTimerHandle);
					}
					if (SuccessSound != nullptr)
					{
						UGameplayStatics::PlaySound2D(GetWorld(), SuccessSound);
					}
				}
				Bread->Destroy();
			}
			else
			{
				ItemOnDesk = nullptr;
				UE_LOG(LogTemp, Display, TEXT("Wrong Food Served!"));
				RandomScale = FMath::RandRange(1, 3);
				RandomIngredients = FMath::RandRange(1, 2);
				UE_LOG(LogTemp, Display, TEXT("Random Scale : %d"), RandomScale);
				ScaleValue = 1.f;
				if (MainPlayer_PC != nullptr)
				{
					MainPlayer_PC->SetTaskDescription(RandomScale, RandomIngredients);
					MainPlayer_PC->TimeLeft = MainPlayer_PC->TimeLeft - 10.f;
					if (UnSuccessfullServeEffect != nullptr)
					{
						UnSuccessfullServeEffect->Activate();
						GetWorldTimerManager().UnPauseTimer(EffectTimerHandle);
					}
					if (FailSound != nullptr)
					{
						UGameplayStatics::PlaySound2D(GetWorld(), FailSound);
					}
				}
				Bread->Destroy();
			}
		}
	}
}

void AServingDesk::EnlargeItem(float ScaleAmount)
{
	Bread = Cast<ABread>(ItemOnDesk);
	if (Bread != nullptr)
	{
		if (ScaleAmount == 1)
		{
			Bread->SetActorScale3D(FVector(1, 1, 1));
		}
		else if (ScaleAmount == 2)
		{
			Bread->SetActorScale3D(FVector(1.5, 1.5, 1));
		}
		else
		{
			Bread->SetActorScale3D(FVector(2, 2, 1));
		}
		UE_LOG(LogTemp, Log, TEXT("Scale Is : %f"), ScaleAmount);
	}
}