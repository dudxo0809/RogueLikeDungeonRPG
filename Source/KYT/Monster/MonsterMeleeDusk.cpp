// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMeleeDusk.h"

AMonsterMeleeDusk::AMonsterMeleeDusk()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(110.f);
	GetCapsuleComponent()->SetCapsuleRadius(65.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -110.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mMonsterTableRowName = TEXT("MeleeDusk");


	SetActorScale3D(FVector(1.5, 1.5, 1.5));

	// ParticleSystem'/Game/ParagonMinions/FX/Particles/Minions/Minion_melee/FX/Impacts/P_Minion_Impact_Default.P_Minion_Impact_Default'
}

void AMonsterMeleeDusk::BeginPlay()
{
	Super::BeginPlay();


}

void AMonsterMeleeDusk::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// 다른 BehaviorTree나 BlackboardData를 사용하면 여기에서
	// 다르게 지정해준다.

}

void AMonsterMeleeDusk::UnPossessed()
{
	Super::UnPossessed();

}

void AMonsterMeleeDusk::Attack()
{
	Super::Attack();

}
