// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSpawnTrigger.h"

#include "../Character/BasePlayerCharacter.h"
#include "../Skill/ParticleNiagara.h"

#include "../Monster/BossMonsterRampage.h"

ABossSpawnTrigger::ABossSpawnTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	mMonsterClassArray.Add(ABossMonsterRampage::StaticClass());
}

void ABossSpawnTrigger::TriggerBegin(const FHitResult& SweepResult, AActor* OtherActor)
{
	ABasePlayerCharacter* Player = Cast<ABasePlayerCharacter>(OtherActor);
	if (!IsValid(Player))
		return;

	FActorSpawnParameters	SpawnParam;

	ABaseBossMonster* Monster = GetWorld()->SpawnActor<ABaseBossMonster>(mMonsterClassArray[0],
		GetActorLocation(),
		FRotator(0, 0, 0),
		SpawnParam);

	// if Monster is nullptr -> Collision has occured
	if (Monster != nullptr) {

		mRoom->AddMonster(Monster);
		
		Monster->SetRoom(mRoom);

	}

	mRoom->SetMonsterIsSpawned();

}

void ABossSpawnTrigger::TriggerEnd()
{
	this->Destroy();
}
