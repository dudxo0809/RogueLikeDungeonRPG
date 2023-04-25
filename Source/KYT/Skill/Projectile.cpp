// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "../Character/MagicianPlayerCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	mTrailParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));

	mProjectile->SetUpdatedComponent(RootComponent);
	mProjectile->ProjectileGravityScale = 0;

	
	mDistance = 10000.f;

	mHoming = false;
	mHomingRadius = 5000.f;

	

}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();


	mPrevLocation = GetActorLocation();
	

	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 일정거리 이동 후 자동 삭제
	CheckDistance();
	
	// 몬스터와 접촉 시 데미지
	// mDuplicate 가 참일 경우 주변으로 투사체 생성
	CheckCollision();

	// 유도 기능
	Homing();

}

void AProjectile::SetTrailParticle(UNiagaraSystem* Particle)
{
	if (IsValid(Particle))
		mTrailParticle->SetAsset(Particle);
}

void AProjectile::SetTrailParticle(const FString& Path)
{
	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(
		nullptr, *Path);

	if (IsValid(Particle))
		mTrailParticle->SetAsset(Particle);
}

void AProjectile::SetImpactParticle(UNiagaraSystem* Particle)
{
	if (IsValid(Particle))
		mImpactParticleSystem = Particle;
}

void AProjectile::SetImpactParticle(const FString& Path)
{
	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(
		nullptr, *Path);
	if (IsValid(Particle))
		mImpactParticleSystem = Particle;
}

void AProjectile::SetImpactParticlePath(const FString& Path)
{
	
	mImpactParticlePath = Path;
}	


ABaseMonster* AProjectile::GetTarget()
{
	FCollisionQueryParams	param(NAME_None, false, this);

	TArray<FHitResult>	CollisionResult;
	bool CollisionEnable = GetWorld()->SweepMultiByChannel(
		CollisionResult, GetActorLocation(),
		GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,				// PlayerAttack
		FCollisionShape::MakeSphere(mHomingRadius),
		param);

	float TargetMinDist = 100000;
	ABaseMonster* TargetMonster = nullptr;

	if (CollisionEnable)
	{
		int32	Count = CollisionResult.Num();

		for (int32 i = 0; i < Count; ++i)
		{
			ABaseMonster* Monster = Cast<ABaseMonster>(CollisionResult[i].GetActor());
			if (!IsValid(Monster))
				continue;

			float TargetDist = FMath::Abs((Monster->GetActorLocation() - GetActorLocation()).Size());

			if (TargetMinDist > TargetDist) {

				TargetMinDist = TargetDist;
				TargetMonster = Monster;

			}

			
		}

		
	}

	return TargetMonster;
}

void AProjectile::CheckDistance()
{
	float Dist = FVector::Distance(mPrevLocation, GetActorLocation());

	if (Dist > mDistance)
	{
		AMagicianPlayerCharacter* Magician = Cast<AMagicianPlayerCharacter>(mOwner);

		if (IsValid(Magician)) {

			Magician->mProjectile.Remove(this);
		}
		Destroy();
	}
}

void AProjectile::CheckCollision() {


	FCollisionQueryParams	param(NAME_None, false, this);

	TArray<FHitResult>	CollisionResult;
	bool CollisionEnable = GetWorld()->SweepMultiByChannel(
		CollisionResult, GetActorLocation(),
		GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6,				// PlayerAttack
		FCollisionShape::MakeSphere(20.f),
		param);


	if (CollisionEnable)
	{
		int32	Count = CollisionResult.Num();

		AMagicianPlayerCharacter* Magician = Cast<AMagicianPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		for (int32 i = 0; i < Count; ++i)
		{
			FActorSpawnParameters	SpawnParam;
			//SpawnParam.Template = mHitActor;
			SpawnParam.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


			AParticleNiagara* Particle =
				GetWorld()->SpawnActor<AParticleNiagara>(
					GetActorLocation(),
					GetActorRotation(),
					SpawnParam);

		
			Particle->SetParticle(mImpactParticleSystem);

			if (IsValid(Cast<ABaseMonster>(CollisionResult[i].GetActor()))) 
			{
				int32 SkillEffectAttributeIndex = Magician->GetSkillEffectAttributeIndex();
				Particle->SetSound(Magician->GetPlayerInfo().SkillEffect[SkillEffectAttributeIndex].ProjectileHitSound);

				Particle->SetSoundVolumeScale(0.3f);
			}
			

			ABaseMonster* Monster = Cast<ABaseMonster>(CollisionResult[i].GetActor());
			if (!IsValid(Monster))
				continue;

			CollisionResult[i].GetActor()->TakeDamage(
				mProjectileDamage,
				FDamageEvent(), nullptr, this);
			//Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonYin/FX/Particles/Yin/Abilities/Primary/FX/P_Yin_Primary_Impact.P_Yin_Primary_Impact'"));


			if (mDuplicate) {

				float Probability = Magician->GetPlayerInfo().ProjectileInfo.mDuplicateProbability;
				float PickNum = FMath::RandRange(0.f, 100.f);

				if (PickNum <= Probability) {

					DuplicateProjectile(Monster, mDuplicateCount, 200, mDuplicateSpeed);
				}

			}
			
		}

		if (IsValid(Magician)) {
			Magician->mProjectile.Remove(this);
		}
		Destroy();
	}


}

void AProjectile::DuplicateProjectile(ABaseMonster* HitMonster, int32 ProjectileCount, float ProjectileToPlayerDist, float ProjectileSpeed)
{
	if (mDuplicate) {

		AMagicianPlayerCharacter* Magician = Cast<AMagicianPlayerCharacter>(mOwner);

		if (IsValid(Magician)) {

			Magician->mProjectile.Remove(this);
		}

		if (!IsValid(HitMonster)) {

			return;
		}


		if (IsValid(Magician) && Magician != nullptr) {
			
			
			int32 AttributeIndex = Magician->GetSkillEffectAttributeIndex();
			
			FActorSpawnParameters	SpawnParam;



			float RandomDegreeOffset = FMath::RandRange(0.f, 360.f);

			for (int32 i = 0; i < ProjectileCount; i++) {

				float Degree = RandomDegreeOffset + (360.f / ProjectileCount) * i;
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

				MuzzleParticle->SetParticle(Magician->GetPlayerInfo().SkillEffect[AttributeIndex].ProjectileMuzzleEffect);
				//MuzzleParticle->SetSound(TEXT("SoundWave'/Game/Sound/Fire1.Fire1'"));


				AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileLocation, ProjectileRotator, SpawnParam);

				Projectile->SetTrailParticle(Magician->GetPlayerInfo().SkillEffect[AttributeIndex].ProjectileTrailEffect);
				Projectile->SetImpactParticle(Magician->GetPlayerInfo().SkillEffect[AttributeIndex].ProjectileImpactEffect);

				Projectile->SetDamage(mProjectileDuplicateDamage);

				Projectile->SetSpeed(ProjectileSpeed);
				Projectile->SetHoming(Magician->GetIsHoming());

				//확산
				Projectile->SetVelocity(((ProjectileLocation - GetActorLocation()) / (ProjectileLocation - GetActorLocation()).Size()) * ProjectileSpeed);

			}
		}

	}
}

void AProjectile::Homing()
{
	if (mHoming) {



		if (!IsValid(mTarget) || mTarget == nullptr) {

			mTarget = GetTarget();

			if (!IsValid(mTarget) || mTarget == nullptr) {

				mHoming = false;

				return;
			}
		}

		if (mTarget->IsDead()) {


			mTarget = GetTarget();

			if (!IsValid(mTarget) || mTarget == nullptr) {

				mHoming = false;

				return;
			}
		}

		FVector TargetLocation = mTarget->GetActorLocation();

		// Size == 1.f;
		FVector ProjectileDirecion = mProjectile->Velocity / mProjectile->Velocity.Size();
		FVector TargetDirection = ((TargetLocation - GetActorLocation()) / (TargetLocation - GetActorLocation()).Size());

		FVector InterpDirection = (85 * ProjectileDirecion + 15 * TargetDirection) / 100;

		mProjectile->Velocity = InterpDirection * mProjectileSpeed;


		SetActorRotation(mProjectile->Velocity.Rotation());

	}
}

