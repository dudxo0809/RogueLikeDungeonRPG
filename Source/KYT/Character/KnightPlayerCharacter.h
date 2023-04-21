// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePlayerCharacter.h"
#include "KnightPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API AKnightPlayerCharacter : public ABasePlayerCharacter
{
	GENERATED_BODY()
	


public:
	// Sets default values for this character's properties
	AKnightPlayerCharacter();

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

};
