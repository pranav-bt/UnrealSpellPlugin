// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalSpell.h"

void ANormalSpell::BeginPlay()
{
	Super::BeginPlay();

	if (Owner)
	{
		FireInDirection(Owner->GetActorForwardVector());
	}
}

void ANormalSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Owner && FVector::Dist(Owner->GetActorLocation(), this->GetActorLocation()) > SpellData->Range)
	{
		this->K2_DestroyActor();
		CollisionComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AMagicSpell::OnCollisionOfSpell);
	}
}

void ANormalSpell::OnCustomCollision_Implementation(AActor* OtherActor)
{
	if (OtherActor && OtherActor!=Owner)
		OtherActor->K2_DestroyActor();
	// This function is for default implementation of normal spell collision
	// If the event in blueprint is used then this default implementation will not be called
}
