// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMonster.h"
#include "MonsterMeleeDawn.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API AMonsterMeleeDawn : public ABaseMonster
{
	GENERATED_BODY()

public:
	AMonsterMeleeDawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();

public:
	virtual void Attack();
};
