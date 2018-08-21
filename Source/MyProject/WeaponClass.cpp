// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponClass.h"


// Sets default values
AWeaponClass::AWeaponClass()
{
	damage = 0;
	weaponName = 0;
	className = 0;
	numberOfMultiHitEnemies = 0;
	speed = 0;
	criticalAttack = 0;
	weaponXP = 0;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponClass::BeginPlay()
{
	Super::BeginPlay();
	
}

AWeaponClass* AWeaponClass::AWeaponClass::GetWeaponDetails()
{
	return this;
}

// Called every frame
void AWeaponClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

