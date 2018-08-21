// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestDLL.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UTestDLL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MyDLL")
		static bool importDLL(FString folder, FString name);
	UFUNCTION(BlueprintCallable, Category = "MyDLL")
		static void freeDLL();
	UFUNCTION(BlueprintCallable, Category = "MyDLL")
		static bool importMethodGetDamage();
	UFUNCTION(BlueprintCallable, Category = "MyDLL")
		static int GetDamage(FString name);
};
