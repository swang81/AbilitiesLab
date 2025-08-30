// Fill out your copyright notice in the Description page of Project Settings.


#include "LabHealthAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"


void ULabHealthAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ULabHealthAttributeSet, Health);
	DOREPLIFETIME(ULabHealthAttributeSet, MaxHealth);
}

void ULabHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	UE_LOG(LogTemp, Warning, TEXT("PreChange: Attribute '%s'"), *Attribute.AttributeName);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}

	Super::PreAttributeChange(Attribute, NewValue);
}



void ULabHealthAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	UE_LOG(LogTemp,Warning, TEXT("Post Change: Attribute '%s' changed %.2f -> %.2f"),*Attribute.AttributeName, OldValue, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		OnHealthChanged.Broadcast(this, OldValue, NewValue);
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		const float CurrentHealth = GetHealth();
		OnHealthChanged.Broadcast(this, CurrentHealth, CurrentHealth);
	}
	
}

void ULabHealthAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageAttribute() )
	{
		const float DamageValue = GetDamage();
		const float OldHealthValue = GetHealth();
		const float MaxHealthValue = GetMaxHealth();
		const float NewHealthValue = FMath::Clamp(OldHealthValue -DamageValue, 0.0f, MaxHealthValue);

		if (OldHealthValue != NewHealthValue)
		{
			SetHealth(NewHealthValue);
		}

		SetDamage(0.0f);
	}
	
}

void ULabHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabHealthAttributeSet, Health, OldValue);
	const float OldHealth = OldValue.GetCurrentValue();
	const float NewHealth = GetHealth();
	OnHealthChanged.Broadcast(this, OldHealth, NewHealth);
	
}

void ULabHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULabHealthAttributeSet, MaxHealth, OldValue);
	const float CurrentHealth = GetHealth();
	OnHealthChanged.Broadcast(this, CurrentHealth, CurrentHealth);
	
}

ULabHealthAttributeSet::ULabHealthAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}
