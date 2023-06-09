// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MonsterInfo.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckDistance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECheckDistanceType : uint8
{
	Attack,
	Trace
};


UCLASS()
class KYT_API UBTDecorator_CheckDistance : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckDistance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		ECheckDistanceType	mCheckType;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
