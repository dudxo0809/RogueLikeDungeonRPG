// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../GameInfo.h"
#include "../Skill/ParticleNiagara.h"
#include "../Monster/BaseMonster.h"
#include "../Character/BasePlayerCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExpProjectile.generated.h"

UCLASS()
class KYT_API AExpProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExpProjectile();



protected:


	//Effect
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UProjectileMovementComponent* mProjectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UNiagaraComponent* mTrailParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UNiagaraComponent* mImpactParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		FString  mImpactParticlePath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UNiagaraSystem* mImpactParticleSystem;


	// Homing
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool mHoming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		ABasePlayerCharacter* mTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	 mHomingRadius;



	// Member
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	 mProjectileSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		float	 mProjectileExp;


public:


	void SetSpeed(float Speed)
	{
		mProjectile->Velocity = (mProjectile->Velocity / mProjectile->Velocity.Size()) * Speed;
		mProjectileSpeed = Speed;
	}

	float GetSpeed()
	{

		return mProjectileSpeed;
	}

	FVector GetVelocity()
	{

		return mProjectile->Velocity;
	}

	void SetVelocity(FVector NewVelocity)
	{

		mProjectile->Velocity = NewVelocity;
	}

	void SetExp(float Exp)
	{
		mProjectileExp = Exp;
	}

	void SetHoming(bool Homing)
	{

		mHoming = Homing;

	}



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




public:


	virtual void SetTrailParticle(UNiagaraSystem* Particle);
	virtual void SetTrailParticle(const FString& Path);


	virtual void SetImpactParticle(UNiagaraSystem* Particle);
	virtual void SetImpactParticle(const FString& Path);
	virtual void SetImpactParticlePath(const FString& Path);


	ABasePlayerCharacter* GetTarget();

	void CheckCollision();

	void Homing();

};
