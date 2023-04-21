// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseMonster.h"

#include "GameFramework/Actor.h"
#include "../Skill/ParticleNiagara.h"

#include "MonsterSpawnPoint.generated.h"

UCLASS()
class KYT_API AMonsterSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawnPoint();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		USceneComponent* mRoot;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		TArray<TSubclassOf<class ABaseMonster>>		mSpawnClassArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 mSpawnIndex;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UNiagaraComponent* mParticle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UFUNCTION()
	void SpawnMonster();



public:
	virtual void SetParticle(UNiagaraSystem* Particle);
	virtual void SetParticle(const FString& Path);

};
