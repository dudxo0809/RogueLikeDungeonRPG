// Copyright Epic Games, Inc. All Rights Reserved.


#include "KYTGameModeBase.h"

AKYTGameModeBase::AKYTGameModeBase()
{
	// Tick �Լ� ȣ��
	PrimaryActorTick.bCanEverTick = true;

	// UI_MainHUD �������Ʈ Ŭ���� �� UClass ������ �����´�.
	ConstructorHelpers::FClassFinder<UUserWidget>
		finder(TEXT("WidgetBlueprint'/Game/KYT/UMG/UI_MainHUD.UI_MainHUD_C'"));

	if (finder.Succeeded())
	{
		m_MainHUDClass = finder.Class;
	}



	mAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	SetRootComponent(mAudio);
}

void AKYTGameModeBase::BeginPlay()
{
	Super::BeginPlay();


}

void AKYTGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


}

void AKYTGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);


}

void AKYTGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);


}

void AKYTGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
