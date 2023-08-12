// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystem.h"
#include "SpellData.generated.h"


enum SpellMode
{
	Normal,
	Homing,
	AOE,
	Custom
};

UENUM()
enum SpellOwner
{
	Enemy,
	Player
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API USpellData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpellData();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:

	// Tuneable Values and Data for the New Spell (Designer Interface)



	//This defines what type of spell desried. Custom type requires implementation in the spell blueprint class otherwise it will function like a Normal spell.
	SpellMode SpellType;

	//This is the attribute of the other actor that will be affected
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "General")
	TSubclassOf<class UCharAttribute> Attribute;

	//This defines the modifying value of the spell. Use Negative Values to reduce and Positive to increase attribute.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "General")
	int32 SpellValue;

	//This defines the range of the spell. Normal or AOE. Can be used for custom implementation as well. 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "General")
	float Range;

	//Mana required for casting the spell
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "General")
	int32 ManaToConsume;

	//The VFX or effect of the spell
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "General")
	UParticleSystem* SpellVFX;

	//Sound Effect to be played
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "General")
	USoundCue* SpellSoundEffect;

	//Animation to be played when casting the spell (Make sure the AnimNotify is hooked in the correct place)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "General")
	UAnimMontage* SpellMontage;

	//Socket name from which the spell will be released (Make sure the socket is attached on the skeleton)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "General")
	FName SocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "General")
	float Cooldown;

	//HOMING ATTRIBUTES

	//Intesity with which the spell will lerp towards the target
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Homing")
	float HomingIntensity = 50.0f;

	//The range within which the opponents will be considered for homing. If no enemy is found in this range then will act as a normal spell.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Homing")
	float HomingRange = 1500.0f;

	// CONTINUOUS SPELL
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Continuous_Spell")
	bool ContinuousSpell = false;

	//AOE ATTRIBUTES
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "AOE")
	float AOERange;
};
