// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMonster.h"
#include "MonsterSuperDawn.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API AMonsterSuperDawn : public ABaseMonster
{
	GENERATED_BODY()

public:
	AMonsterSuperDawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();

public:
	virtual void Attack();
};
