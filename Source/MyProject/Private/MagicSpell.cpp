// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicSpell.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BaseMagicCharacter.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameplayTagContainer.h"



// Sets default values
AMagicSpell::AMagicSpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 0.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!SpellData)
	{
		SpellData = CreateDefaultSubobject<USpellData>(TEXT("SpellDataComponent"));
	}

	Owner = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

/* TODO: Make this into an object oriented approach where every spell type is an individual object with begin, tick and end states. */
// Called when the game starts or when spawned
void AMagicSpell::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::SpawnEmitterAttached(SpellData->SpellVFX, RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMagicSpell::OnCollisionOfSpell);


}

// Called every frame
void AMagicSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagicSpell::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AMagicSpell::OnCollisionOfSpell(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnCustomCollision(OtherActor);
}

void AMagicSpell::OnCustomCollision_Implementation(AActor* OtherActor)
{
	//Provide basic implementation for collision
	//This can be overridden in dervied cpp or Blueprint class as well if required
}

void AMagicSpell::PerformSphereTrace(float Radius)
{
	FVector StartLocation = Owner->GetActorLocation(); // Get the player's current location
	FVector EndLocation = StartLocation + FVector(0.f, 0.f, Radius); // Calculate the end location for the sphere trace


	// Set up the query parameters for the sphere trace
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the player character during the trace

	// Perform the sphere trace
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		StartLocation,
		EndLocation,
		FQuat::Identity, // No rotation
		ECC_Visibility, // Trace against the visibility collision channel
		FCollisionShape::MakeSphere(Radius), // Use a sphere as the trace shape
		CollisionParams
	);

	if (bHit)
	{

		bool OwnerTeam = Cast<ABaseMagicCharacter>(Owner)->CharacterTeam;
		// Process the hit results and overlapping actors
		for (const FHitResult& HitResult : HitResults)
		{

			if (ABaseMagicCharacter* OtherActor = Cast<ABaseMagicCharacter>(HitResult.GetActor()))
			{
				bool TeamCheck = OwnerTeam == OtherActor->CharacterTeam;
				if (!TeamCheck)
				{
					OnCustomCollision(OtherActor);
				}
			}
		}



	}
}

void AMagicSpell::PerformBoxTrace(float Length)
{
	FVector StartLocation = Owner->GetActorLocation(); // Get the player's current location
	FVector ForwardVector = Owner->GetActorForwardVector(); // Get the forward vector of the player
	FVector EndLocation = StartLocation + ForwardVector * Length; // Calculate the end location for the box trace

	FQuat Rotation = FRotationMatrix::MakeFromX(ForwardVector).ToQuat(); // Calculate rotation based on the forward vector

	// Set up the query parameters for the box trace
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Owner); // Ignore the player character during the trace

	// Perform the box trace
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		StartLocation,
		EndLocation,
		Rotation,
		ECC_Visibility, // Trace against the visibility collision channel
		FCollisionShape::MakeBox(FVector(SpellData->HomingRange,1000,250)), // Use a box as the trace shape
		CollisionParams
	);

	if (bHit)
	{
		// FOR VISUALIZATION PURPOSE ONLY
		DrawDebugBox(
			GetWorld(),
			StartLocation + ((EndLocation - StartLocation) / 2),
			FVector(SpellData->HomingRange, 1000, 250),
			FColor::Green,
			false,
			2.0f,
			0,
			5.0f
		);


		// Process the hit results and overlapping actors
		for (const FHitResult& HitResult : HitResults)
		{

			bool OwnerTeam = Cast<ABaseMagicCharacter>(Owner)->CharacterTeam;
			
			
			if (ABaseMagicCharacter* OtherActor = Cast<ABaseMagicCharacter>(HitResult.GetActor()))
			{
				bool TeamCheck = OwnerTeam == OtherActor->CharacterTeam;
				if (!TeamCheck)
				{
					HomingTarget = OtherActor;
					return;
				}
			}
		}
	}
}

//void AMagicSpell::OnCustomCollision()
//{
//}

