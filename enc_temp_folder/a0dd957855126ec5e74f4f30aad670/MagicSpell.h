// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "GameplayTagContainer.h"
#include "SpellData.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MagicSpell.generated.h"




UCLASS()
class MYPROJECT_API AMagicSpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicSpell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	USphereComponent* CollisionComponent;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Spell Data component.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SpellData)
	USpellData* SpellData;


	// Helper Variables


	// Owner of this spell that is cast
	ACharacter* Owner;

	// Stores the hit results of sphere or box trace
	TArray<FHitResult> HitResults;

	// Current Overlapping actor on AOE
	AActor* OverlappingActor;

	// Homing Target if any
	AActor* HomingTarget;


	// Helper Functions


	// Function that initializes the projectile's velocity in the shoot direction.
	void FireInDirection(const FVector& ShootDirection);

	// On Collision event function
	UFUNCTION()
	void OnCollisionOfSpell(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	// Collision function which can be customised if required or has general implementation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Collision" , DisplayName = "SpellEffectTrigger")
	void OnCustomCollision(AActor* OtherActor);
	virtual void OnCustomCollision_Implementation(AActor* OtherActor);


	// Sphere trace function that checks all overlapping actors
	void PerformSphereTrace(float Radius);

	// Box trace function in front of the player which returns all overlapping actors. Used for indetifying homing target
	void PerformBoxTrace(float Length);

};
