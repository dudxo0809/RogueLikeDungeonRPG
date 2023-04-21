// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Skill.h"

#include "../MonsterAIController.h"
#include "../BaseMonster.h"
#include "../../Character/BasePlayerCharacter.h"
#include "../MonsterAnimInstance.h"

#include "../BossMonsterRampage.h"



UBTTask_Skill::UBTTask_Skill()
{
	NodeName = TEXT("Skill");
	bNotifyTick = true;
	bNotifyTaskFinished = true;

	mSkillNum = 0;
}

EBTNodeResult::Type UBTTask_Skill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp,
		NodeMemory);

	AMonsterAIController* Controller =
		Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(Controller))
		return EBTNodeResult::Failed;

	ABossMonsterRampage* Boss = Cast<ABossMonsterRampage>(Controller->GetPawn());

	if (!IsValid(Boss))
		return EBTNodeResult::Failed;

	UMonsterAnimInstance* Anim = Boss->GetMonsterAnimInst();

	// Blackboard�� ����� Target�� ���;� �Ѵ�.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		// �̵��� �����.
		Controller->StopMovement();

		// �ִϸ��̼��� Idle�� ��ȯ�Ѵ�.
		Anim->ChangeAnim(EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	// Skill ���� �ҷ�����

	int32 AttackAnimNum = 0;

	for (int32 i = 0; i < 3; i++) {

		if (Boss->mSkillCoolTime[i] <= Boss->mSkillCoolCurrentTime[i]) 
		{
			AttackAnimNum = i + 1;
		}
	}

	mSkillNum = AttackAnimNum;

	switch (AttackAnimNum) {


	case 0:
		Anim->ChangeAnim(EMonsterAnimType::Idle);
		return EBTNodeResult::Failed;

		break;

	case 1:
		Anim->ChangeAnim(EMonsterAnimType::Skill1);

		Boss->mSkillCoolCurrentTime[0] = 0.f;

		break;
	case 2:
		Anim->ChangeAnim(EMonsterAnimType::Skill2);

		Boss->mSkillCoolCurrentTime[1] = 0.f;

		break;
	case 3:
		Anim->ChangeAnim(EMonsterAnimType::Skill3);

		Boss->mSkillCoolCurrentTime[2] = 0.f;

		break;

	default:
		break;
	}




	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_Skill::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::AbortTask(OwnerComp,
		NodeMemory);

	return result;
}

void UBTTask_Skill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	
	AMonsterAIController* Controller =
		Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (!IsValid(Controller))
	{
		// Task�� �����Ų��.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (mSkillNum == 0) {

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	ABossMonsterRampage* Boss = Cast<ABossMonsterRampage>(Controller->GetPawn());

	if (!IsValid(Boss))
	{
		// Task�� �����Ų��.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UMonsterAnimInstance* Anim = Boss->GetMonsterAnimInst();

	// Blackboard�� ����� Target�� ���;� �Ѵ�.
	ABasePlayerCharacter* Target = Cast<ABasePlayerCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		// �̵��� �����.
		Controller->StopMovement();

		// �ִϸ��̼��� Idle�� ��ȯ�Ѵ�.
		Anim->ChangeAnim(EMonsterAnimType::Idle);

		// Task�� �����Ų��.
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// ������ �������� �Ǵ��Ѵ�.
	if (Boss->GetAttackEnd())
	{
		// Skill ��Ÿ�� üũ

		int32 SkillIndex = mSkillNum - 1;

		if (Boss->mSkillCoolTime[SkillIndex] > Boss->mSkillCoolCurrentTime[SkillIndex])
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}

		Boss->SetAttackEnd(false);
	}

}

void UBTTask_Skill::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);


}
