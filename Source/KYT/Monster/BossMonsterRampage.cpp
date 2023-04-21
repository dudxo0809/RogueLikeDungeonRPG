// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonsterRampage.h"


#include "MonsterAIController.h"
#include "../UMG/MonsterHP.h"

#include "../Skill/ParticleCascade.h"



ABossMonsterRampage::ABossMonsterRampage()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(110.f);
	GetCapsuleComponent()->SetCapsuleRadius(80.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -110.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	mMonsterTableRowName = TEXT("Rampage");


	SetActorScale3D(FVector(2, 2, 2));

	mAttackLocationDist = 200.f;


	mSkillCoolTime.Add(5.f);
	mSkillCoolTime.Add(20.f);
	mSkillCoolTime.Add(30.f);

	mSkillCoolCurrentTime.Add(0.f);
	mSkillCoolCurrentTime.Add(0.f);
	mSkillCoolCurrentTime.Add(0.f);
	

	
}


void ABossMonsterRampage::BeginPlay()
{
	Super::BeginPlay();

	//Sound

	mNormalAttackSoundPath = TEXT("SoundWave'/Game/UltimateMagicUE/wav/Target_Hits/Target_Hit_-_Earth__2_.Target_Hit_-_Earth__2_'");
}

void ABossMonsterRampage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto& i : mSkillCoolCurrentTime) {

		i += DeltaTime;
	}
}

void ABossMonsterRampage::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// 다른 BehaviorTree나 BlackboardData를 사용하면 여기에서
	// 다르게 지정해준다.


	// 부모 기능을 실행하기 전에 먼저 BehaviorTree와
	// Blackboard를 지정해준다.
	AMonsterAIController* AI =
		Cast<AMonsterAIController>(NewController);

	if (IsValid(AI))
	{
		AI->SetBehaviorTree(TEXT("BehaviorTree'/Game/KYT/Monster/AI/Rampage/BT_Rampage.BT_Rampage'"));
		AI->SetBlackboard(TEXT("BlackboardData'/Game/KYT/Monster/AI/Rampage/BB_Rampage.BB_Rampage'"));
	}

}

void ABossMonsterRampage::UnPossessed()
{
	Super::UnPossessed();

}

void ABossMonsterRampage::Attack()
{
	Super::Attack();


}

// Smash 
// Round
void ABossMonsterRampage::Skill1()
{


	FCollisionQueryParams	param(NAME_None, false, this);


	FHitResult	CollisionResult;
	bool CollisionEnable = GetWorld()->SweepSingleByChannel(
		CollisionResult,
		GetActorLocation() + FVector(0, 0, 300) ,
		GetActorLocation() + FVector(0, 0, 300),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel10,				// MonsterAttack
		FCollisionShape::MakeSphere(800.f),
		param);

	FColor	DrawColor = CollisionEnable ? FColor::Red : FColor::Green;


	FActorSpawnParameters	SpawnParam;
	//SpawnParam.Template = mHitActor;
	SpawnParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	AParticleCascade* Particle =
		GetWorld()->SpawnActor<AParticleCascade>(
			GetActorLocation(),
			GetActorRotation(),
			SpawnParam);

	Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonRampage/FX/Particles/Abilities/RipNToss/FX/P_Rampage_Rock_HitWorld.P_Rampage_Rock_HitWorld'"));
	Particle->SetSound(TEXT("SoundWave'/Game/UltimateMagicUE/wav/Target_Hits/Target_Hit_-_Earth__10_.Target_Hit_-_Earth__10_'"));
	Particle->SetSoundVolumeScale(0.7f);

	Particle->SetActorScale3D(FVector(2, 2, 2));

	// Sound
	//UAudioComponent* mAudio = NewObject<UAudioComponent>(this, TEXT("Audio"));
	//mAudio->SetSound(TEXT(""));
	//mAudio->SetVolumeMultiplier(0.7f);
	//mAudio->Play();

	if (CollisionEnable)
	{

		CollisionResult.GetActor()->TakeDamage(
			(float)mInfo.SkillDataArray[0].AttackPoint,
			FDamageEvent(), GetController(), this);
		//Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonYin/FX/Particles/Yin/Abilities/Primary/FX/P_Yin_Primary_Impact.P_Yin_Primary_Impact'"));

	}

}

// HP Recovery
void ABossMonsterRampage::Skill2()
{
	FActorSpawnParameters	SpawnParam;
	//SpawnParam.Template = mHitActor;
	SpawnParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	AParticleCascade* Particle =
		GetWorld()->SpawnActor<AParticleCascade>(
			GetActorLocation(),
			GetActorRotation(),
			SpawnParam);

	Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonRampage/FX/Particles/Abilities/Roar/FX/P_Rampage_Roar_Radius.P_Rampage_Roar_Radius'"));
	//Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonRampage/FX/Particles/Abilities/Primary/FX/P_MeleeTrails_RoarBuffed.P_MeleeTrails_RoarBuffed'"));
	Particle->SetSound(TEXT("SoundWave'/Game/UltimateMagicUE/wav/Buffs/Buff_36.Buff_36'"));
	Particle->SetSoundVolumeScale(0.5f);

	Particle->SetActorScale3D(FVector(5, 5, 5));

	mInfo.HP += (mInfo.HPMax * 0.3f);

	if (mInfo.HP > mInfo.HPMax)
		mInfo.HP = mInfo.HPMax;


	float Ratio = (float)mInfo.HP / mInfo.HPMax;
	mMonsterHP->SetHPPercent(Ratio);

}

// Range Attack
void ABossMonsterRampage::Skill3()
{


	FCollisionQueryParams	param(NAME_None, false, this);

	FVector	StartLocation = GetActorLocation() +
		GetActorForwardVector() * 100;
	FVector	EndLocation = StartLocation +
		GetActorForwardVector() * 2000;

	FHitResult	CollisionResult;
	bool CollisionEnable = GetWorld()->SweepSingleByChannel(
		CollisionResult, StartLocation,
		EndLocation, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel10,				// MonsterAttack
		FCollisionShape::MakeSphere(600.f),
		param);

	FColor	DrawColor = CollisionEnable ? FColor::Red : FColor::Green;


	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
		2500 / 2.f,
		800.f,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 1.0f);



	FActorSpawnParameters	SpawnParam;
	//SpawnParam.Template = mHitActor;
	SpawnParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	for (int32 i = 0; i < 3; i++) {

		AParticleCascade* Particle =
			GetWorld()->SpawnActor<AParticleCascade>(
				(StartLocation + EndLocation) * i / 8,
				GetActorRotation(),
				SpawnParam);

		Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonRampage/FX/Particles/Rampage_v001_IceBlue/FX/P_Rampage_Lunge_ImpactBlue.P_Rampage_Lunge_ImpactBlue'"));

	}
	AParticleCascade* Particle =
		GetWorld()->SpawnActor<AParticleCascade>(
			(StartLocation + EndLocation) / 2.f,
			GetActorRotation(),
			SpawnParam);

	Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonRampage/FX/Particles/Rampage_v001_IceBlue/FX/P_Rampage_Lunge_ImpactBlue.P_Rampage_Lunge_ImpactBlue'"));
	Particle->SetSound(TEXT("SoundWave'/Game/UltimateMagicUE/wav/DeBuffs/DeBuff_11.DeBuff_11'"));
	Particle->SetSoundVolumeScale(0.9f);

	Particle->SetActorScale3D(FVector(3, 3, 3));

	// Sound
	//UAudioComponent* mAudio = NewObject<UAudioComponent>(this, TEXT("Audio"));
	//mAudio->SetSound(TEXT(""));
	//mAudio->SetVolumeMultiplier(0.7f);
	//mAudio->Play();

	if (CollisionEnable)
	{

		CollisionResult.GetActor()->TakeDamage(
			(float)mInfo.SkillDataArray[2].AttackPoint,
			FDamageEvent(), GetController(), this);
		//Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonYin/FX/Particles/Yin/Abilities/Primary/FX/P_Yin_Primary_Impact.P_Yin_Primary_Impact'"));

	}
}
