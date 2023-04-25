// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "../KYTGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();



	m_NewGameBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("NewGame_Btn"))));
	m_ContinueBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("Continue_Btn"))));
	m_EndGameBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("EndGame_Btn"))));
	m_InfiniteBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("Infinite_Btn"))));

	m_SaveSlotBtnArray.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("SaveSlotBtn1")))));
	m_SaveSlotBtnArray.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("SaveSlotBtn2")))));
	m_SaveSlotBtnArray.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("SaveSlotBtn3")))));
	m_SaveSlotBtnArray.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("SaveSlotBtn4")))));


	m_SaveSlotTextArray.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("SaveSlotText1")))));
	m_SaveSlotTextArray.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("SaveSlotText2")))));
	m_SaveSlotTextArray.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("SaveSlotText3")))));
	m_SaveSlotTextArray.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("SaveSlotText4")))));

	


	// Add Dynamic
	m_NewGameBtn->OnClicked.AddDynamic(this, &UMainMenu::OnNewGameBtnClicked);
	m_ContinueBtn->OnClicked.AddDynamic(this, &UMainMenu::OnContinueBtnClicked);
	m_EndGameBtn->OnClicked.AddDynamic(this, &UMainMenu::OnEndGameBtnClicked);
	m_InfiniteBtn->OnClicked.AddDynamic(this, &UMainMenu::OnInfiniteBtnClicked);
	



	m_SaveSlotBtnArray[0]->OnClicked.AddDynamic(this, &UMainMenu::OnSaveSlot1BtnClicked);
	m_SaveSlotBtnArray[1]->OnClicked.AddDynamic(this, &UMainMenu::OnSaveSlot2BtnClicked);
	m_SaveSlotBtnArray[2]->OnClicked.AddDynamic(this, &UMainMenu::OnSaveSlot3BtnClicked);
	m_SaveSlotBtnArray[3]->OnClicked.AddDynamic(this, &UMainMenu::OnSaveSlot4BtnClicked);




	// Save Data를 확인하고 없다면 Continue 비활성화
	
	m_ContinueBtn->SetIsEnabled(false);

	for (int32 i = 0; i < 4; i++) {

		FString FullPath = FPaths::ProjectSavedDir() + TEXT("SaveGames/") + FString::FromInt(i) + TEXT("/Save.txt");

		TSharedPtr<FArchive>	Reader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

		// Save 파일이 존재함
		if (Reader.IsValid()) {

			// 해당 번호의 버튼 활성화
			m_SaveSlotBtnArray[i]->SetIsEnabled(true);
			
		}
		else {

			// 해당 번호의 버튼 비활성화

			m_SaveSlotBtnArray[i]->SetIsEnabled(false);
		}
	}



	m_SelectedSaveSlotIndex = 0;
}



void UMainMenu::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);


}

void UMainMenu::OnNewGameBtnClicked()
{
	//Player->SavePlayer();

	UKYTGameInstance* MyGameInst = Cast<UKYTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(MyGameInst)) {

		// Set Save Index to GameInstance
		MyGameInst->SetCurrentSaveIndex(-1);

		// Open Level
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Dungeon"));
	}
	
	
	

}

void UMainMenu::OnContinueBtnClicked()
{
	UKYTGameInstance* MyGameInst = Cast<UKYTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(MyGameInst)) {

		// Set Save Index to GameInstance
		MyGameInst->SetCurrentSaveIndex(m_SelectedSaveSlotIndex);

		// Open Level
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Dungeon"));
	}

}

void UMainMenu::OnEndGameBtnClicked()
{
	UGameplayStatics::GetGameInstance(GetWorld());
	
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);

}

void UMainMenu::OnInfiniteBtnClicked()
{
	UKYTGameInstance* MyGameInst = Cast<UKYTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(MyGameInst)) {

		// Set Save Index to GameInstance
		MyGameInst->SetCurrentSaveIndex(m_SelectedSaveSlotIndex);

		// Open Level
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("Infinite"));
	}

}

void UMainMenu::SaveSlotBtnClicked(int32 Index)
{
	m_SelectedSaveSlotIndex = Index;

	// Font Size 25 -> 30
	FSlateFontInfo FontInfo = m_SaveSlotTextArray[Index]->Font;
	
	for (int32 i = 0; i < 4; i++) {
		
		if (i == Index)
			FontInfo.Size = 30;
		else
			FontInfo.Size = 25;

		m_SaveSlotTextArray[i]->SetFont(FontInfo);
	}

	m_ContinueBtn->SetIsEnabled(true);
}

void UMainMenu::OnSaveSlot1BtnClicked()
{
	SaveSlotBtnClicked(0);
}

void UMainMenu::OnSaveSlot2BtnClicked()
{
	SaveSlotBtnClicked(1);
}

void UMainMenu::OnSaveSlot3BtnClicked()
{
	SaveSlotBtnClicked(2);
}

void UMainMenu::OnSaveSlot4BtnClicked()
{
	SaveSlotBtnClicked(3);
}
