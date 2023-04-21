// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseTrigger.h"
#include "LevelTrigger.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API ALevelTrigger : public ABaseTrigger
{
	GENERATED_BODY()

public:
	ALevelTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FName	mLevelName;


public:
	virtual void TriggerBegin(const FHitResult& SweepResult, AActor* OtherActor);
	virtual void TriggerEnd();

public:
	void SetLevel(FName LevelName) {

		mLevelName = LevelName;
	}


public:



};
