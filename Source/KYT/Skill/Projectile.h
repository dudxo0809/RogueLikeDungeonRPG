// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "ParticleNiagara.h"
#include "../Monster/BaseMonster.h"
#include "../Character/BasePlayerCharacter.h"


#include "Projectile.generated.h"

UCLASS()
class KYT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UProjectileMovementComponent* mProjectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UNiagaraComponent* mTrailParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UNiagaraComponent* mImpactParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FString  mImpactParticlePath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	 mProjectileSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	 mProjectileDamage;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool mHoming;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		ABaseMonster* mTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	 mHomingRadius;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool mRotate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		ABasePlayerCharacter* mPlayer;
	


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool mDuplicate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32 mDuplicateCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	 mDuplicateSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	 mProjectileDuplicateDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float mDuplicateProbability;


	UNiagaraSystem* mImpactParticleSystem;

	float			mDistance;
	FVector			mPrevLocation;


public:

	ABasePlayerCharacter* mOwner;

	FVector mRotatePrevLocation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UProjectileMovementComponent* GetProjectile()const { 
		
		return mProjectile; 
	}

	void SetDistance(float Distance) { 
		
		mDistance = Distance; 
	}

	void SetSpeed(float Speed) {

		mProjectile->Velocity = (mProjectile->Velocity / mProjectile->Velocity.Size()) * Speed;
		mProjectileSpeed = Speed;
	}

	float GetSpeed() {

		return mProjectileSpeed;
	}

	FVector GetVelocity() {

		return mProjectile->Velocity;
	}

	void SetVelocity(FVector NewVelocity) {

		mProjectile->Velocity = NewVelocity;
	}

	void SetRotate(ABasePlayerCharacter* Player, bool Rotate) {

		mPlayer = Player;
		mRotate = Rotate;
	}

	void SetDuplicate(bool Duplicate) {

		mDuplicate = Duplicate;
	}

	void SetDuplicateCount(int32 Count) {

		mDuplicateCount = Count;
	}

	void SetDamage(float Damage) {

		mProjectileDamage = Damage;
	}

	void SetDuplicateSpeed(float Speed) {

		mDuplicateSpeed = Speed;
	}

	void SetProjectileDuplicateDamage(float Damage) {

		mProjectileDuplicateDamage = Damage;
	}

	void SetProjectileDuplicateProbability(float Probability) {

		mDuplicateProbability = Probability;
	}


public:


	virtual void SetTrailParticle(UNiagaraSystem* Particle);
	virtual void SetTrailParticle(const FString& Path);


	virtual void SetImpactParticle(UNiagaraSystem* Particle);
	virtual void SetImpactParticle(const FString& Path);
	virtual void SetImpactParticlePath(const FString& Path);

	void SetHoming(bool Homing) {

		mHoming = Homing;
		
	}
	
	ABaseMonster* GetTarget();

	void CheckDistance();
	void CheckCollision();

	void DuplicateProjectile(ABaseMonster* HitMonster, int32 ProjectileCount, float ProjectileToPlayerDist, float ProjectileSpeed);

	void Homing();

};
