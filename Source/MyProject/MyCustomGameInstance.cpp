// Fill out your copyright notice in Description page of Project Settings.

#include "MyCustomGameInstance.h"
#include "MyProjectCharacter.h"
#include "MyProjectPlayerController.h"
#include "MyProject.h"



UMyCustomGameInstance::UMyCustomGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	g_CurrentWaveSpawnedEnemies = 0.0;
	g_CurrentWaveDestroyedEnemies = 0.0;
	g_TotalEnemies = 0.0;
	g_Wave = 1.f;
	g_WaveSet = 1.0;
	g_Gold = 0.0;
	g_CurrentEnemiesToSpawn = g_WaveSet * 5.0 + (((FMath::Fmod(g_Wave, 10.0)) - 1.0f) * 3.0f);
}

float UMyCustomGameInstance::GetCurrentWave()
{
	return g_Wave;
}

void UMyCustomGameInstance::SetCurrentWave(float i_wave)
{
	g_Wave = i_wave;
}

void UMyCustomGameInstance::ChangeStats(float i_wave, float i_gold)
{
	SetCurrentWave(i_wave);
	g_Gold = i_gold;
}

float UMyCustomGameInstance::GetTotalGold()
{
	return g_Gold;
}

void UMyCustomGameInstance::IncreaseWave()
{
	g_IndividualWaveGold = 0;
	g_Wave++;
	if (FMath::Fmod(g_Wave, 10) == 0)
	{		
		g_WaveSet++;
		g_Gold += g_WaveSetGold;
		g_WaveSetGold = 0.f;

		if (FMath::Fmod(g_WaveSet, 4) == 0)
			ChangeMap("Procedural_Spring");
		else if (FMath::Fmod(g_WaveSet, 3) == 0)
			ChangeMap("Procedural_Winter");
		else if (FMath::Fmod(g_WaveSet, 2) == 0)
			ChangeMap("Procedural_Fall");
		else
			ChangeMap("Procedural_Summer");
	}

	g_CurrentWaveSpawnedEnemies = 0;
	g_CurrentWaveDestroyedEnemies = 0;

}

void UMyCustomGameInstance::Init()
{
	Super::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyCustomGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMyCustomGameInstance::EndLoadingScreen);
}

void UMyCustomGameInstance::BeginLoadingScreen(const FString& InMapName)
{
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
		if (LoadingScreen.IsValid())
		{
			LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
			/*LoadingScreen.MoviePaths = "v.mp4";*/
		}
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void UMyCustomGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
	int32 test = 0;
}

void UMyCustomGameInstance::ShowWidget()
{
	//AMyProjectPlayerController* p_Controller = Cast<AMyProjectPlayerController>(GetPrimaryPlayerController());
	//int i = 1;
	//if (p_Controller)
	//		p_Controller->UpdateCollectedItems();
}

void UMyCustomGameInstance::ChangeMap(const char* i_map)
{
	UGameplayStatics::OpenLevel((UObject*)this, FName(i_map));
}

