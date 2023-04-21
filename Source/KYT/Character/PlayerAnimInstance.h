// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */



UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Ground,
	Jump,
	Fall,
	Death
};

USTRUCT(BlueprintType)
struct FSkillAnimationInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32	SkillNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UAnimMontage* Montage;
};



UCLASS()
class KYT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UPlayerAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	mSpeedRatio;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	mMoveDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UAnimMontage*	mStartMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		TArray<UAnimMontage*>	mAttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UAnimMontage* mFallRecoveryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		TArray<FSkillAnimationInfo>	mSkillMontageArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool	mAttackEnable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32	mAttackIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool	mAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		EPlayerAnimType	mAnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool	mGround;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool	mJumpLoop;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	mFallRecoveryAdditive;

	int32	mUseSkillNumber;


	int32 mComboCount;


public:
	EPlayerAnimType GetPlayerAnimType()	const
	{
		return mAnimType;
	}

	void SetMoveDir(float Dir)
	{
		mMoveDir = Dir;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:

	void Start();

	bool Attack();
	void Jump();
	void UseSkill(int32 SkillNumber);

	void SetPlayerAnimType(EPlayerAnimType AnimType) {

		mAnimType = AnimType;
	}

public:
	// 노티파이 함수는 void AnimNotify_노티파이이름() 의 형태로 만들어준다.
	UFUNCTION()
		void AnimNotify_Attack();

	UFUNCTION()
		void AnimNotify_AttackEnable();

	UFUNCTION()
		void AnimNotify_AttackEnd();

	UFUNCTION()
		void AnimNotify_JumpEnd();

	UFUNCTION()
		void AnimNotify_FallEnd();

	UFUNCTION()
		void AnimNotify_FallRecoveryEnd();

	UFUNCTION()
		void AnimNotify_CanMove();

	UFUNCTION()
		void AnimNotify_CannotMove();

	UFUNCTION()
		void AnimNotify_UseSkill();

	UFUNCTION()
		void AnimNotify_ApplyDamage();


	UFUNCTION()
		void AnimNotify_SaveAttack();

	UFUNCTION()
		void AnimNotify_ResetCombo();



	UFUNCTION()
		void AnimNotify_FootLeft();

	UFUNCTION()
		void AnimNotify_FootRight();

	
};
