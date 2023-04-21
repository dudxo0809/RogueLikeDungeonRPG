// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnPoint.h"

// Sets default values
AMonsterSpawnPoint::AMonsterSpawnPoint():
	mSpawnIndex(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);
	//mRoot->bVisualizeComponent = true;



	
}

// Called when the game starts or when spawned
void AMonsterSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	//SpawnMonster();

}

// Called every frame
void AMonsterSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawnPoint::SpawnMonster()
{
	// 생성할 몬스터 클래스가 있을 경우에만 진행한다.
	if (!mSpawnClassArray.IsEmpty() && mSpawnClassArray.Num() > mSpawnIndex)
	{

		FActorSpawnParameters	SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ABaseMonster* SpawnMonster =
			GetWorld()->SpawnActor<ABaseMonster>(mSpawnClassArray[mSpawnIndex],
				GetActorLocation(), GetActorRotation(),
				SpawnParam);

		SpawnMonster->SetSpawnPoint(this);
	

		mSpawnIndex++;
	}

}

void AMonsterSpawnPoint::SetParticle(UNiagaraSystem* Particle)
{
	if (IsValid(Particle))
		mParticle->SetAsset(Particle);
}

void AMonsterSpawnPoint::SetParticle(const FString& Path)
{
	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(
		nullptr, *Path);

	if (IsValid(Particle))
		mParticle->SetAsset(Particle);
}

