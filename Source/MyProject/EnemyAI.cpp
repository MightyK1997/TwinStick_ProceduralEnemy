// Fill out your copyright notice in the Description page of Project Settings.
//#include "AIEssentials.h"

#include "EnemyAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "MyProject.h"

AEnemyAI::AEnemyAI()
{
	p_BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	p_BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void AEnemyAI::Possess(APawn *i_InPawn)
{
	Super::Possess(i_InPawn);
	AEnemyCharacter *p_character = Cast<AEnemyCharacter>(i_InPawn);

	if (p_character && p_character->p_EnemyBehavior)
	{
		SetAcceptanceRadius(p_character->GetAcceptanceRadius());
		p_BlackboardComp->InitializeBlackboard(*p_character->p_EnemyBehavior->BlackboardAsset);
		enemyKeyID = p_BlackboardComp->GetKeyID("Target");
		p_BehaviorComp->StartTree(*p_character->p_EnemyBehavior);
	}
}

void AEnemyAI::SetAcceptanceRadius(float i_radius)
{
	acceptanceRadius = i_radius;
}

//void AEnemyAI::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
//{
//	Super::UpdateControlRotation(DeltaTime, bUpdatePawn);
//
//	FVector focalPoint = GetFocalPoint();
//	if (!focalPoint.IsZero() && GetPawn())
//	{
//		FVector direction = focalPoint - GetPawn()->GetActorLocation();
//		FRotator newRotator = direction.Rotation();
//
//		newRotator.Yaw = FRotator::ClampAxis(newRotator.Yaw);
//		SetControlRotation(newRotator);
//
//		APawn* const p = GetPawn();
//
//		if (p && bUpdatePawn)
//		{
//			p->FaceRotation(newRotator, DeltaTime);
//		}
//	}
//}

float AEnemyAI::GetAcceptanceRadius()
{
	return acceptanceRadius;
}




