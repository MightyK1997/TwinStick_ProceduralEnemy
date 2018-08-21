// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BetweenWavesWidget.h"
#include "WeaponClass.h"
#include "Engine/GameInstance.h"
#include "MoviePlayer.h"
#include "MyCustomGameInstance.generated.h"

/**
*
*/

UENUM(BlueprintType)
enum class EWeaponPowerups : uint8
{
	Fire	UMETA(DisplayName = "Fire"),
	Water	UMETA(DisplayName = "Water"),
	Earth	UMETA(DisplayName = "Earth"),
	Wind	UMETA(DisplayName = "Wind")
};

UCLASS()
class MYPROJECT_API UMyCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	//Local Variables and Methods
	UMyCustomGameInstance(const FObjectInitializer& ObjectInitializer);
	float GetCurrentWave();

	void SetCurrentWave(float i_wave);

	void ChangeStats(float i_wave, float i_gold);
	float GetTotalGold();
	void IncreaseWave();

	virtual void Init() override;

	UFUNCTION()
		virtual void BeginLoadingScreen(const FString& MapName);
	UFUNCTION()
		virtual void EndLoadingScreen(UWorld* InLoadedWorld);

	
	
	float g_TotalEnemies;
	float g_CurrentEnemiesToSpawn;
	
	float g_FodderSpawned;
	float g_MinionsSpawned;
	float g_KnightSpawned;

	// Bluprintable Variables and Methods
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerGold)
	float g_CurrentWaveSpawnedEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerGold)
	float g_CurrentWaveDestroyedEnemies;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerGold)
	float g_Wave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerGold)
	float g_WaveSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isSwordUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isTantoUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isGaldiusUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isBasketUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isOno1Unlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isOno2Unlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isQuiangUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isCarolingianUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isChengdaoUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isClaymoreUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isCutlassUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isHallherdUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isKatanaUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isKhandaUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isLabrysUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isLiuyedaoUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isMiaodaoUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isNzappaUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isPodaoUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isQuarterstaffUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isSaiUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isScimitarUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isScytheUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isSevenbranchUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isSpetumUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isTrishulaUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isZanbatoUnlocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
		bool isZweihanderUnlocked;

	/*Current Player Weapon*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
	TSubclassOf<AWeaponClass> g_CurrentWeapon;
	//UClass* g_CurrentWeapon = AWeaponClass::StaticClass();/*reinterpret_cast<AWeaponClass*>(AWeaponClass::StaticClass());*/
	/*Alternate PlayerWeapon*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerGold)
	float g_Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerGold)
	float g_WaveSetGold;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerGold)
	float g_IndividualWaveGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
		FString CurrentWeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
		FString AlternateWeaponName;

	//UClass* g_AlternateWeapon = AWeaponClass::StaticClass();/*reinterpret_cast<AWeaponClass*>(AWeaponClass::StaticClass());*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
	TSubclassOf<AWeaponClass> g_AlternateWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
	AWeaponClass* Sword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
	AWeaponClass* Quiang;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
	AWeaponClass* Tanto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
	AWeaponClass* BasketSword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
	AWeaponClass* Gladius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
	AWeaponClass* Ono1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerWeaponInstance)
	AWeaponClass* Ono2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = God)
		EWeaponPowerups GodSelected;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Unlocks")
	//	bool isSwordUnlocked;


	//private:
	//	UBetweenWavesWidget* p_BetweenWavesUI;
	//
	//protected:
	//	UPROPERTY(EditDefaultsOnly)
	//	TSubclassOf<UBetweenWavesWidget> BetweenWavesUI_BP;

public:
	void ShowWidget();
	void ChangeMap(const char* i_map);
};

