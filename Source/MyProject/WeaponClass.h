// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponClass.generated.h"

UENUM(BlueprintType)
enum class EWeaponMetalEnum : uint8
{
	WM_Wood		UMETA(DisplayName = "Weapon Material Wood"),
	WM_Bronze	UMETA(DisplayName = "Weapon Material Bronze"),
	WM_Steel	UMETA(DisplayName = "Weapon Material Steel"),
	WM_Obsidian	UMETA(DisplayName = "Weapon Material Obsidian"),
	WM_Dragon	UMETA(DisplayName = "Weapon Material Dragon")
};

UCLASS(Blueprintable)
class MYPROJECT_API AWeaponClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponClass();

	AWeaponClass(float i_damage, char* i_weaponName, char* i_className, float i_numberOfMultiHitEnemies, float i_Speed, float i_CriticalAttack) :
		damage(i_damage), weaponName(i_weaponName), className(i_className), numberOfMultiHitEnemies(i_numberOfMultiHitEnemies), speed(i_Speed), criticalAttack(i_CriticalAttack)
	{

	}

	AWeaponClass* GetWeaponDetails();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FString weaponName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FString className;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float numberOfMultiHitEnemies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float criticalAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		float weaponXP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		EWeaponMetalEnum MetalTypes;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	FVector weaponScale;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};