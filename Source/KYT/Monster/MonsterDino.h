// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMonster.h"
#include "MonsterDino.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API AMonsterDino : public ABaseMonster
{
	GENERATED_BODY()
	
public:
	AMonsterDino();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void PossessedBy(AController* NewController);
	virtual void UnPossessed();

public:
	virtual void Attack();
};
