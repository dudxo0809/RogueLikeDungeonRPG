// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMeleeDawn.h"

AMonsterMeleeDawn::AMonsterMeleeDawn()
{

	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(110.f);
	GetCapsuleComponent()->SetCapsuleRadius(65.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -110.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mMonsterTableRowName = TEXT("MeleeDawn");


	SetActorScale3D(FVector(1.5, 1.5, 1.5));
}

void AMonsterMeleeDawn::BeginPlay()
{
	Super::BeginPlay();

}

void AMonsterMeleeDawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// 다른 BehaviorTree나 BlackboardData를 사용하면 여기에서
	// 다르게 지정해준다.

}

void AMonsterMeleeDawn::UnPossessed()
{
	Super::UnPossessed();

}

void AMonsterMeleeDawn::Attack()
{
	Super::Attack();

}
