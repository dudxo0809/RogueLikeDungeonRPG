// Fill out your copyright notice in the Description page of Project Settings.


#include "KnightPlayerCharacter.h"

#include "../KYTGameInstance.h"
#include "../Skill/ParticleCascade.h"
#include "../Skill/ParticleNiagara.h"

#include "PlayerAnimInstance.h"



AKnightPlayerCharacter::AKnightPlayerCharacter()
{


	mPlayerTableRowName = TEXT("Knight");


	// BasePlayerCharacter::BeginPlay() 에 의해 다시 대입됨
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	KnightAsset(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (KnightAsset.Succeeded()) {

		GetMesh()->SetSkeletalMesh(KnightAsset.Object);
	}


	// AnimInstance
	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT("AnimBlueprint'/Game/KYT/Player/Animation/Knight/ABP_Knight.ABP_Knight_C'"));

	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);

	mHitActor = CreateDefaultSubobject<AParticleCascade>(TEXT("HitParticle"));

	AParticleCascade* Particle = Cast<AParticleCascade>(mHitActor);
	Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonGreystone/FX/Particles/Greystone/Abilities/Primary/FX/P_Greystone_Primary_Sparks.P_Greystone_Primary_Sparks'"));
	//Particle->SetSound(TEXT("SoundWave'/Game/Sound/Fire1.Fire1'"), false);


}

void AKnightPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	UKYTGameInstance* GameInst = GetWorld()->GetGameInstance<UKYTGameInstance>();

	const FPlayerCharacterTable* Info = GameInst->FindPlayerTable(mPlayerTableRowName);

	if (Info)
	{
		mInfo.PlayerClass = E_Player_Class::Knight;


	}

}

void AKnightPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AKnightPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AKnightPlayerCharacter::NormalAttack()
{
	Super::NormalAttack();


	
}


void AKnightPlayerCharacter::NormalAttackEffect(int32 ComboCount)
{

	

	FVector	StartLocation = GetActorLocation() +
		GetActorForwardVector() * 30.f;
	FVector	EndLocation = StartLocation +
		GetActorForwardVector() * mInfo.BaseAttackDistance;

	FCollisionQueryParams	param(NAME_None, false, this);

	TArray<FHitResult>	CollisionResult;
	bool CollisionEnable = GetWorld()->SweepMultiByChannel(
		CollisionResult, StartLocation,
		EndLocation, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,				// PlayerAttack
		FCollisionShape::MakeSphere(50.f),
		param);

	FColor	DrawColor = CollisionEnable ? FColor::Red : FColor::Green;

	/*
	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
		mInfo.BaseAttackDistance / 2.f,
		50.f,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 0.5f);
	*/
	//

	if (CollisionEnable)
	{
		int32	Count = CollisionResult.Num();

		for (int32 i = 0; i < Count; ++i)
		{
			FActorSpawnParameters	SpawnParam;
			//SpawnParam.Template = mHitActor;
			SpawnParam.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


			AParticleNiagara* Particle =
				GetWorld()->SpawnActor<AParticleNiagara>(
					CollisionResult[i].ImpactPoint,
					CollisionResult[i].ImpactNormal.Rotation(),
					SpawnParam);

			Particle->SetParticle(TEXT("NiagaraSystem'/Game/Ultimate_Magic_Bundle/MagicProjectiles/Niagara/Holy/NS_Holy_Impact.NS_Holy_Impact'"));
			//Particle->SetSound(TEXT("SoundWave'/Game/Sound/Fire1.Fire1'"));

			float Scale = ComboCount * 1;

			Particle->SetActorScale3D(FVector(1 + Scale, 1 + Scale, 1 + Scale));

			CollisionResult[i].GetActor()->TakeDamage(
				(float)mInfo.AttackPoint * (1 + Scale),
				FDamageEvent(), GetController(), this);
			//Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonYin/FX/Particles/Yin/Abilities/Primary/FX/P_Yin_Primary_Impact.P_Yin_Primary_Impact'"));
		}
	}


}

void AKnightPlayerCharacter::UseSkill(int32 SkillNumber)
{
	// 실제 스킬 동작
	// 데미지 처리 & 이펙트

	switch (SkillNumber) {

	case 0 :
	{
		FActorSpawnParameters	SpawnParam;
		//SpawnParam.Template = mHitActor;
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AParticleNiagara* FirstParticle =
			GetWorld()->SpawnActor<AParticleNiagara>(GetActorLocation(), GetActorRotation(), SpawnParam);

		FirstParticle->SetParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileImpactEffect);
		//FirstParticle->SetSound(mInfo.SkillEffectArray[mSkillEffectAttributeIndex].SkillSound1);


		UGameplayStatics::GetPlayerController(GetWorld(),0);

		

	}
		break;


	case 1:
	{

	}
		break;

	case 2:
	{

	}
		break;

	case 3:
	{

	}

		break;
	}
	

}

void AKnightPlayerCharacter::ApplyDamage(int32 SkillNumber)
{
	// 데미지 처리 & 이펙트

	switch (SkillNumber) {

	case 0:
	{
		FCollisionQueryParams	param(NAME_None, false, this);

		TArray<FOverlapResult>	CollisionResult;

		bool CollisionEnable = GetWorld()->OverlapMultiByChannel(CollisionResult,
			GetActorLocation(), FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel6,
			FCollisionShape::MakeSphere(1500),
			param);

		FColor	DrawColor = CollisionEnable ? FColor::Red : FColor::Green;

		DrawDebugSphere(GetWorld(), GetActorLocation(), 1500, 20, DrawColor, false, 0.5f);

		//
		FActorSpawnParameters	SpawnParam;
		//SpawnParam.Template = mHitActor;
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (CollisionEnable)
		{
			int32	Count = CollisionResult.Num();

			for (int32 i = 0; i < Count; ++i)
			{
				AParticleNiagara* Particle =
					GetWorld()->SpawnActor<AParticleNiagara>(
						CollisionResult[i].GetActor()->GetActorLocation(),
						CollisionResult[i].GetActor()->GetActorRotation(),
						SpawnParam);

				Particle->SetParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].UltimateEffect);
			//	Particle->SetSound(mInfo.SkillArray[mSkillEffectAttributeIndex].SkillSound2);

				CollisionResult[i].GetActor()->TakeDamage(
					mInfo.SkillDataArray[SkillNumber].AttackPoint,
					FDamageEvent(), GetController(), this);

			}
		}

	}
	break;


	case 1:
	{

	}
	break;

	case 2:
	{

	}
	break;

	case 3:
	{

	}

	break;
	}


}

void AKnightPlayerCharacter::Skill1()
{
	if (mInfo.MP < mInfo.SkillDataArray[0].MP)
		return;

	else {

		SyncPlayerStatus();

		mInfo.MP -= mInfo.SkillDataArray[0].MP;
		mAnimInst->UseSkill(0);
	}
	
}

void AKnightPlayerCharacter::Skill2()
{
	if (mInfo.MP < mInfo.SkillDataArray[1].MP)
		return;

	else {

		SyncPlayerStatus();

		mInfo.MP -= mInfo.SkillDataArray[1].MP;
		mAnimInst->UseSkill(1);
	}
}

void AKnightPlayerCharacter::Skill3()
{
	if (mInfo.MP < mInfo.SkillDataArray[2].MP)
		return;

	else {

		SyncPlayerStatus();

		mInfo.MP -= mInfo.SkillDataArray[2].MP;
		mAnimInst->UseSkill(2);
	}
}

void AKnightPlayerCharacter::Skill4()
{
	if (mInfo.MP < mInfo.SkillDataArray[3].MP)
		return;

	else {

		SyncPlayerStatus();

		mInfo.MP -= mInfo.SkillDataArray[3].MP;
		mAnimInst->UseSkill(3);
	}
}
