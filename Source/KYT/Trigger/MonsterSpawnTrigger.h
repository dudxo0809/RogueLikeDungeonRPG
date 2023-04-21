// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BaseTrigger.h"

#include "MonsterSpawnTrigger.generated.h"

/**
 * 
 */

UENUM()
enum class EMonsterSpawnPos : int32 {

	Min = -1000,
	Max = 1000

};


UENUM()
enum class EMonsterSpawnNumber : int32 {

	Min = 5,
	Max = 10

};

class ARoomBase;

UCLASS()
class KYT_API AMonsterSpawnTrigger : public ABaseTrigger
{
	GENERATED_BODY()

public:
	AMonsterSpawnTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TArray<UClass*> mMonsterClassArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ARoomBase* mRoom;


private:

	int32 mStageNum;



public:
	//UFUNCTION(BlueprintCallable)
//	void AddMonsterSpawnPoint(AMonsterSpawnPoint* SpawnPoint);

	void SetRoom(ARoomBase* Room)
	{
		mRoom = Room;
	}

public:
	virtual void TriggerBegin(const FHitResult& SweepResult, AActor* OtherActor);
	virtual void TriggerEnd();
};
