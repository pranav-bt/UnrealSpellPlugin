// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSystemComponent.h"

// Sets default values for this component's properties
UAttributeSystemComponent::UAttributeSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	for (TSubclassOf<UCharAttribute> Attributee : AttributesToInitialize)
	{
		UCharAttribute* AttributeObject = NewObject<UCharAttribute>(this, Attributee);
		if (AttributeObject)
		{

			Attributes.Add(AttributeObject);
		}
	}
	
	// ...
}


// Called when the game starts
void UAttributeSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributeSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttributeSystemComponent::ModifyAttribute(TSubclassOf<UCharAttribute> AttributeToBeModified, float Value)
{
	for (UCharAttribute* Attribute : Attributes)
	{
		if (Attribute && Attribute->StaticClass() == AttributeToBeModified)
		{

			Attribute->ModifyValue(Value);

		}
	}
}

