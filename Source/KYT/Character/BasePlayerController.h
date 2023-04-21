// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterInfo.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
class USequenceCameraShakePattern;

UCLASS()
class KYT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

protected:
	// TWeakPtr�� ����ī������ ���Ѵ�.
	// ����� �Ҹ��ϸ� �ڵ����� nullptr�� �ȴ�.
	// TWeakPtr�� UObject�� ���ٷ��.
	// TWeakObjectPtr�� UObject�� �ٷ��.
	TWeakObjectPtr<AActor> mPickActor;
	//class ADecal* mMousePick;

	UPROPERTY()
	UCameraShakeBase*	m_CameraShake;
	
	UPROPERTY()
	TSubclassOf<UCameraShakeBase> m_CameraShakeClass;
	
	UPROPERTY()
	USequenceCameraShakePattern* m_Pattern;


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent();
	virtual void PostInitializeComponents() override;

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

public:
	
	void AttackCameraShake();

};
