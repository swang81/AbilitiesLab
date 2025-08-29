// Fill out your copyright notice in the Description page of Project Settings.


#include "LabHealthAttributeSet.h"
#include "Net/UnrealNetwork.h"



void ULabHealthAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ULabHealthAttributeSet, Health);
	DOREPLIFETIME(ULabHealthAttributeSet, MaxHealth);
}

ULabHealthAttributeSet::ULabHealthAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}