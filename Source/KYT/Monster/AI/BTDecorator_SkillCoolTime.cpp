// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_SkillCoolTime.h"


#include "../MonsterAIController.h"
#include "../BaseMonster.h"
#include "../BossMonsterRampage.h"


UBTDecorator_SkillCoolTime::UBTDecorator_SkillCoolTime()
{
}



// BossMonster�� Skill CoolTime�� ����ؼ� 
// ��, ���� ��ȯ
// 
// ��ų�� �ϳ��� ��밡���ϸ� True ��ȯ
// 
//
bool UBTDecorator_SkillCoolTime::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);


	// GetAIOwner() : UBehaviorTreeComponent�� ������ �ִ�
	// AIController�� ���� �� �ִ�.
	AMonsterAIController* Controller =
		Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(Controller))
		return EBTNodeResult::Failed;

	ABossMonsterRampage* Boss = Cast<ABossMonsterRampage>(Controller->GetPawn());

	if (!IsValid(Boss))
		return false;

	// Rampage�� ��ų ��Ÿ�� Load
	int32 SkillNum = Boss->mSkillCoolTime.Num();

	for (int32 i = 0; i < SkillNum; i++)
	{
		if (Boss->mSkillCoolTime[i] <= Boss->mSkillCoolCurrentTime[i])
			return true;
	}


	return false;
}
