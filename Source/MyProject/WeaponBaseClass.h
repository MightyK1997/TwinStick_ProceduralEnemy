// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "WeaponBaseClass.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGodTypes : uint8
{
	Fire	UMETA(DisplayName = "Fire"),
	Water	UMETA(DisplayName = "Water"),
	Earth	UMETA(DisplayName = "Earth"),
	Wind	UMETA(DisplayName = "Wind")
};

UCLASS(Blueprintable)
class UWeaponStatBaseClass : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	float damageDone;
	UPROPERTY(EditDefaultsOnly)
	EGodTypes typeOfGodImbibed;
	UPROPERTY(EditDefaultsOnly)
	bool isPoweredUp;
};

USTRUCT(BlueprintType)
struct FDamageBaseStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData")
	float damageDone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData")
	EGodTypes typeOfGodImbibed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageData")
	bool isPoweredUp;
};
UCLASS(Blueprintable)
class MYPROJECT_API UWeaponBaseClass : public UDamageType
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BaseDamageStats")
	TArray<FDamageBaseStruct> allDamageStats;
};