// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharAttribute.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYPROJECT_API UCharAttribute : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CurrentValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AttributeLevel;

	UFUNCTION(BlueprintCallable)
	virtual void ModifyValue(float Value);
};
