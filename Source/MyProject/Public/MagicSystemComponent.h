// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseMagicCharacter.h"
#include "MagicSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UMagicSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMagicSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Member Variables //

	// Owner of the Spell
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ABaseMagicCharacter* OwnerOfSpell;

	// Max Mana of the owner
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxMana = 100;

	// Current Mana of the owner
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentMana = 100;

	// Max Spells of the owner. This is the maximum number of spells this owner can hold
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxNumberOfSpells = 100;

	// All Spells of the owner. These are all the spells that the owner holds
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<class AMagicSpell>> AllMagicSpells;

	// Max Active spells of the owner
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 MaxActiveSpellsOfOwner = 4;

	// Active Spells of the owner. These are the spells which are currently active and between which the owner can toggle quickly.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<class AMagicSpell>> ActiveMagicSpells;
	 
	// Current Spell of the owner. Currently selected spell.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AMagicSpell> CurrentSpellClass;

	AMagicSpell* CurrentSpell;


	// Helper Functions //

	// Check if owner has enough mana
	bool HasEnoughMana();

	// Consumes the desired amount of mana. Includes the HasEnoughMana check
	void ConsumeMana(int32 ManaAmountToConsume);

	// This method initializes the spell by playing the correct montage
	UFUNCTION(BlueprintCallable)
	void CastSpell();

	UFUNCTION()
	void OnPlayNotifyBegin(FName Name, const FBranchingPointNotifyPayload& NotifyPayload);

	UFUNCTION()
	void OnPlayNotifyEnd(FName Name, const FBranchingPointNotifyPayload& NotifyPayload);

	// Change the current spell from one of the active spells
	UFUNCTION(BlueprintCallable)
	void ChangeActiveSpell(int32 Index);
};
