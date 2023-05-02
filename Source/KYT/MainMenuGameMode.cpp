// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"


AMainMenuGameMode::AMainMenuGameMode() {

	// Tick 함수 호출
	PrimaryActorTick.bCanEverTick = true;

	// UI_MainHUD 블루프린트 클래스 의 UClass 정보를 가져온다.
	ConstructorHelpers::FClassFinder<UUserWidget>
		finder(TEXT("WidgetBlueprint'/Game/KYT/UMG/UI_MainMenu.UI_MainMenu_C'"));

	if (finder.Succeeded())
	{
		m_MainMenuClass = finder.Class;
	}

	
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Input Mode
	FInputModeUIOnly UIOnly;
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(UIOnly);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);


	// Sound
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/RPG_Dungeon_Themes/WAVs/Dungeon_8_Where_Art_Thou/WAV_Where_Art_Thou_Version_01_LOOP.WAV_Where_Art_Thou_Version_01_LOOP'"));

	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);
		mAudio->SetVolumeMultiplier(0.8f);

		mAudio->Play();
	}

	// Add Viewport
	// 위젯 블루프린트 UClass 정보를 이용해서 객체를 만들어낸다.
	if (IsValid(m_MainMenuClass))
	{
		// 생성한 객체의 주소를 m_MainHUD 에 받아둔다.
		m_MainMenu = Cast<UMainMenu>(CreateWidget(GetWorld(), m_MainMenuClass));
		if (IsValid(m_MainMenu))
		{
			m_MainMenu->AddToViewport();
		}
	}

}

void AMainMenuGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);


}

void AMainMenuGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);



}

void AMainMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);



}

void AMainMenuGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}
