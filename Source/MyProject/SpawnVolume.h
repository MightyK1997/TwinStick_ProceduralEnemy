// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCustomGameInstance.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"
#include "SpawnVolume.generated.h"



UCLASS()
class MYPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actors properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	UMyCustomGameInstance *p_Instance;
	

protected:

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyCharacter> FodderToSpawn;
	//SAEnemyCharacter *WhatToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyCharacter> KnightToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AEnemyCharacter> MinionToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	EEnemyType enemyType;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "AIControllerClass"), Category = Pawn)
	TSubclassOf<class AEnemyAI> SpawnedEnemyAI;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float StartEnemyNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float EachWaveIncreaseEnemy;
	
	float SpawnDelayMax;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* WhereToSpawn;

	void SpawnEnemy();
	//void DestroyEnemy(AEnemyCharacter* i_pEnemy);
	void BeginNewWave();

	//only in code, no BluePrint access
	float SpawnDelay;

	//spawned enemy parameters
	uint8 waveNumber;
	uint8 enemiesSpawned;
	//uint8 spawnedPawnNumber;
	//uint8 spawnedMinionNumber;
	//uint8 spawnedKnightNumber;
	uint8 enemyClassID;
};
