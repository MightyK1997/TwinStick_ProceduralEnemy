// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckForPlayer.h"
#include "EnemyAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "MyProject.h"
#include "MyProjectCharacter.h"


UBTService_CheckForPlayer::UBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;		//for multiple instances
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyAI *p_EnemyPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	if (p_EnemyPC)
	{
		//check if the player is in the world
		AMyProjectCharacter *p_Player = Cast<AMyProjectCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (p_Player)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object> (p_EnemyPC->enemyKeyID, p_Player);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Enemy is here");
		}
		
	}

}




