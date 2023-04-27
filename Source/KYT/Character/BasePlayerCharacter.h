// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "BaseCharacter.h"
#include "../Monster/BaseMonster.h"
#include "CameraAnimationSequence.h"

#include "BasePlayerCharacter.generated.h"

/**
 * 
 */


UCLASS()
class KYT_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

	friend class ARandomRoomGameMode;


public:
	// Sets default values for this character's properties
	ABasePlayerCharacter();
	//


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
		USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
		UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
		USceneCaptureComponent2D* mSceneCapture2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Component, meta = (AllowPrivateAccess = true))
	UMaterial* mMinimapMaterial;
	
	//Move & Dash
	float	mMoveForwardDir;
	float	mMoveDir;

	float	mDashCoolTime;
	float	mDashCurrentCoolTime;

	class UPlayerAnimInstance* mAnimInst;
	bool	mDeath;

	AActor* mHitActor;


	class AWeaponActor* mWeapon;

	bool mMovable;
	FVector mStopLocation;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FPlayerCharacterInfo		mInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))	
	FName				mPlayerTableRowName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		TArray<bool> mSkillEnable;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		int32 mSkillEffectAttributeIndex;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UCameraAnimationSequence* mNormalAttackCameraShakeSequence;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float mNormalAttackVolume = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float  mSkillVolume = 0.6f;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FRotator GetSpringArmRelativeRotation() { 
		
		return mSpringArm->GetRelativeRotation(); 
	}

	void SetSpringArmRelativeRotation(FRotator Rotator) {
		
		mSpringArm->SetRelativeRotation(Rotator);
	}

	FPlayerCharacterInfo GetPlayerInfo() {

		return mInfo;
	}

	void SetPlayerInfo(FPlayerCharacterInfo Info) {

		mInfo = Info;
	}


	UCameraComponent* GetCamera() {

		return mCamera;
	}

	int32 GetSkillEffectAttributeIndex() {

		return mSkillEffectAttributeIndex;
	}

public:

	void MoveForward(float Scale);
	void MoveSide(float Scale);

	void Jump();
	void MouseMove();
	virtual void NormalAttack();
	virtual void NormalAttackEffect(int32 ComboCount);

	void RotationCameraZ(float Scale);
	void CameraZoom(float Scale);

	void SetPlayerMovable(bool Movable);


	void SetAttribute(EPlayerAttribute PlayerAttribute);

	void SetAttributeLevel(EPlayerAttribute PlayerAttribute, int32 Level)
	{
		mInfo.PlayerAttributeLevel[(int32)PlayerAttribute] = Level;
	}



public:


	void PlayerLevelUpScreen();
	void DecreasePlayerLevel()
	{
		mInfo.Level--;
	}


public:

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	virtual void UseSkill(int32 SkillNumber);
	virtual void ApplyDamage(int32 SkillNumber);

	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill3();
	virtual void Skill4();

	virtual void Dash();



	virtual void GetExp(float Exp);
	virtual void LevelUp();

	virtual void PlayerInfoMenu();



public:

	virtual void SyncPlayerStatus();



public:

	UMaterial* GetMinimapMaterial()
	{
		return mMinimapMaterial;
	}



public:	
	void Test();
};
