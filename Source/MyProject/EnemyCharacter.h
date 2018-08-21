// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCustomGameInstance.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"
UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Fire	UMETA(DisplayName = "Fire"),
	Water	UMETA(DisplayName = "Water"),
	Earth	UMETA(DisplayName = "Earth"),
	Wind	UMETA(DisplayName = "Wind")
};

UCLASS()
class MYPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	//getter-setter
	void SetClassID(uint8 id, float i_waveSet);
	void SetWalkSpeed(float i_Speed);
	void SetAcceptanceRadius(float i_Radius);
	void SetHealth(float i_health);
	void SetType(EEnemyType i_type);

	uint8 GetClassID();
	float GetWalkSpeed();
	float GetAcceptanceRadius();
	float GetHealth();

	FTimerHandle SpawnTimer;

	UFUNCTION(BlueprintCallable, Category = Damage)
	void EnemyHit(float damage);

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void TakeDamageOverTime(float i_damageTime, float i_damage);

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree *p_EnemyBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	bool isAttacking;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Behavior)
	float health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Behavior)
	EEnemyType MyType;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SpawnDefaultController() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);
	void DestroyActor();
	UMyCustomGameInstance* p_GameInstance;

private:
	//enemy characteristics
	uint8 classID;
	float speed = 0.0f;
	float acceptanceRadius = 0.0f;
};
