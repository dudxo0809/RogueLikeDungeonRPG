// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMonster.h"
#include "BaseBossMonster.h"
#include "BossMonsterRampage.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API ABossMonsterRampage : public ABaseBossMonster
{
	GENERATED_BODY()

	friend class UBTDecorator_SkillCoolTime;
	friend class UBTTask_Skill;

public:
	ABossMonsterRampage();


private:

	TArray<float> mSkillCoolTime;
	TArray<float> mSkillCoolCurrentTime;


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
	virtual void Attack();
	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill3();
};
