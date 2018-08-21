// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "EnemyAI.h"
#include "MyProjectCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyProjectPlayerController.h"
#include "MyProject.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AIControllerClass = AEnemyAI::StaticClass();
}

void AEnemyCharacter::SetClassID(uint8 i_ID, float i_waveSet)
{
	//for push
	classID = i_ID;

	if (classID == 1)
	{
		health = 25.f + (i_waveSet - 1)*5.f;
		SetWalkSpeed(500.f);
		SetAcceptanceRadius(50.f);		
	}
	else if (classID == 2)
	{
		health = 50.f + (i_waveSet - 1)*10.f;
		SetWalkSpeed(350.f);
		SetAcceptanceRadius(150.f);
	}
	else
	{
		health = 100.f + (i_waveSet - 1)*20.f;
		SetWalkSpeed(150.f);
		SetAcceptanceRadius(200.f);
	}
}

void AEnemyCharacter::SetWalkSpeed(float i_Speed)
{
	speed = i_Speed;
	GetCharacterMovement()->MaxWalkSpeed = speed;
}

void AEnemyCharacter::SetType(EEnemyType i_type)
{
	MyType = i_type;
	if (MyType == EEnemyType::Fire)
	{
		health += 1;
		SetWalkSpeed(GetWalkSpeed() + 1);
	}
	else if (MyType == EEnemyType::Water)
	{
		health += 1;
		SetWalkSpeed(GetWalkSpeed() + 1);
	}
	else if (MyType == EEnemyType::Earth)
	{
		health += 1;
		SetWalkSpeed(GetWalkSpeed() + 1);
	}
	else if (MyType == EEnemyType::Wind)
	{
		health += 1;
		SetWalkSpeed(GetWalkSpeed() + 1);
	}
}

void AEnemyCharacter::SetAcceptanceRadius(float i_Radius)
{
	acceptanceRadius = i_Radius;
}

void AEnemyCharacter::SetHealth(float i_health)
{
	health = i_health;
}

uint8 AEnemyCharacter::GetClassID()
{
	return classID;
}

float AEnemyCharacter::GetWalkSpeed()
{
	return speed;
}

float AEnemyCharacter::GetAcceptanceRadius()
{
	return acceptanceRadius;
}

float AEnemyCharacter::GetHealth()
{
	return health;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	p_GameInstance = Cast<UMyCustomGameInstance>(GetGameInstance());
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	/*float i_Roll;
	float i_Pitch;
	float i_Yaw;
	*/
	Super::Tick(DeltaTime);
	/*
	if (GetWorld())
	{
		if (GetWorld()->GetFirstPlayerController())
		{
			FRotator newRotator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetOwner()->GetActorLocation());

			UKismetMathLibrary::BreakRotator(newRotator, i_Roll, i_Pitch, i_Yaw);
			i_Yaw -= 90.f;
			if (this->GetMesh())
			{
				this->GetMesh()->SetWorldRotation(UKismetMathLibrary::MakeRotator(i_Pitch, i_Roll, i_Yaw));
			}
		}
	}
	*/
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::SpawnDefaultController()
{
	Super::SpawnDefaultController();
}

float AEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AEnemyCharacter::TakeDamageOverTime(float i_damageTime, float i_damage)
{
	while (i_damageTime != 0)
	{
		if(health > 0)
		{
			health -= i_damage;
			i_damageTime--;
		}
	}
}

void AEnemyCharacter::EnemyHit(float i_damage)
{	
	SetHealth(health - i_damage);
	if (health <= 0.f)
	{
		if (this->classID ==3)
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemyCharacter::DestroyActor, 3.5f, false);
		else
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemyCharacter::DestroyActor, 1.5f, false);
	}
}

void AEnemyCharacter::DestroyActor()
{
	if (p_GameInstance)
	{
		switch (this->classID)
		{
		case 1: 		
			p_GameInstance->g_WaveSetGold += 50;
			p_GameInstance->g_IndividualWaveGold += 50;
			break;
		case 2:
			p_GameInstance->g_WaveSetGold += 500;
			p_GameInstance->g_IndividualWaveGold += 500;
			break;
		case 3:
			p_GameInstance->g_WaveSetGold += 5000;
			p_GameInstance->g_IndividualWaveGold += 5000;
			break;
		default:
			p_GameInstance->g_WaveSetGold += 100;
			break;
		}
		this->Destroy();
		p_GameInstance->g_CurrentWaveDestroyedEnemies++;		
	}
}

//void AEnemyCharacter::AllKilled()
//{
//	APlayerController* p_PlayerController = GetWorld()->GetFirstPlayerController();
//
//	if (p_PlayerController)
//	{
//		AMyProjectPlayerController *p_MyPlayerCon = Cast<AMyProjectPlayerController>(p_PlayerController);
//		if (p_MyPlayerCon)
//		{
//			if (p_GameInstance)
//			{
//				if (p_GameInstance->g_CurrentWaveDestroyedEnemies == 10)
//				{
//					p_MyPlayerCon->p_BetweenWavesUI->SetMoney(p_GameInstance->g_Gold);
//					p_MyPlayerCon->p_BetweenWavesUI->SetMoney(p_MyPlayerCon->p_BetweenWavesUI->GetMoney() + p_GameInstance->g_CurrentWaveDestroyedEnemies);
//					p_MyPlayerCon->p_BetweenWavesUI->AddToViewport();
//					p_MyPlayerCon->SetPause(true);
//				}
//			}			
//		}
//	}
//}