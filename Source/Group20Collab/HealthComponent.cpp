// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent(): _MaxHealth(100.f)
{
	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	_CurrentHealth = _MaxHealth;
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer)
{
	float preHealth = _CurrentHealth;
	SetCurrentHealth(_CurrentHealth - damage, instigator);
	_OnHealthChanged.Broadcast(_CurrentHealth, damage, instigator);
}

void UHealthComponent::SetCurrentHealth(float value, AController* Instigator)
{
	_CurrentHealth = value;

	if(_CurrentHealth <= 0)
	{
		_OnDeath.Broadcast(Instigator);
	}
}

void UHealthComponent::SetMaxHealth(float value, AController* Instigator)
{
	float HealthPercent = _CurrentHealth / _MaxHealth;
	_OnMaxHealthChanged.Broadcast(value, _MaxHealth - value, Instigator);
	
	_MaxHealth = value;

	SetCurrentHealth(HealthPercent * _MaxHealth, Instigator);
}

