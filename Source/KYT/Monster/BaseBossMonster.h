// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMonster.h"
#include "../RandomRoom/RoomBase.h"

#include "BaseBossMonster.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API ABaseBossMonster : public ABaseMonster
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ABaseBossMonster();





private:

	float mNextStageTime;
	float mNextStageCurrentTime;
	

	bool bLevelTrigerSpawn;

	ARoomBase* mBossRoom;



public:

	void SetRoom(ARoomBase* BossRoom) {

		mBossRoom = BossRoom;
	}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();


};
