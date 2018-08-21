// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject.h"
#include "EnemyAI.h"
#include "MyProjectCharacter.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UBTTask_MoveToPlayer : public UBTTask_BlackboardBase
{
	//for push
	GENERATED_BODY()		

public:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory) override;
		virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
		virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
		void ChangeAcceptanceRadius();

private:
	float acceptanceRadius = 400.f;
	FTimerHandle SpawnTimer;
	AEnemyAI *p_Enemy;
	float distance = 101.f;

	AMyProjectCharacter *p_Player;
};
