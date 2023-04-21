// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "BasePlayerCharacter.h"

#include "SequenceCameraShake.h"


ABasePlayerController::ABasePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	//bFindCameraComponentWhenViewTarget = true;
	//bShowMouseCursor = true;

	m_CameraShake = nullptr;
	m_Pattern = nullptr;

}

void ABasePlayerController::BeginPlay()
{
	// Super :: �ڱ��ڽ��� �θ�Ŭ������ �ǹ��Ѵ�.
	Super::BeginPlay();


	FInputModeGameAndUI GameUI;
	//FInputModeGameOnly GameOnly;
	SetInputMode(GameUI);

	


	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

	PlayerCameraManagerClass = APlayerCameraManager::StaticClass();

	
	m_CameraShake = NewObject<UCameraShakeBase>(this, TEXT("CameraShake"));
	m_Pattern = NewObject<USequenceCameraShakePattern>(this, TEXT("Pattern"));

}



void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AttackCameraShake();
	
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAxis<>();
}

void ABasePlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// �÷��̾� ��Ʈ�ѷ��� Pawn�� ���ǵɶ� ȣ��ȴ�.
void ABasePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

// �÷��̾� ��Ʈ�ѷ��� ���ǿ��� �����ɶ� ȣ��ȴ�.
void ABasePlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABasePlayerController::AttackCameraShake()
{

	ABasePlayerCharacter* MyPlayer = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!IsValid(MyPlayer))
		return;
			
	UCameraAnimationSequence* Seq = MyPlayer->mNormalAttackCameraShakeSequence;

	//USequenceCameraShakePattern

	m_Pattern->Sequence = Seq;
	m_Pattern->PlayRate = 5.f;
	m_Pattern->Scale = 2.f;
	m_Pattern->BlendInTime = 0.2f;
	m_Pattern->BlendOutTime = 0.4f;

	m_CameraShake->SetRootShakePattern(m_Pattern);

	m_CameraShakeClass = m_CameraShake->GetClass();

	
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(m_CameraShakeClass);


}
