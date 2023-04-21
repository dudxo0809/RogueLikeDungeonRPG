// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicianPlayerCharacter.h"

#include "../KYTGameInstance.h"
#include "../Skill/Projectile.h"

#include "PlayerAnimInstance.h"
#include "BasePlayerController.h"


AMagicianPlayerCharacter::AMagicianPlayerCharacter()
{


	mPlayerTableRowName = TEXT("Magician");

	// BasePlayerCharacter::BeginPlay() �� ���� �ٽ� ���Ե�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MagicianAsset(TEXT("SkeletalMesh'/Game/ParagonPhase/Characters/Heroes/Phase/Meshes/Phase_GDC.Phase_GDC'"));
	if (MagicianAsset.Succeeded()) {

		GetMesh()->SetSkeletalMesh(MagicianAsset.Object);
	}


	// AnimInstance
	static ConstructorHelpers::FClassFinder<UAnimInstance>	AnimClass(TEXT("AnimBlueprint'/Game/KYT/Player/Animation/Magician/ABP_Magician.ABP_Magician_C'"));

	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);


	mNormalAttackVolume = 0.5f;
	mSkillVolume = 0.5f;

}

void AMagicianPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UKYTGameInstance* GameInst = GetWorld()->GetGameInstance<UKYTGameInstance>();

	const FPlayerCharacterTable* Info = GameInst->FindPlayerTable(mPlayerTableRowName);

	if (Info)
	{
		mInfo.PlayerClass = E_Player_Class::Magician;

	}

	mInfo.ProjectileInfo.mProjectileDamage = mInfo.AttackPoint;
	
}

void AMagicianPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMagicianPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMagicianPlayerCharacter::NormalAttack()
{
	Super::NormalAttack();

	ABasePlayerController* MyController =  Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(MyController)) {

		MyController->AttackCameraShake();
	}

}

void AMagicianPlayerCharacter::NormalAttackEffect(int32 ComboCount)
{
	FActorSpawnParameters	SpawnParam;



	AParticleNiagara* MuzzleParticle =
		GetWorld()->SpawnActor<AParticleNiagara>(
			GetActorLocation() + GetActorForwardVector() * 200.f,
			GetActorRotation(),
			SpawnParam);

	MuzzleParticle->SetParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileMuzzleEffect);
	MuzzleParticle->SetSound(mInfo.SkillEffect[mSkillEffectAttributeIndex].NormalAttackSoundArray[ComboCount]);
	MuzzleParticle->SetSoundVolumeScale(mNormalAttackVolume);


	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation(), SpawnParam);
	Projectile->SetTrailParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileTrailEffect);
	Projectile->SetImpactParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileImpactEffect);
	Projectile->SetSpeed(mInfo.ProjectileInfo.mProjectileSpeed);
	Projectile->SetDuplicateSpeed(mInfo.ProjectileInfo.mProjectileSpeed);

	float Scale = ComboCount * 0.5f;

	Projectile->SetActorScale3D(FVector(1 + Scale, 1 + Scale, 1 + Scale) * mInfo.ProjectileInfo.mProjectileScale);

	Projectile->SetHoming(mInfo.ProjectileInfo.mHoming);
	Projectile->SetDuplicate(mInfo.ProjectileInfo.mDuplicate);
	Projectile->SetDuplicateCount(mInfo.ProjectileInfo.mDuplicateCount);

	Projectile->SetDamage(mInfo.ProjectileInfo.mProjectileDamage * mInfo.ProjectileInfo.mProjectileDamageScale);
	Projectile->SetProjectileDuplicateDamage(mInfo.ProjectileInfo.mProjectileDamage * mInfo.ProjectileInfo.mProjectileDamageScale * 0.5f);

	mProjectile.Add(Projectile);
	Projectile->mOwner = this;
}

void AMagicianPlayerCharacter::UseSkill(int32 SkillNumber)
{
	// ���� ��ų ����
	// ������ ó�� & ����Ʈ
	if (mSkillEnable[SkillNumber] == 0)
		return;


	// Reduce MP
	

	if (mInfo.MP < mInfo.SkillDataArray[SkillNumber].MP)
		return;

	else {

		SyncPlayerStatus();
		mInfo.MP -= mInfo.SkillDataArray[SkillNumber].MP;
	}

		
	
	TArray<USoundBase*> SkillSoundArray = mInfo.SkillEffect[mSkillEffectAttributeIndex].SkillSoundArray;

	
	FActorSpawnParameters	SpawnParam;

	switch (SkillNumber) {

	// �������� ����ü 3���� ������ �߻��Ѵ�
	// 
	case 0:
	{
		
		for (int32 i = 0; i < 3; i++) {

			FVector ProjectileLocation = GetActorLocation() + GetActorForwardVector() * 100;
			
			ProjectileLocation += GetActorRightVector() * 100 * (i - 1) ;


			AParticleNiagara* MuzzleParticle =
				GetWorld()->SpawnActor<AParticleNiagara>(
					ProjectileLocation,
					GetActorRotation(),
					SpawnParam);

			MuzzleParticle->SetParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileMuzzleEffect);
			MuzzleParticle->SetSound(SkillSoundArray[SkillNumber]);
			MuzzleParticle->SetSoundVolumeScale(mSkillVolume);


			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileLocation, GetActorRotation(), SpawnParam);
			Projectile->SetActorScale3D(FVector(1, 1, 1) * mInfo.ProjectileInfo.mProjectileScale);

			Projectile->SetTrailParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileTrailEffect);
			Projectile->SetImpactParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileImpactEffect);

			Projectile->SetSpeed(mInfo.ProjectileInfo.mProjectileSpeed * 2.0f);
			Projectile->SetDuplicateSpeed(mInfo.ProjectileInfo.mProjectileSpeed);

			Projectile->SetDuplicateCount(mInfo.ProjectileInfo.mDuplicateCount);

			Projectile->SetHoming(mInfo.ProjectileInfo.mHoming);
			Projectile->SetDuplicate(mInfo.ProjectileInfo.mDuplicate);

			Projectile->SetDamage(mInfo.ProjectileInfo.mProjectileDamage * mInfo.ProjectileInfo.mProjectileDamageScale * 1.0f);
			Projectile->SetProjectileDuplicateDamage(mInfo.ProjectileInfo.mProjectileDamage * mInfo.ProjectileInfo.mProjectileDamageScale * 0.2f);

			mProjectile.Add(Projectile);
			Projectile->mOwner = this;
		}


	}
	break;

	// ���� ������ ����ü�� �ӵ��� ũ�� ������Ű��
	// �ڽ� �ֺ����� ����ü 7���� �����Ѵ�
	case 1:
	{
		int32 Count = mProjectile.Num();
		for (int32 i = 0; i < Count; i++) {

			if (!IsValid(mProjectile[i]))
				continue;

			mProjectile[i]->SetHoming(mInfo.ProjectileInfo.mHoming);
			mProjectile[i]->SetSpeed(mProjectile[i]->GetSpeed() * 3.f);

		}



		float ProjectileToPlayerDist = 200;


		UAudioComponent* mAudio = NewObject<UAudioComponent>(this, TEXT("Audio"));
		mAudio->SetSound(SkillSoundArray[SkillNumber]);
		mAudio->SetVolumeMultiplier(mSkillVolume);
		mAudio->Play();
		

		for (int32 i = 0; i < 7; i++) {

			float Degree = (360.f / 7) * i;
			float Radian = FMath::DegreesToRadians(Degree);

			float dx = FMath::Cos(Radian) * ProjectileToPlayerDist;
			float dy = FMath::Sin(Radian) * ProjectileToPlayerDist;



			FVector ProjectileLocation = FVector(GetActorLocation().X + dx, GetActorLocation().Y + dy, GetActorLocation().Z);
			FRotator ProjectileRotator = (ProjectileLocation - GetActorLocation()).Rotation();

			AParticleNiagara* MuzzleParticle =
				GetWorld()->SpawnActor<AParticleNiagara>(
					ProjectileLocation,
					ProjectileRotator,
					SpawnParam);

			MuzzleParticle->SetParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileMuzzleEffect);
			//MuzzleParticle->SetSound(SkillSoundArray[SkillNumber]);


			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileLocation, ProjectileRotator, SpawnParam);
			Projectile->SetActorScale3D(FVector(1, 1, 1) * mInfo.ProjectileInfo.mProjectileScale);

			mProjectile.Add(Projectile);
			Projectile->mOwner = this;

			Projectile->SetTrailParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileTrailEffect);
			Projectile->SetImpactParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileImpactEffect);



			//Ȯ��
			Projectile->SetVelocity(((ProjectileLocation - GetActorLocation()) / (ProjectileLocation - GetActorLocation()).Size()) * mInfo.ProjectileInfo.mProjectileSpeed * 0.5f);

			Projectile->SetHoming(mInfo.ProjectileInfo.mHoming);

			Projectile->SetDuplicate(mInfo.ProjectileInfo.mDuplicate);

			Projectile->SetDuplicateCount(mInfo.ProjectileInfo.mDuplicateCount/2);


			Projectile->SetSpeed(mInfo.ProjectileInfo.mProjectileSpeed * 0.6f);
			Projectile->SetDuplicateSpeed(mInfo.ProjectileInfo.mProjectileSpeed * 0.3f);

			Projectile->SetDamage(mInfo.ProjectileInfo.mProjectileDamage * mInfo.ProjectileInfo.mProjectileDamageScale * 0.8f);
			Projectile->SetProjectileDuplicateDamage(mInfo.ProjectileInfo.mProjectileDamage * mInfo.ProjectileInfo.mProjectileDamageScale * 0.2f);

		}

	}
	break;

	// ���濡 ū �Ӽ������� ����Ų�� 
	// �ټ��� ������ ū �������� �ش�
	case 2:
	{
		//SpawnParam.Template = mHitActor;
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		mInfo.SkillDataArray[SkillNumber].HitPosition = GetActorLocation() + GetActorForwardVector() * 500.f;

		AParticleNiagara* FirstParticle =
			GetWorld()->SpawnActor<AParticleNiagara>(mInfo.SkillDataArray[SkillNumber].HitPosition
				, GetActorRotation()
				, SpawnParam);

		FirstParticle->SetParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].UltimateEffect);
		FirstParticle->SetSound(SkillSoundArray[SkillNumber]);
		FirstParticle->SetSoundVolumeScale(mSkillVolume);
		//FirstParticle->SetActorScale3D(FVector(10.f, 10.f, 10.f));

		mSkill2Success = true;
	}
	break;

	// ���濡 ū �������� �ִ� ���� ����ü�� �߻��Ѵ�
	// ����ü�� ������ �����ϸ� �ֺ����� 20���� ���� ����ü�� �߻��Ѵ�.
	case 3:
	{

		AParticleNiagara* MuzzleParticle =
			GetWorld()->SpawnActor<AParticleNiagara>(
				GetActorLocation() + GetActorForwardVector() * 100.f,
				GetActorRotation(),
				SpawnParam);

		MuzzleParticle->SetParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileMuzzleEffect);
		MuzzleParticle->SetSound(SkillSoundArray[SkillNumber]);
		MuzzleParticle->SetSoundVolumeScale(mSkillVolume);


		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation(), SpawnParam);

		Projectile->SetTrailParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileTrailEffect);
		Projectile->SetImpactParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileImpactEffect);


		Projectile->mOwner = this;

		Projectile->SetDuplicateCount(20);


		Projectile->SetSpeed(mInfo.ProjectileInfo.mProjectileSpeed * 0.8f);
		Projectile->SetDuplicateSpeed(mInfo.ProjectileInfo.mProjectileSpeed * 2.f);

		float Scale = 8;

		Projectile->SetActorScale3D(FVector(Scale, Scale, Scale));

		Projectile->SetHoming(mInfo.ProjectileInfo.mHoming);
		Projectile->SetDuplicate(true);

		Projectile->SetDamage(mInfo.ProjectileInfo.mProjectileDamage* mInfo.ProjectileInfo.mProjectileDamageScale * 5.f);
		Projectile->SetProjectileDuplicateDamage(mInfo.ProjectileInfo.mProjectileDamage* mInfo.ProjectileInfo.mProjectileDamageScale * 0.2f);
	
		mProjectile.Add(Projectile);
		Projectile->mOwner = this;
	}

	break;
	}


}

void AMagicianPlayerCharacter::ApplyDamage(int32 SkillNumber)
{
	if (mSkillEnable[SkillNumber] == false)
		return;

	switch (SkillNumber) {

	case 0:
	{

	}
	break;


	case 1:
	{
	
	}
	break;

	case 2:
	{
		if (mSkill2Success == false)
			break;

		FCollisionQueryParams	param(NAME_None, false, this);

		TArray<FOverlapResult>	CollisionResult;

		bool CollisionEnable = GetWorld()->OverlapMultiByChannel(CollisionResult,
			mInfo.SkillDataArray[SkillNumber].HitPosition,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel6,
			FCollisionShape::MakeSphere(300),
			param);

		FColor	DrawColor = CollisionEnable ? FColor::Red : FColor::Green;

		DrawDebugSphere(GetWorld(),
			mInfo.SkillDataArray[SkillNumber].HitPosition,
			300, 20, DrawColor, false, 0.5f);

		// Sound
		UAudioComponent* mAudio = NewObject<UAudioComponent>(this, TEXT("Audio"));
		mAudio->SetSound(mInfo.SkillEffect[mSkillEffectAttributeIndex].SkillHitSound);
		mAudio->SetVolumeMultiplier(mSkillVolume);
		mAudio->Play();


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
				if (!IsValid(Cast<ABaseMonster>(CollisionResult[i].GetActor()))) {
					continue;
				}

				AParticleNiagara* Particle =
					GetWorld()->SpawnActor<AParticleNiagara>(
						CollisionResult[i].GetActor()->GetActorLocation(),
						CollisionResult[i].GetActor()->GetActorRotation(),
						SpawnParam);

				Particle->SetParticle(mInfo.SkillEffect[mSkillEffectAttributeIndex].ProjectileImpactEffect);
				//Particle->SetSound(mInfo.SkillEffect[mSkillEffectAttributeIndex].SkillHitSound);

				CollisionResult[i].GetActor()->TakeDamage(
					mInfo.ProjectileInfo.mProjectileDamage * mInfo.ProjectileInfo.mProjectileDamageScale * 8.f,
					FDamageEvent(), GetController(), this);

			}
		}

		mSkill2Success = false;
	}
	break;

	case 3:
	{

	}

	break;
	}


}

void AMagicianPlayerCharacter::Skill1()
{
	if (mSkillEnable[0] == false)
		return;

	else {

		mAnimInst->UseSkill(0);
	}
}

void AMagicianPlayerCharacter::Skill2()
{
	if (mSkillEnable[1] == false)
		return;

	else {

		mAnimInst->UseSkill(1);
	}
}

void AMagicianPlayerCharacter::Skill3()
{
	if (mSkillEnable[2] == false)
		return;

	else {

		mAnimInst->UseSkill(2);
	}
}

void AMagicianPlayerCharacter::Skill4()
{
	if (mSkillEnable[3] == false)
		return;

	else {

		mAnimInst->UseSkill(3);
	}
}

void AMagicianPlayerCharacter::LevelUp()
{
	Super::LevelUp();

	

}

