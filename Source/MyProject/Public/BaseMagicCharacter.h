// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagicSystemInterface.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "BaseMagicCharacter.generated.h"

UCLASS()
class MYPROJECT_API ABaseMagicCharacter : public ACharacter, public IMagicSystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMagicCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Implementing the interface to return MSC
	virtual class UMagicSystemComponent* GetMagicSystemComponent();

	// Implementing the interface to return the AS
	virtual class UAttributeSystemComponent* GetAttributeSet();

	// MagicSystemComponent //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MagicSystem)
	class UMagicSystemComponent* MagicSystemComponent;

	// AttributeSet //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = MagicSystem)
	class UAttributeSystemComponent* AttributeSet;

	// Helper Variables //
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CharacterSetup)
	bool CharacterTeam = 0;

	// INPUT MAPPINGS //
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;


	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking input */
	void AttackHold();
};
