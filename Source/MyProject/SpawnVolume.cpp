// Fill out your copyright notice in the Description page of Project Settings.
#include "SpawnVolume.h"
#include "MyProject.h"
#include "Kismet/KismetMathLibrary.h"
#include "vector.h"


PRAGMA_DISABLE_DEPRECATION_WARNINGS


// Sets default values
ASpawnVolume::ASpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	//RootComponent = WhereToSpawn
	SpawnDelayMin = 1.0f;
	SpawnDelayMax = 4.5f;
	enemiesSpawned = 0;

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	//SpawnDelay = FMath::FRandRange(SpawnDelayMin, SpawnDelayMax);
	
	SpawnDelay = 5.f;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnEnemy, SpawnDelay, false);
	p_Instance = Cast<UMyCustomGameInstance>(GetGameInstance());
	enemyClassID = 1;

}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (p_Instance->g_CurrentWaveSpawnedEnemies == 0)
		SpawnEnemy();
*/
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	//FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;
	
	//FVector SpawnExtent = FVector(100.f, 100.f, 0.f);
	return SpawnOrigin;
	//return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void ASpawnVolume::SpawnEnemy()
{
	//If something to spawn
	if (FodderToSpawn != NULL && KnightToSpawn && MinionToSpawn)
	{
		//check for valid world
		UWorld* const world = GetWorld();
		if (world)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "new wave start");
			//set spawn parameters
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Instigator = Instigator;
			SpawnParameters.bNoFail = true;
			//get random spawn location
			FVector SpawnLocation = GetRandomPointInVolume();

			//get random rotation
			FRotator SpawnRotator;
			SpawnRotator.Yaw = FMath::FRand() * 0.f ;
			SpawnRotator.Pitch = FMath::FRand() * 0.f;
			SpawnRotator.Roll = FMath::FRand() * 0.f;
			
			//spawn enemy
			if (p_Instance)
			{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("spawned= %f wave= %f"), p_Instance->g_CurrentWaveSpawnedEnemies, p_Instance->g_Wave));
				if (p_Instance->g_CurrentWaveSpawnedEnemies < (p_Instance->g_WaveSet * StartEnemyNumber) +  (((FMath::Fmod(p_Instance->g_Wave, 10.f) - 1) *EachWaveIncreaseEnemy)))
				{
					if (FMath::Fmod(p_Instance->g_MinionsSpawned, 10.f) == 0 && p_Instance->g_MinionsSpawned > 1)
					{
						AEnemyCharacter* SpawnedEnemy = world->SpawnActor<AEnemyCharacter>(KnightToSpawn, SpawnLocation, SpawnRotator, SpawnParameters);						
						SpawnedEnemy->SetClassID(3, p_Instance->g_WaveSet);
						SpawnedEnemy->SetType(enemyType);
						p_Instance->g_KnightSpawned++;
						p_Instance->g_MinionsSpawned++;
						//attach AI controller
						SpawnedEnemy->SpawnDefaultController();
					}
					else if (FMath::Fmod(p_Instance->g_FodderSpawned, 10.f) == 0 && p_Instance->g_FodderSpawned > 1)
					{
						AEnemyCharacter* SpawnedEnemy = world->SpawnActor<AEnemyCharacter>(MinionToSpawn, SpawnLocation, SpawnRotator, SpawnParameters);						
						SpawnedEnemy->SetClassID(2, p_Instance->g_WaveSet);
						SpawnedEnemy->SetType(enemyType);
						p_Instance->g_MinionsSpawned++;
						p_Instance->g_FodderSpawned++;
						
						//attach AI controller
						SpawnedEnemy->SpawnDefaultController();
					}
					else
					{
						AEnemyCharacter* SpawnedEnemy = world->SpawnActor<AEnemyCharacter>(FodderToSpawn, SpawnLocation, SpawnRotator, SpawnParameters);
						SpawnedEnemy->SetClassID(1, p_Instance->g_WaveSet);
						SpawnedEnemy->SetType(enemyType);
						p_Instance->g_FodderSpawned++;
						//attach AI controller
						SpawnedEnemy->SpawnDefaultController();
					}
					enemiesSpawned++;

					SpawnDelay = FMath::FRandRange(SpawnDelayMin, SpawnDelayMax);
					p_Instance->g_TotalEnemies++;
					p_Instance->g_CurrentWaveSpawnedEnemies++;
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Spawned= %d Gold= %d"), (FMath::Fmod(p_Instance->g_Wave, 10.f) - 1), (p_Instance->g_WaveSet * StartEnemyNumber)));
					
				}
				GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnEnemy, SpawnDelay, false);
			}
		}
	}
}

//void ASpawnVolume::DestroyEnemy(AEnemyCharacter* i_pEnemy)
//{
//	i_pEnemy->GetController()->Destroy();
//	i_pEnemy->Destroy();
//	p_Instance->g_CurrentWaveDestroyedEnemies++;
//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Destroyed");
//
//	if (p_Instance->g_CurrentWaveDestroyedEnemies == p_Instance->g_CurrentWaveEnemies)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Wave Complete");
//		p_Instance->IncreaseWave();
//		BeginNewWave();
//	}
//}

void ASpawnVolume::BeginNewWave()
{
	enemiesSpawned = 0;
	SpawnDelay = FMath::FRandRange(SpawnDelayMin, SpawnDelayMax);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnEnemy, SpawnDelay, false);
}

//void ASpawnVolume::DestroyEnemy(TArray<AEnemyCharacter*> i_pEnemyArray)
//{
//	for (int i = 0; i > i_pEnemyArray.Num; i++)
//	{
//		i_pEnemyArray[i]->GetController()->Destroy();
//		i_pEnemyArray[i]->Destroy();
//		p_Instance->g_CurrentWaveDestroyedEnemies++;
//		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Destroyed");
//
//		if (p_Instance->g_CurrentWaveDestroyedEnemies == p_Instance->g_CurrentWaveEnemies)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Wave Complete");
//			p_Instance->IncreaseWave();
//		}
//	}
//}
