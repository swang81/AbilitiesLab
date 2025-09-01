#pragma once
#include "CoreMinimal.h"
#include "MyAbilitySlotsEnum.generated.h"

UENUM(BlueprintType)
enum class EMyAbilitySlotsEnum : uint8
{
	PrimaryAbility  UMETA(DisplayName="Primary Ability"),
	SecondaryAbility UMETA(DisplayName="Secondary Ability"),
	UltimateAbility UMETA(DisplayName="Ultimate Ability")
};

