// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "BetweenWavesWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UBetweenWavesWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UBetweenWavesWidget(const FObjectInitializer& ObjectInitializer);

protected:
	//UFUNCTION(BlueprintImplementableEvent, Category = UI)
	//	void AddItemToUI();
	//for push

	UFUNCTION(BlueprintCallable, Category = UI)
	void SetWaveStats();

	UFUNCTION(BlueprintCallable, Category = UI)
	void ResumeFromPause();

	UFUNCTION(BlueprintCallable, Category = UI)
	void ShowWidget();

	UFUNCTION(BlueprintCallable, Category = UI)
	void BackToTown();

	UFUNCTION(BlueprintCallable, Category = UI)
	void PlayerDead();

	UPROPERTY(BlueprintReadOnly)
	FText ItemToAdd;

	UPROPERTY(BlueprintReadOnly)
	bool isPaused = false;

	UPROPERTY(BlueprintReadOnly)
	float kills;

	UPROPERTY(BlueprintReadOnly)
	float money = 50.f;

	


public:
	void AddItemToUI(FText item);
	void SetPauseState(bool i_Pause);
	bool GetPauseState();
	void SetVisibleInViewport(bool i_Viewport);
	bool GetVisibleInViewport();
	float GetMoney();
	float GetKills();
	void SetMoney(float i_money);
	void SetKills(float i_kills);

private:
	bool visibleInViewport;

};