// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_HomingSpell.h"
#include "Kismet/KismetMathLibrary.h"

void ATest_HomingSpell::BeginPlay()
{
	Super::BeginPlay();

	PerformBoxTrace(SpellData->Range);
}

void ATest_HomingSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HomingTarget)
	{
		FRotator SpellRotation = GetActorRotation();
		FVector SpellLocation = GetActorLocation();
		
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(SpellLocation, HomingTarget->GetActorLocation());
		FRotator LerpRotation = UKismetMathLibrary::RInterpTo_Constant(SpellRotation, LookAtRotation, DeltaTime, SpellData->HomingIntensity);

		SetActorRotation(LerpRotation);

		FVector SpellVelocity = GetActorForwardVector() * ProjectileMovementComponent->MaxSpeed;

		ProjectileMovementComponent->Velocity = SpellVelocity;

	}

	else
	{
		ProjectileMovementComponent->InitialSpeed = 1000.0f;
		FireInDirection(Owner->GetActorForwardVector());
	}
}



void ATest_HomingSpell::OnCustomCollision_Implementation(AActor* OtherActor)
{
	if (OtherActor && OtherActor != Owner)
	{
		OtherActor->K2_DestroyActor();
		Destroy();
	}
}
