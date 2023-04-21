// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnTrigger.h"

#include "../Character/BasePlayerCharacter.h"

#include "../KYTGameModeBase.h"
#include "../RandomRoom/RandomRoomGameMode.h"

#include "../UMG/Minimap.h"

#include "../Skill/ParticleNiagara.h"
#include "../RandomRoom/RoomBase.h"

#include "../Monster/MonsterMeleeDawn.h"
#include "../Monster/MonsterMeleeDusk.h"
#include "../Monster/MonsterSuperDawn.h"
#include "../Monster/MonsterSuperDusk.h"

#include "../Monster/BossMonsterRampage.h"



AMonsterSpawnTrigger::AMonsterSpawnTrigger()
{
	PrimaryActorTick.bCanEverTick = true;


	mRoom = nullptr;

	mStageNum = 1;
//
	//GetClass()
	
	mMonsterClassArray.Add(AMonsterMeleeDawn::StaticClass());
	mMonsterClassArray.Add(AMonsterSuperDawn::StaticClass());

	mMonsterClassArray.Add(AMonsterMeleeDusk::StaticClass());
	mMonsterClassArray.Add(AMonsterSuperDusk::StaticClass());

//	mMonsterClassArray.Add(ABossMonsterRampage::StaticClass());

	ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode)) {

		mStageNum = MyGameMode->GetStageNumber();
	}

}

/*
void AMonsterSpawnTrigger::AddMonsterSpawnPoint(AMonsterSpawnPoint* SpawnPoint)
{
	mMonsterSpawnPointArray.Add(SpawnPoint);
}
*/

void AMonsterSpawnTrigger::TriggerBegin(const FHitResult& SweepResult, AActor* OtherActor)
{
	ABasePlayerCharacter* Player = Cast<ABasePlayerCharacter>(OtherActor);
	if (!IsValid(Player))
		return;

	TArray<ABaseMonster*> TempMonsterArray;
	
	// Limit Monster Spawn Number
	int32 MaxSpawncount = 20;

	int32 MonsterNumMin = (int32)EMonsterSpawnNumber::Min + mStageNum;
	int32 MonsterNumMax = (int32)EMonsterSpawnNumber::Max + mStageNum;

	int32 MonsterCount = FMath::RandRange(MonsterNumMin, MonsterNumMax);

	// Maximum Monster Spawn count is 20!
	MonsterCount = (MonsterCount <= MaxSpawncount ? MonsterCount : MaxSpawncount);

	// Audio
	UAudioComponent* mAudio = NewObject<UAudioComponent>(this, TEXT("Audio"));

	USoundBase* SpawnSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/UltimateMagicUE/wav/Classic_Spawn_SFX/Classic_Spawn__6_.Classic_Spawn__6_'"));
	mAudio->SetSound(SpawnSound);
	mAudio->SetVolumeMultiplier(0.6f);
	mAudio->Play();

	for (int32 i = 0; i < MonsterCount; i++) {

		int32 MonsterClassIndex = FMath::RandRange(0, mMonsterClassArray.Num() - 1);
		
		int32 OffsetX = FMath::RandRange((int32)EMonsterSpawnPos::Min, (int32)EMonsterSpawnPos::Max);
		int32 OffsetY = FMath::RandRange((int32)EMonsterSpawnPos::Min, (int32)EMonsterSpawnPos::Max);

		FVector SpawnLocation = GetActorLocation() + FVector(OffsetX, OffsetY, 0);

		FActorSpawnParameters	SpawnParam;


		ABaseMonster* Monster = GetWorld()->SpawnActor<ABaseMonster>(mMonsterClassArray[MonsterClassIndex],
			SpawnLocation,
			FRotator(0, 0, 0),
			SpawnParam);

		// if Monster is nullptr -> Collision has occured

		if (Monster == nullptr) {

			i--;
			continue;
		}

		mRoom->AddMonster(Monster);
		TempMonsterArray.Add(Monster);

		AParticleNiagara* Effect = GetWorld()->SpawnActor<AParticleNiagara>(SpawnLocation,
			FRotator(0, 0, 0),
			SpawnParam);

		//Effect->SetActorScale3D(FVector(0.7, 0.7, 0.7));
		

		switch (MonsterClassIndex){

			case 0:
			case 1:

				//Effect->SetParticle(TEXT("NiagaraSystem'/Game/Ultimate_Magic_Bundle/AEO_Abilities/MagicAEO/Niagara/ShadowIsle/NS_ShadowIsle_Yellow.NS_ShadowIsle_Yellow'"));
				Effect->SetParticle(TEXT("NiagaraSystem'/Game/Ultimate_Magic_Bundle/MagicProjectiles/Niagara/Ice/NS_Ice_Muzzle_White.NS_Ice_Muzzle_White'"));
				break;
			case 2:
			case 3:
				//Effect->SetParticle(TEXT("NiagaraSystem'/Game/Ultimate_Magic_Bundle/AEO_Abilities/MagicAEO/Niagara/ShadowIsle/NS_ShadowIsle_Purple.NS_ShadowIsle_Purple'"));
				Effect->SetParticle(TEXT("NiagaraSystem'/Game/Ultimate_Magic_Bundle/MagicProjectiles/Niagara/Ice/NS_Ice_Muzzle_White.NS_Ice_Muzzle_White'"));
				break;
		}
		
	}

	// mRoom 에 몬스터가 전부 스폰되었다고 알림
	mRoom->SetMonsterIsSpawned();


	// 
	AKYTGameModeBase* MyGameMode = Cast<AKYTGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode)) {

		UMinimap* MyMiniMap = MyGameMode->GetMainHUD()->GetMiniMap();
		MyMiniMap->SetMonsterArray(TempMonsterArray);
	}

}

void AMonsterSpawnTrigger::TriggerEnd()
{


	this->Destroy();
}
