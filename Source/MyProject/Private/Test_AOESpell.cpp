// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_AOESpell.h"

void ATest_AOESpell::BeginPlay()
{
	Super::BeginPlay();
	PerformSphereTrace(SpellData->AOERange);
}

void ATest_AOESpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATest_AOESpell::OnCustomCollision_Implementation(AActor* OtherActor)
{
	if(OtherActor && OtherActor != Owner)
		OtherActor->K2_DestroyActor();
}
