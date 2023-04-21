// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BaseTrigger.h"

#include "../RandomRoom/RoomBase.h"

#include "BossSpawnTrigger.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API ABossSpawnTrigger : public ABaseTrigger
{
	GENERATED_BODY()

public:
	ABossSpawnTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<UClass*> mMonsterClassArray;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ARoomBase* mRoom;


public:
	

	void SetRoom(ARoomBase* Room)
	{
		mRoom = Room;
	}


public:
	virtual void TriggerBegin(const FHitResult& SweepResult, AActor* OtherActor);
	virtual void TriggerEnd();
};
