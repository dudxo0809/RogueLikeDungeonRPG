// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBossMonster.h"

#include "MonsterSpawnPoint.h"
#include "../KYTGameInstance.h"
#include "MonsterAIController.h"
#include "MonsterAnimInstance.h"
#include "../Skill/ParticleNiagara.h"

#include "../Trigger/LevelTrigger.h"

ABaseBossMonster::ABaseBossMonster()
{
}

void ABaseBossMonster::BeginPlay()
{
	Super::BeginPlay();


	
	mNextStageTime = 5.f;
	mNextStageCurrentTime = 0.f;

	bLevelTrigerSpawn = false;
}

void ABaseBossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (mDead && !bLevelTrigerSpawn)
	{
		mNextStageCurrentTime += DeltaTime;
		if (mNextStageCurrentTime >= mNextStageTime) {

			bLevelTrigerSpawn = true;

			FActorSpawnParameters	SpawnParam;

			ALevelTrigger* LevelTrigger = GetWorld()->SpawnActor<ALevelTrigger>(mBossRoom->GetActorLocation(), mBossRoom->GetActorRotation(), SpawnParam);
			
			LevelTrigger->SetActorScale3D(FVector(3, 3, 3));
			LevelTrigger->SetLevel(TEXT("Dungeon"));


			AParticleNiagara* Particle =
				GetWorld()->SpawnActor<AParticleNiagara>(
					mBossRoom->GetActorLocation() + FVector(0,0,400),
					FRotator(90,0,0),
					SpawnParam);

			Particle->SetParticle(TEXT("NiagaraSystem'/Game/KYT/Level/NS_LevelTrigger.NS_LevelTrigger'"));
			Particle->SetSound(TEXT("SoundWave'/Game/UltimateMagicUE/wav/Spell_Loops/Loop_-__Forest_Spirits.Loop_-__Forest_Spirits'"));
			Particle->SetSoundVolumeScale(0.5f);

			Particle->SetActorRotation(FRotator(90, 0, 0));
			Particle->SetActorScale3D(FVector(7, 7, 7));

			
		}
	}

}

void ABaseBossMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	
}

void ABaseBossMonster::UnPossessed()
{

	Super::UnPossessed();
}