// Fill out your copyright notice in the Description page of Project Settings.


#include "CharAttribute.h"

void UCharAttribute::ModifyValue(float Value)
{
	CurrentValue += Value;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(CurrentValue));
}
