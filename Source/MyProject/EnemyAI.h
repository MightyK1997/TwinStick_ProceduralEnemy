// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemyAI : public AAIController
{
	//for push
	GENERATED_BODY()

		UPROPERTY(transient)
		class UBlackboardComponent *p_BlackboardComp;

	UPROPERTY(transient)
		class UBehaviorTreeComponent *p_BehaviorComp;

public:

	AEnemyAI();
	virtual void Possess(APawn *i_InPawn) override;
	//virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;
	
	void SetAcceptanceRadius(float i_radius);
	float GetAcceptanceRadius();

	uint8 enemyKeyID;

private:
	float acceptanceRadius;
};
