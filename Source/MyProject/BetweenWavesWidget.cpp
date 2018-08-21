#include "BetweenWavesWidget.h"
#include "MyProjectPlayerController.h"
#include "MyCustomGameInstance.h"
#include "MyProject.h"

UBetweenWavesWidget::UBetweenWavesWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UBetweenWavesWidget::SetWaveStats()
{

}

void UBetweenWavesWidget::ResumeFromPause()
{	
	//for push
	//SetPauseState(false);
	//SetVisibleInViewport(false);
	RemoveFromViewport();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "pause");

	APlayerController* p_PlayerController = GetWorld()->GetFirstPlayerController();

	if (p_PlayerController)
	{
		AMyProjectPlayerController *p_con = Cast<AMyProjectPlayerController>(p_PlayerController);
		if (p_con)
		{
			UMyCustomGameInstance *p = Cast<UMyCustomGameInstance>(p_con->GetGameInstance());
			if (p)
			{				
				p->IncreaseWave();
			}
			if (p_PlayerController)
			{			
				p_con->SetPause(false);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "resume");
			}
		}
	}	
}

void UBetweenWavesWidget::AddItemToUI(FText i_text)
{
	//ItemToAdd = new FText("!@#!#@!");
	//AddItemToUI();
}

void UBetweenWavesWidget::SetPauseState(bool i_Pause)
{
	isPaused = i_Pause;
}

bool UBetweenWavesWidget::GetPauseState()
{
	return isPaused;
}

float UBetweenWavesWidget::GetMoney()
{
	return money;
}

void UBetweenWavesWidget::SetMoney(float i_money)
{
	money = i_money;
}

float UBetweenWavesWidget::GetKills()
{
	return kills;
}

void UBetweenWavesWidget::SetKills(float i_kills)
{
	kills = i_kills;
}

void UBetweenWavesWidget::SetVisibleInViewport(bool i_Viewport)
{
	visibleInViewport = i_Viewport;
	AddToViewport();
}

void UBetweenWavesWidget::ShowWidget()
{
	APlayerController* p_PlayerController = GetWorld()->GetFirstPlayerController();

	if (p_PlayerController)
	{
		AMyProjectPlayerController *p_con = Cast<AMyProjectPlayerController>(p_PlayerController);
		if (p_con)
		{
			UMyCustomGameInstance *p = Cast<UMyCustomGameInstance>(p_con->GetGameInstance());
			if (p)
			{
				SetMoney(p->g_IndividualWaveGold);
				
				SetKills(GetKills() + p->g_CurrentWaveDestroyedEnemies);
				AddToViewport();
			}
			if (p_PlayerController)
			{
				p_con->SetPause(true);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "resume");
			}
		}
	}
}

void UBetweenWavesWidget::PlayerDead()
{
	//for push
	SetPauseState(false);
	SetVisibleInViewport(false);
	RemoveFromViewport();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "back from dead");

	APlayerController* p_PlayerController = GetWorld()->GetFirstPlayerController();

	if (p_PlayerController)
	{
		AMyProjectPlayerController *p_con = Cast<AMyProjectPlayerController>(p_PlayerController);
		if (p_con)
		{
			UMyCustomGameInstance *p = Cast<UMyCustomGameInstance>(p_con->GetGameInstance());
			if (p)
			{
				if (FMath::Fmod(p->GetCurrentWave(), 10) < 9.f)
				{
					p->SetCurrentWave(p->GetCurrentWave() - FMath::Fmod(p->GetCurrentWave(), 10));
				}	
				p->g_WaveSetGold = p->g_Gold;				
				p->IncreaseWave();	
				p->ChangeMap("TownTestLevel");				
			}			
		}
	}
}

bool UBetweenWavesWidget::GetVisibleInViewport()
{
	return visibleInViewport;
}

void UBetweenWavesWidget::BackToTown()
{
	//for push
	SetPauseState(false);
	SetVisibleInViewport(false);
	RemoveFromViewport();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "pause");

	APlayerController* p_PlayerController = GetWorld()->GetFirstPlayerController();

	if (p_PlayerController)
	{
		AMyProjectPlayerController *p_con = Cast<AMyProjectPlayerController>(p_PlayerController);
		if (p_con)
		{
			UMyCustomGameInstance *p = Cast<UMyCustomGameInstance>(p_con->GetGameInstance());
			if (p)
			{
				if (FMath::Fmod(p->GetCurrentWave(), 10) < 9.f)
				{
					p->SetCurrentWave(p->GetCurrentWave() - FMath::Fmod(p->GetCurrentWave(), 10));
				}
				p->g_Gold += p->g_WaveSetGold;					//saving gold
				p->IncreaseWave();
				p->g_WaveSetGold = 0.f;
				p->ChangeMap("TownTestLevel");
			}
			if (p_PlayerController)
			{
				//p_con->UpdateInstanceParameters();
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "resume");
			}
		}
	}
}

