// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicSpell.h"
#include "Test_HomingSpell.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ATest_HomingSpell : public AMagicSpell
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void OnCustomCollision(AActor* OtherActor);
	// Override the collision event. This is the function that decides what should happen on impact/trigger of spell.
	virtual void OnCustomCollision_Implementation(AActor* OtherActor) override;
};
