#include "MainPlayer_CC.h"
#include "Engine/World.h"

AMainPlayer_CC::AMainPlayer_CC()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainPlayer_CC::BeginPlay()
{
	Super::BeginPlay();
}

void AMainPlayer_CC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainPlayer_CC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainPlayer_CC::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainPlayer_CC::MoveRight);

	FRotator RotationFromMovement = GetVelocity().Rotation();
	SetActorRotation(RotationFromMovement);
}

void AMainPlayer_CC::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AMainPlayer_CC::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}