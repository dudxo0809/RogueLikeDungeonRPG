// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../MonsterInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TargetTrace.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API UBTTask_TargetTrace : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_TargetTrace();

protected:
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual EBTNodeResult::Type AbortTask(
		UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, float DeltaSeconds);

	/** called when task execution is finished
	 * this function should be considered as const (don't modify state of object) if node is not instanced!
	 * bNotifyTaskFinished must be set to true for this function to be called
	 * Calling INIT_TASK_NODE_NOTIFY_FLAGS in the constructor of the task will set this flag automatically */
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory, EBTNodeResult::Type TaskResult);
};
