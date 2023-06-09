// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"

#include "BaseMonster.h"


UMonsterAnimInstance::UMonsterAnimInstance()
{
	mAnimType = EMonsterAnimType::Idle;
	mHitAdditive = 0.f;
	mLoopFalse = false;
}

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMonsterAnimInstance::AnimNotify_DeathEnd()
{
	ABaseMonster* Monster = Cast<ABaseMonster>(TryGetPawnOwner());

	//if (IsValid(Monster))
	//	Monster->OnDissolve();
}

void UMonsterAnimInstance::AnimNotify_HitEnd()
{
	mHitAdditive = 0.f;
}

void UMonsterAnimInstance::AnimNotify_Attack()
{
	ABaseMonster* Monster = Cast<ABaseMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->Attack();
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	ABaseMonster* Monster = Cast<ABaseMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->SetAttackEnd(true);
}

void UMonsterAnimInstance::AnimNotify_Skill1()
{
	ABaseMonster* Monster = Cast<ABaseMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->Skill1();
}

void UMonsterAnimInstance::AnimNotify_Skill2()
{
	ABaseMonster* Monster = Cast<ABaseMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->Skill2();
}

void UMonsterAnimInstance::AnimNotify_Skill3()
{
	ABaseMonster* Monster = Cast<ABaseMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->Skill3();
}

void UMonsterAnimInstance::AnimNotify_SkillEnd()
{
	ABaseMonster* Monster = Cast<ABaseMonster>(TryGetPawnOwner());

	if (IsValid(Monster))
		Monster->ClearCurrentSkill();
}
