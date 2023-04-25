// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BasePlayerCharacter.h"
#include "MagicianPlayerCharacter.generated.h"

/**
 * 
 */

class AProjectile;

UCLASS()
class KYT_API AMagicianPlayerCharacter : public ABasePlayerCharacter
{
	GENERATED_BODY()
	


public:
	// Sets default values for this character's properties
	AMagicianPlayerCharacter();



public:

	TArray<AProjectile*> mProjectile;


public:

	bool mSkill2Success;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



public:

	virtual void NormalAttack();
	virtual void NormalAttackEffect(int32 ComboCount);

	virtual void UseSkill(int32 SkillNumber);
	virtual void ApplyDamage(int32 SkillNumber);

	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill3();
	virtual void Skill4();

	virtual void Dash();



public:


	bool GetIsHoming() {

		return mInfo.ProjectileInfo.mHoming;

	}
	void SetHoming(bool bHoming)
	{
		mInfo.ProjectileInfo.mHoming = bHoming;
	}

	bool GetIsDuplicate()
	{
		return mInfo.ProjectileInfo.mDuplicate;
	}
	void SetDuplicate(bool bDuplicate)
	{
		mInfo.ProjectileInfo.mDuplicate = bDuplicate;
	}

	float GetProjectileDuplicateProbability() {

		return mInfo.ProjectileInfo.mDuplicateProbability;
	}

	void SetProjectileDuplicateProbability(float Probability) {

		mInfo.ProjectileInfo.mDuplicateProbability = Probability;
	}

	int32 GetProjectileDuplicateCount() {

		return mInfo.ProjectileInfo.mDuplicateCount;

	}

	void SetProjectileDuplicateCount(int32 Count)
	{
		mInfo.ProjectileInfo.mDuplicateCount = Count;
	}


	float GetProjectileSpeed() {

		return mInfo.ProjectileInfo.mProjectileSpeed;

	}
	void SetProjectileSpeed(float Speed)
	{
		mInfo.ProjectileInfo.mProjectileSpeed = Speed;
	}

	float GetProjectileScale() {

		return	mInfo.ProjectileInfo.mProjectileScale;

	}
	void SetProjectileScale(float Scale)
	{
		mInfo.ProjectileInfo.mProjectileScale = Scale;
	}

	float GetProjectileDamageScale() {

		return mInfo.ProjectileInfo.mProjectileDamageScale;

	}
	void SetProjectileDamageScale(float Scale)
	{
		mInfo.ProjectileInfo.mProjectileDamageScale = Scale;
	}

	virtual void LevelUp();
};
