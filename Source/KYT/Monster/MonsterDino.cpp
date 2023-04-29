// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDino.h"

AMonsterDino::AMonsterDino()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(110.f);
	GetCapsuleComponent()->SetCapsuleRadius(65.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -110.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mMonsterTableRowName = TEXT("Dino");


	SetActorScale3D(FVector(1.5, 1.5, 1.5));
}

void AMonsterDino::BeginPlay()
{
	Super::BeginPlay();


}

void AMonsterDino::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// �ٸ� BehaviorTree�� BlackboardData�� ����ϸ� ���⿡��
	// �ٸ��� �������ش�.
}

void AMonsterDino::UnPossessed()
{
	Super::UnPossessed();


}

void AMonsterDino::Attack()
{
	Super::Attack();


}
