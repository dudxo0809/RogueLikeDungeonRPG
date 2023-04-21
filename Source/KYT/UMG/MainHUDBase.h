// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <Blueprint\UserWidget.h>

#include "PlayerStatus.h"
#include "PlayerLevelUp.h"
#include "Minimap.h"
#include "PlayerInfoMenu.h"

#include "../Character/CharacterInfo.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API UMainHUDBase : public UUserWidget
{
	GENERATED_BODY()
	

private:

	UPlayerStatus*  m_PlayerStatus;
	UPlayerLevelUp* m_PlayerLevelUp;
	UMinimap*		m_Minimap;
	UPlayerInfoMenu* m_PlayerInfoMenu;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


public:

	UMinimap* GetMiniMap()
	{
		return m_Minimap;
	}

	UPlayerInfoMenu* GetPlayerInfoMenu() {

		return m_PlayerInfoMenu;
	}



public:

	void SetHP(float Ratio);
	void SetMP(float Ratio);
	void SetExp(float Ratio);
	void SetLevel(int32 Level);

	void SetSkillImage(int32 SkillIndex, bool Enable);

	void SetStageNumber(int32 StageNumber);

	void SetAttributeLevel();

public:


	void ShowPlayerLevelUp(FPlayerCharacterInfo PlayerInfo);
	void HidePlayerLevelUp();

	void ShowPlayerInfoMenu();
	void HidePlayerInfoMenu();

	bool IsPlayerLevelUpScreenShow();
	bool IsPlayerInfoMenuScreenShow();
};
