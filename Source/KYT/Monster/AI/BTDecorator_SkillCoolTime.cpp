// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_SkillCoolTime.h"


#include "../MonsterAIController.h"
#include "../BaseMonster.h"
#include "../BossMonsterRampage.h"


UBTDecorator_SkillCoolTime::UBTDecorator_SkillCoolTime()
{
}



// BossMonster의 Skill CoolTime을 계산해서 
// 참, 거짓 반환
// 
// 스킬중 하나라도 사용가능하면 True 반환
// 
//
bool UBTDecorator_SkillCoolTime::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);


	// GetAIOwner() : UBehaviorTreeComponent를 가지고 있는
	// AIController를 얻어올 수 있다.
	AMonsterAIController* Controller =
		Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(Controller))
		return EBTNodeResult::Failed;

	ABossMonsterRampage* Boss = Cast<ABossMonsterRampage>(Controller->GetPawn());

	if (!IsValid(Boss))
		return false;

	// Rampage의 스킬 쿨타임 Load
	int32 SkillNum = Boss->mSkillCoolTime.Num();

	for (int32 i = 0; i < SkillNum; i++)
	{
		if (Boss->mSkillCoolTime[i] <= Boss->mSkillCoolCurrentTime[i])
			return true;
	}


	return false;
}
