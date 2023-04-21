// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BaseMonster.h"
#include "MonsterSuperDusk.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API AMonsterSuperDusk : public ABaseMonster
{
	GENERATED_BODY()

public:
	AMonsterSuperDusk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();

public:
	virtual void Attack();
};
