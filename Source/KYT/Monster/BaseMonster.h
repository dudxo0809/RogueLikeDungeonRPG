// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterInfo.h"
#include "../Character/BaseCharacter.h"
#include <Components\WidgetComponent.h>

#include "BaseMonster.generated.h"

/**
 * 
 */
class AExpProjectile;
class UMonsterHP;

UCLASS()
class KYT_API ABaseMonster : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();



protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FMonsterBaseInfo		mInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName					mMonsterTableRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UWidgetComponent*		mWidgetComopnent;

	// HUD
	TSubclassOf<UUserWidget>	mMonsterHPClass;
	UMonsterHP* mMonsterHP;
	

	// AttackSound
	FString mNormalAttackSoundPath;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		AExpProjectile* mExpProjectile;


	bool		mAttackEnd;

	AActor* mHitActor;

	class UMonsterAnimInstance* mAnimInst;

	class AMonsterSpawnPoint* mSpawnPoint;


	bool mDead;

	bool mDestroyStart;

	float mDestroyTime;
	float mDestroyCurrentTime;

private:

	int32 mStageNum;


protected:

	float mAttackLocationDist;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();


public:

	const FMonsterBaseInfo& GetMonsterInfo() const { 
		
		return mInfo;
	}

	void SetSpawnPoint(class AMonsterSpawnPoint* SpawnPoint)
	{
		mSpawnPoint = SpawnPoint;
	}

	void SetAttackEnd(bool AttackEnd)
	{
		mAttackEnd = AttackEnd;
	}

	bool GetAttackEnd() { 
		
		return mAttackEnd; 
	}

	class UMonsterAnimInstance* GetMonsterAnimInst() const { 
		
		return mAnimInst; 
	}

	bool IsDead() {

		return mDead;
	}

	void SetExpHoming();
	void DestroyStart(float DestroyTime);

public:

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);


public:
	virtual void Attack();

	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill3();

	void ClearSkill();
	void ClearCurrentSkill();
};
