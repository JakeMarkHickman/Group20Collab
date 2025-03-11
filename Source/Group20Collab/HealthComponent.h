// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthComponent_HealthChangedEvent, float, UpdatedHealth, float, HealthChanged, AController*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthComponent_MaxHealthChangedEvent, float, UpdatedHealth, float, HealthChanged, AController*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthComponent_DeathEvent, AController*, Instigator);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GROUP20COLLAB_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UPROPERTY(BlueprintAssignable, Category = Health)
	FHealthComponent_HealthChangedEvent _OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = Health)
	FHealthComponent_MaxHealthChangedEvent _OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = Health)
	FHealthComponent_DeathEvent _OnDeath;
	
protected:
	UPROPERTY()
	float _CurrentHealth;

	UPROPERTY(EditAnywhere)
	float _MaxHealth;
	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer);
	
	void SetCurrentHealth(float value, AController* Instigator);
	void SetMaxHealth(float value, AController* Instigator);

	float GetCurrentHealth() { return _CurrentHealth; };
	float GetMaxHealth() { return _MaxHealth; };
};
