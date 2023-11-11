#include "ServingDesk.h"
#include "Bread.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayer_PC.h"

AServingDesk::AServingDesk()
{
	PrimaryActorTick.bCanEverTick = true;

	ServingBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ServingBoard"));
	ServingBoard->SetupAttachment(DefaultSceneRoot);
}

void AServingDesk::BeginPlay()
{
	Super::BeginPlay();
	RandomScale = FMath::RandRange(1, 3);
	PlayerCharacterReference = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerCharacterReference != nullptr)
	{
		MainPlayer_PC = Cast<AMainPlayer_PC>(PlayerCharacterReference);
		if (MainPlayer_PC != nullptr)
		{
			MainPlayer_PC->SetTaskDescription(RandomScale);
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Random Scale : %d"), RandomScale);
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
			if (PlayerCharacterReference != nullptr)
			{
				MainPlayer_PC = Cast<AMainPlayer_PC>(PlayerCharacterReference);
				if (MainPlayer_PC != nullptr)
				{
					MainPlayer_PC->SetTaskDescription(RandomScale);
					MainPlayer_PC->ZombiesSaved = MainPlayer_PC->ZombiesSaved + 1;
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
			if (PlayerCharacterReference != nullptr)
			{
				MainPlayer_PC = Cast<AMainPlayer_PC>(PlayerCharacterReference);
				if (MainPlayer_PC != nullptr)
				{
					MainPlayer_PC->SetTaskDescription(RandomScale);
					MainPlayer_PC->TimeLeft = MainPlayer_PC->TimeLeft - 10.f;
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