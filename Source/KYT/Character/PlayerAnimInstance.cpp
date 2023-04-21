// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "BasePlayerCharacter.h"
//#include "../Skill/SkillProjectile.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mMoveDir = 0.f;

	mAttack = false;
	mAttackEnable = true;
	mAttackIndex = 0;

	mAnimType = EPlayerAnimType::Ground;

	mGround = true;
	mJumpLoop = false;

	mFallRecoveryAdditive = 0.f;

	mUseSkillNumber = -1;

	mComboCount = 0;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Start();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement =
			PlayerCharacter->GetCharacterMovement();

		mSpeedRatio = Movement->Velocity.Size() /
			Movement->MaxWalkSpeed;

		// 땅 위에 있는지를 판단한다.
		mGround = Movement->IsMovingOnGround();

		if (!mGround && mAnimType != EPlayerAnimType::Jump)
		{
			mAnimType = EPlayerAnimType::Fall;
		}
	}
}

void UPlayerAnimInstance::Start()
{
	Montage_Play(mStartMontage);
}

bool UPlayerAnimInstance::Attack()
{
	if (!mAttackEnable)
		return false;

	mAttackEnable = false;

	if (!Montage_IsPlaying(mAttackMontageArray[mAttackIndex]))
	{
		if (mAttackIndex == 3) {
			mAttackIndex = 3;
		}
		Montage_SetPosition(mAttackMontageArray[mAttackIndex], 0.f);
		Montage_Play(mAttackMontageArray[mAttackIndex]);

		mAttackIndex = (mAttackIndex + 1) % mAttackMontageArray.Num();
		mAttack = true;

		return true;
	}

	else {
		mAttackEnable = true;

		return false;
	}

	return false;
}


void UPlayerAnimInstance::Jump()
{
	mAnimType = EPlayerAnimType::Jump;
}

void UPlayerAnimInstance::UseSkill(int32 SkillNumber)
{
	int32	Count = mSkillMontageArray.Num();

	for (int32 i = 0; i < Count; ++i)
	{
		if (mSkillMontageArray[i].SkillNumber == SkillNumber)
		{
			mUseSkillNumber = SkillNumber;

			if (!Montage_IsPlaying(mSkillMontageArray[i].Montage))
			{
				Montage_SetPosition(mSkillMontageArray[i].Montage, 0.f);
				Montage_Play(mSkillMontageArray[i].Montage);
			}
			break;
		}
	}
}

void UPlayerAnimInstance::AnimNotify_Attack()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(TryGetPawnOwner());

	if (mAttackIndex == 3) {
		mAttackIndex = 3;
	}

	if (IsValid(PlayerCharacter)) {
	
		PlayerCharacter->NormalAttackEffect(mComboCount);
		
	}
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	
	mAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{

	mAttackIndex = 0;
	mAttackEnable = true;
	mAttack = false;

}

void UPlayerAnimInstance::AnimNotify_JumpEnd()
{
	mAnimType = EPlayerAnimType::Fall;
}

void UPlayerAnimInstance::AnimNotify_FallEnd()
{
	mAnimType = EPlayerAnimType::Ground;

	if (IsValid(mFallRecoveryMontage))
	{
		mFallRecoveryAdditive = 1.f;

		Montage_SetPosition(mFallRecoveryMontage, 0.f);
		Montage_Play(mFallRecoveryMontage);
	}
}

void UPlayerAnimInstance::AnimNotify_FallRecoveryEnd()
{
	mFallRecoveryAdditive = 0.f;
}

void UPlayerAnimInstance::AnimNotify_CanMove()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter)) {

		mAttackEnable = true;
		PlayerCharacter->SetPlayerMovable(true);

	}
	

}

void UPlayerAnimInstance::AnimNotify_CannotMove()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter)) {

		mAttackEnable = false;
		PlayerCharacter->SetPlayerMovable(false);

	}
	
}

void UPlayerAnimInstance::AnimNotify_UseSkill()
{
	// 스킬을 사용한다.
	if (mUseSkillNumber == -1)
		return;

	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter)) {
	
		PlayerCharacter->UseSkill(mUseSkillNumber);
		
		mAttackEnable = false;
	}
}

void UPlayerAnimInstance::AnimNotify_ApplyDamage()
{
	if (mUseSkillNumber == -1)
		return;

	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
		PlayerCharacter->ApplyDamage(mUseSkillNumber);
}

void UPlayerAnimInstance::AnimNotify_SaveAttack()
{
	if (mAttackMontageArray.Num() - 1 <= mComboCount)
		mComboCount = 0;
	else
		mComboCount++;
}

void UPlayerAnimInstance::AnimNotify_ResetCombo()
{
	mComboCount = 0;
}

void UPlayerAnimInstance::AnimNotify_FootLeft()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(TryGetPawnOwner());

//	if (IsValid(PlayerCharacter))
		//PlayerCharacter->FootStep(true);
}

void UPlayerAnimInstance::AnimNotify_FootRight()
{
	ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(TryGetPawnOwner());

	//if (IsValid(PlayerCharacter))
		//PlayerCharacter->FootStep(false);
}

