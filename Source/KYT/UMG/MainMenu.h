// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Setting.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	

private:

	UButton* m_NewGameBtn;
	UButton* m_ContinueBtn;
	UButton* m_EndGameBtn;
	UButton* m_InfiniteBtn;
	UButton* m_SettingBtn;
	UButton* m_DeleteBtn;

private:

	USetting* m_Setting;


private:

	TArray<UButton*> m_SaveSlotBtnArray;
	TArray<UTextBlock*> m_SaveSlotTextArray;

private:

	int32 m_SelectedSaveSlotIndex;

	bool bSaveBtnClicked;


public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


public:

	UFUNCTION()
		void OnNewGameBtnClicked();

	UFUNCTION()
		void OnContinueBtnClicked();

	UFUNCTION()
		void OnEndGameBtnClicked();

	UFUNCTION()
		void OnInfiniteBtnClicked();

	UFUNCTION()
		void OnSettingBtnClicked();

	UFUNCTION()
		void OnDeleteBtnClicked();


public:

	void SaveSlotBtnClicked(int32 Index);

	UFUNCTION()
		void OnSaveSlot1BtnClicked();

	UFUNCTION()
		void OnSaveSlot2BtnClicked();

	UFUNCTION()
		void OnSaveSlot3BtnClicked();

	UFUNCTION()
		void OnSaveSlot4BtnClicked();

	
};
