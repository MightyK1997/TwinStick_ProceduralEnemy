// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTask_MoveToPlayer.h"
#include "MyProject.h"
#include "EnemyAI.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "MyProjectCharacter.h"


EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//for push
	p_Enemy = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	p_Player = Cast<AMyProjectCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(p_Enemy->enemyKeyID));

	if (p_Player)
	{
		AEnemyCharacter *p_EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (p_EnemyCharacter->health >0)
			p_Enemy->MoveToActor(p_Player, acceptanceRadius, true, true, true, 0, true);

		distance = FMath::Sqrt(FMath::Square(p_Player->GetActorLocation().X - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation().X) +
			FMath::Square(p_Player->GetActorLocation().Y - p_EnemyCharacter->GetActorLocation().Y));

		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::SanitizeFloat(distance));
		if (distance < 400.f)
		{
			acceptanceRadius = 20.f;			
		}
		else
		{
			acceptanceRadius = 400.f;
		}
		OnTaskFinished(OwnerComp, NodeMemory, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		OnTaskFinished(OwnerComp, NodeMemory, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	OnTaskFinished(OwnerComp, NodeMemory, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;		
}

void UBTTask_MoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::SanitizeFloat(DeltaSeconds));
}

void UBTTask_MoveToPlayer::ChangeAcceptanceRadius()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Start New Task");
	acceptanceRadius = 20.f;
	
}

void UBTTask_MoveToPlayer::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{	
	
	if (acceptanceRadius == 20.f)
	{
		AEnemyCharacter *p_EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (p_EnemyCharacter)
		{
			distance = FMath::Sqrt(FMath::Square(p_Player->GetActorLocation().X - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation().X) +
				FMath::Square(p_Player->GetActorLocation().Y - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation().Y));
			if (distance < 100)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Setting attack");
				p_EnemyCharacter->isAttacking = true;
				acceptanceRadius = 5.f;
			}
			else
			{
				p_EnemyCharacter->isAttacking = false;
			}
			
		}
	}	
}





