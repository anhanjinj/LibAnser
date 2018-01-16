// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogicUtile.generated.h"


#define LOG_ONSCREEN(FStr, ShowTime, Color) { GEngine->AddOnScreenDebugMessage(-1, ShowTime, Color, FStr);}



/**
 * 
 */
UCLASS(Blueprintable)
class ULogicUtile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

		
		
};
