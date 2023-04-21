// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "EngineGlobals.h"
#include "Engine.h"


#include "DrawDebugHelpers.h"


#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSoundComponent.h"
#include "MediaSource.h"




#include "GameInfo.generated.h"
/**
 * 
 */




UENUM()
enum class EPlayerAttribute : uint8 {

	Arcane = 0,

	Fire,
	Ice,
	Thunder,
	Poison,

	Holy,
	Shadow,

	Void

};





UCLASS()
class KYT_API UGameInfo : public UObject
{
	GENERATED_BODY()

};
