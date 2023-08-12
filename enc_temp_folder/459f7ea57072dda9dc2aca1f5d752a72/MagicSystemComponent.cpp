// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicSystemComponent.h"
#include "BaseMagicCharacter.h"
#include "MagicSpell.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "SpellData.h"

// Sets default values for this component's properties
UMagicSystemComponent::UMagicSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMagicSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentSpellClass = ActiveMagicSpells[0];
	OwnerOfSpell = Cast<ABaseMagicCharacter>(GetOwner());
	// ...
	
}


// Called every frame
void UMagicSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

bool UMagicSystemComponent::HasEnoughMana()
{
	return false;
}

void UMagicSystemComponent::ConsumeMana(int32 ManaAmountToConsume)
{
	CurrentMana -= ManaAmountToConsume;
}

void UMagicSystemComponent::CastSpell()
{
	CurrentSpell = CurrentSpellClass->GetDefaultObject<AMagicSpell>();
	UAnimInstance* AnimInstance = Cast<ABaseMagicCharacter>(GetOwner())->GetMesh()->GetAnimInstance();
	if (CurrentSpell && CurrentSpell->SpellData && AnimInstance)
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UMagicSystemComponent::OnPlayNotifyBegin);
		AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &UMagicSystemComponent::OnPlayNotifyEnd);
		AnimInstance->Montage_Play(CurrentSpell->SpellData->SpellMontage);
	}
}

void UMagicSystemComponent::OnPlayNotifyBegin(FName Name, const FBranchingPointNotifyPayload& NotifyPayload)
{
	// Get the camera transform.
	FVector CameraLocation;
	FRotator CameraRotation;
	FVector MuzzleOffset;
	OwnerOfSpell->GetActorEyesViewPoint (CameraLocation, CameraRotation);

	// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

	// Transform MuzzleOffset from camera space to world space.
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
	// Skew the aim to be slightly upwards.
	FRotator MuzzleRotation = CameraRotation;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<ABaseMagicCharacter>(GetOwner());
	SpawnParams.Instigator = Cast<ABaseMagicCharacter>(GetOwner());
	GetWorld()->SpawnActor<AMagicSpell>(CurrentSpellClass, OwnerOfSpell->GetMesh()->GetSocketLocation(CurrentSpell->SpellData->SocketName), MuzzleRotation, SpawnParams);
}

void UMagicSystemComponent::OnPlayNotifyEnd(FName Name, const FBranchingPointNotifyPayload& NotifyPayload)
{
	UAnimInstance* AnimInstance = OwnerOfSpell->GetMesh()->GetAnimInstance();
	AnimInstance->OnPlayMontageNotifyBegin.RemoveDynamic(this, &UMagicSystemComponent::OnPlayNotifyBegin);
	AnimInstance->OnPlayMontageNotifyEnd.RemoveDynamic(this, &UMagicSystemComponent::OnPlayNotifyEnd);
}

void UMagicSystemComponent::ChangeActiveSpell(int32 Index)
{
	CurrentSpellClass = ActiveMagicSpells[Index];
}

