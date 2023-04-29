// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpProjectile.h"

// Sets default values
AExpProjectile::AExpProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	mTrailParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));

	mProjectile->SetUpdatedComponent(RootComponent);
	mProjectile->ProjectileGravityScale = 0;

	mHoming = true;
	mHomingRadius = 5000.f;
}

// Called when the game starts or when spawned
void AExpProjectile::BeginPlay()
{
	Super::BeginPlay();
	

	mTarget = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

// Called every frame
void AExpProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// 플레이어와 접촉 시 경험치
	CheckCollision();

	// 유도 기능
	Homing();

}




ABasePlayerCharacter* AExpProjectile::GetTarget()
{
	mTarget = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!IsValid(mTarget))
		mTarget = nullptr;
	/*
	FCollisionQueryParams	param(NAME_None, false, this);

	FHitResult	CollisionResult;
	bool CollisionEnable = GetWorld()->SweepSingleByChannel(
		CollisionResult, GetActorLocation(),
		GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8,				// MonsterAttack
		FCollisionShape::MakeSphere(mHomingRadius),
		param);

	ABasePlayerCharacter* TargetPlayer = nullptr;

	if (CollisionEnable)
	{
		TargetPlayer = Cast<ABasePlayerCharacter>(CollisionResult.GetActor());

		if (!IsValid(TargetPlayer))
			return nullptr;
	}
	*/

	return mTarget;
}


void AExpProjectile::CheckCollision()
{

	FCollisionQueryParams	param(NAME_None, false, this);

	FHitResult	CollisionResult;
	bool CollisionEnable = GetWorld()->SweepSingleByChannel(
		CollisionResult, GetActorLocation(),
		GetActorLocation(), FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel8,				// PlayerAttack
		FCollisionShape::MakeSphere(20.f),
		param);


	if (CollisionEnable)
	{
		ABasePlayerCharacter* MyPlayer = Cast<ABasePlayerCharacter>(CollisionResult.GetActor());
		if (!IsValid(MyPlayer))
			return;

		FActorSpawnParameters	SpawnParam;
		//SpawnParam.Template = mHitActor;
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		AParticleNiagara* Particle =
			GetWorld()->SpawnActor<AParticleNiagara>(
				GetActorLocation(),
				GetActorRotation(),
				SpawnParam);

		if (Particle && IsValid(Particle))
		{
			Particle->SetParticle(mImpactParticleSystem);
			//Particle->SetSound(TEXT("SoundWave'/Game/Sound/Fire1.Fire1'"));
		}

		float ExpScale = 1 + (MyPlayer->GetPlayerInfo().BasicUpgradeInfo.mExpLevel * 0.1f);

		MyPlayer->GetExp(mProjectileExp * ExpScale);

		Destroy();
	}

}

void AExpProjectile::Homing()
{
	if (mHoming) {

		if (!IsValid(mTarget) || mTarget == nullptr) {

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

		FVector InterpDirection = (75 * ProjectileDirecion + 25 * TargetDirection) / 100;

		mProjectile->Velocity = InterpDirection * mProjectileSpeed;


		SetActorRotation(mProjectile->Velocity.Rotation());

	}
}



//


void AExpProjectile::SetTrailParticle(UNiagaraSystem* Particle)
{
	if (IsValid(Particle))
		mTrailParticle->SetAsset(Particle);
}

void AExpProjectile::SetTrailParticle(const FString& Path)
{
	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(
		nullptr, *Path);

	if (IsValid(Particle))
		mTrailParticle->SetAsset(Particle);
}

void AExpProjectile::SetImpactParticle(UNiagaraSystem* Particle)
{
	if (IsValid(Particle))
		mImpactParticleSystem = Particle;
}

void AExpProjectile::SetImpactParticle(const FString& Path)
{
	UNiagaraSystem* Particle = LoadObject<UNiagaraSystem>(
		nullptr, *Path);
	if (IsValid(Particle))
		mImpactParticleSystem = Particle;
}

void AExpProjectile::SetImpactParticlePath(const FString& Path)
{
	mImpactParticlePath = Path;
}
