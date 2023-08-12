// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharAttribute.h"
#include "AttributeSystemComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UAttributeSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	// DO NOT MODIFY THIS CLASS //



	// All the attributes that this character has. Can be reused for multiple characters having similar attributes
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<UCharAttribute>> AttributesToInitialize;

	// Dont expose this. For internal use only
	UPROPERTY()
	TArray<UCharAttribute*> Attributes;

	UFUNCTION(BlueprintCallable)
	virtual void ModifyAttribute(TSubclassOf<UCharAttribute> AttributeToBeModified, float Value);




};
