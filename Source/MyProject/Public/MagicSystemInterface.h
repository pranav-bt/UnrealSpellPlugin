// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MagicSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMagicSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYPROJECT_API IMagicSystemInterface
{
	GENERATED_BODY()


	
public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual class UAttributeSystemComponent* GetAttributeSet() = 0;

	// Pure virtual function which has to be implemented and is supposed to return a reference to the magicsystemcomponent
	virtual class UMagicSystemComponent* GetMagicSystemComponent() = 0;

	// Pura Virtual function which has to be implemented and is supposed to return a reference to the AttributeSet
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CharacterSetup)
	//bool CharacterTeam = 0;
};
