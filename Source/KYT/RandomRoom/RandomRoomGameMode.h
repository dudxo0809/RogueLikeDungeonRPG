// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../KYTGameModeBase.h"


#include "RandomRoomGameMode.generated.h"

/**
 * 
 */
class ARoomBase;

class CRoomData;
class CFloorData;

class UDungeonSaveGame;

UCLASS()
class KYT_API ARandomRoomGameMode : public AKYTGameModeBase
{
	GENERATED_BODY()
	


public:
	ARandomRoomGameMode();



private:

	UDungeonSaveGame* mSaveGame;

	int32 mStageNum;

private:

	CFloorData* mFloorData;

	TArray<TSubclassOf<ARoomBase>>	m_RoomBaseClass;
	TArray<ARoomBase*> mRoomBaseArray;

	TSubclassOf<ARoomBase>	m_RoomInitClass;
	ARoomBase* mRoomInit;

	TSubclassOf<ARoomBase>	m_RoomBossClass;
	ARoomBase* mRoomBoss;


private:

	FVector2D mBossRoomPos;



public:
	virtual void BeginPlay()	override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void Tick(float DeltaTime)	override;


public:

	FVector2D GetBossRoomPosition();

public:

	UDungeonSaveGame* CreateSaveGame();
	void SaveGame(int32 SaveIndex);

public:

	void SetStageNumber(int32 Num)
	{
		mStageNum = Num;
	}

	int32 GetStageNumber()
	{
		return mStageNum;
	}

};
