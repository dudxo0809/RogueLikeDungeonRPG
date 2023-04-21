// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSuperDusk.h"


AMonsterSuperDusk::AMonsterSuperDusk()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(110.f);
	GetCapsuleComponent()->SetCapsuleRadius(75.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -110.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mMonsterTableRowName = TEXT("SuperDusk");


	SetActorScale3D(FVector(1.5, 1.5, 1.5));

	// ParticleSystem'/Game/ParagonMinions/FX/Particles/Minions/Minion_melee/FX/Impacts/P_Minion_Impact_Default.P_Minion_Impact_Default'

	mAttackLocationDist = 100.f;
}

void AMonsterSuperDusk::BeginPlay()
{
	Super::BeginPlay();


}

void AMonsterSuperDusk::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// 다른 BehaviorTree나 BlackboardData를 사용하면 여기에서
	// 다르게 지정해준다.

}

void AMonsterSuperDusk::UnPossessed()
{
	Super::UnPossessed();

}

void AMonsterSuperDusk::Attack()
{
	Super::Attack();

}
