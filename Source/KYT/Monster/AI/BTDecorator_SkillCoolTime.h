// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_SkillCoolTime.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API UBTDecorator_SkillCoolTime : public UBTDecorator
{
	GENERATED_BODY()
	

public:
	UBTDecorator_SkillCoolTime();

protected:
	


protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

};
