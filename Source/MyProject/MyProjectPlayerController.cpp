// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyProjectPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MyProjectCharacter.h"


AMyProjectPlayerController::AMyProjectPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMyProjectPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	
}

void AMyProjectPlayerController::SetupInputComponent()
{
	// set up game play key binding
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMyProjectPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMyProjectPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyProjectPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMyProjectPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AMyProjectPlayerController::OnResetVR);
}

void AMyProjectPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMyProjectPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AMyProjectCharacter* MyPawn = Cast<AMyProjectCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UNavigationSystem::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AMyProjectPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMyProjectPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AMyProjectPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMyProjectPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void AMyProjectPlayerController::UpdateInstanceParameters()
{	
	//update widget variables
	if (p_Instance && BetweenWavesUI_BP)
	{
		if (p_Instance->g_CurrentWaveDestroyedEnemies == p_Instance->g_Wave * 10 && p_Instance->g_TotalEnemies != 0)
		{
			p_BetweenWavesUI->SetPauseState(true);
			p_BetweenWavesUI->SetVisibleInViewport(true);
		}
		else
		{
			p_BetweenWavesUI->SetPauseState(false);
			p_BetweenWavesUI->SetVisibleInViewport(false);
		}
	}

	//Show widget components on screen
	if (BetweenWavesUI_BP)
	{
		this->SetPause(p_BetweenWavesUI->GetPauseState());

		if (p_BetweenWavesUI->GetVisibleInViewport())
		{
			if (!(p_BetweenWavesUI->IsInViewport()))
			{
				p_BetweenWavesUI->AddToViewport();
			}
				
		}
		else
			p_BetweenWavesUI->RemoveFromViewport();
	}
}

void AMyProjectPlayerController::Possess(APawn* i_Pawn)
{
	Super::Possess(i_Pawn);
	/*p_Instance = Cast<UMyCustomGameInstance>(GetGameInstance());
	if (BetweenWavesUI_BP)
	{
		p_BetweenWavesUI = CreateWidget<UBetweenWavesWidget>(this, BetweenWavesUI_BP);
	}*/
}

void AMyProjectPlayerController::UpdateCollectedItems(FText i_Text)
{
	AMyProjectCharacter* p_character = Cast<AMyProjectCharacter>(GetPawn());
	if (p_character)
	{
		p_BetweenWavesUI->AddItemToUI(i_Text);
	}
}

