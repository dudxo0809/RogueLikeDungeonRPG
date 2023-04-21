// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include <Components/Image.h>
#include "Components/Button.h"

#include "../Character/CharacterInfo.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoMenu.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API UPlayerInfoMenu : public UUserWidget
{
	GENERATED_BODY()

private:

	// Has 8 elements
	TArray<UButton*> mAttributeBtn;

	UButton* mOkBtn;
	UButton* mNoBtn;
	
	UTextBlock* mChooseAttributeDescription;

	UButton* mSaveGameBtn;
	UButton* mEndGameBtn;

private:

	TArray<UTextBlock*> mPlayerInfo;

	TArray<FText> mAttributeName;

public:


	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


	void SetInit();


public:

	void OnMyBtnClicked(int32 Index);

	UFUNCTION()
		void OnArcaneBtnClicked();

	UFUNCTION()
		void OnFireBtnClicked();

	UFUNCTION()
		void OnIceBtnClicked();

	UFUNCTION()
		void OnThunderBtnClicked();

	UFUNCTION()
		void OnPoisonBtnClicked();

	UFUNCTION()
		void OnHolyBtnClicked();

	UFUNCTION()
		void OnShadowBtnClicked();

	UFUNCTION()
		void OnVoidBtnClicked();




public:


	UFUNCTION()
		void OnOkBtnClicked();

	UFUNCTION()
		void OnNoBtnClicked();



	UFUNCTION()
		void OnSaveGameBtnClicked();

	UFUNCTION()
		void OnEndGameBtnClicked();

};
