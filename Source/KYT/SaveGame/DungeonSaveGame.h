// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Character/CharacterInfo.h"

#include "GameFramework/SaveGame.h"
#include "DungeonSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API UDungeonSaveGame : public USaveGame
{
	GENERATED_BODY()

	friend class ARandomRoomGameMode;

private:

	UPROPERTY()
	FPlayerCharacterInfo mPlayerInfo;

	UPROPERTY()
	TArray<bool> mSkillEnable;

	UPROPERTY()
	int32 mSkillEffectAttributeIndex;

private:

	UPROPERTY()
	int32 mStageNum;

public:



};
