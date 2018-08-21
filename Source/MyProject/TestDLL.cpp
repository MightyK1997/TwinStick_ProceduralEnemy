// Fill out your copyright notice in the Description page of Project Settings.

#include "TestDLL.h"

typedef int(*_GetDamage) (FString name);

_GetDamage m_getInvertedBoolFromDll;

void *v_dllHandle;

bool UTestDLL::importDLL(FString folder, FString name)
{
	FString filePath = "C:/Users/u1141916/Documents/Twinstick/Orochi_Studios/TwinStick_ProceduralEnemy/Plugins/TestUhrealClassLibrary.dll";
	if (FPaths::FileExists(filePath))
	{
		//return true;
		v_dllHandle = FPlatformProcess::GetDllHandle(*filePath);
		if (v_dllHandle != NULL)
		{
			return true;
		}
	}
	return false;
}

bool UTestDLL::importMethodGetDamage()
{
	if (v_dllHandle != NULL)
	{
		m_getInvertedBoolFromDll = NULL;
		FString procName = "GetDamage";
		m_getInvertedBoolFromDll = (_GetDamage)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_getInvertedBoolFromDll != NULL)
		{
			return true;
		}
	}
	return false;
}

int UTestDLL::GetDamage(FString name)
{
	if (m_getInvertedBoolFromDll != NULL)
	{
		int out = int(m_getInvertedBoolFromDll(name));
		return out;
	}
	return -32202;
}


void UTestDLL::freeDLL()
{
	if (v_dllHandle != NULL)
	{
		v_dllHandle = NULL;
	}
}