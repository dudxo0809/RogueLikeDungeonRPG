// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TextBlock.h"
#include <Components/Image.h>
#include "Components/Button.h"

#include "../Character/CharacterInfo.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerLevelUp.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API UPlayerLevelUp : public UUserWidget
{
	GENERATED_BODY()

private:

	UTextBlock* mPlayerLevel;
	
	// Has 4 elements
	TArray<UImage*> mChoiceIcon;
	TArray<UTextBlock*> mChoiceDescription;
	TArray<UButton*> mChoiceBtn;

	UButton* mOkBtn;
	UButton* mNoBtn;
	UTextBlock* mExitDescription;
	

private:

	TArray<FPlayerSkillUpgradeInfo> mPlayerSkillUpgradeArray;

	TArray<FName> mExitDescriptionArray;

public:



	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


public:

	void SetPlayerLevel(int32 Level);

	void SetSkillUpgradeInfo(TArray<FPlayerSkillUpgradeInfo> InfoArray);

	FName SetExitDescriptionRandom();

public:

	UFUNCTION()
	void OnChoice1BtnClicked();

	UFUNCTION()
	void OnChoice2BtnClicked();

	UFUNCTION()
	void OnChoice3BtnClicked();

	UFUNCTION()
	void OnChoice4BtnClicked();



	UFUNCTION()
	void OnOkBtnClicked();

	UFUNCTION()
	void OnNoBtnClicked();
	
};
