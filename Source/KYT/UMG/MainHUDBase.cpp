// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDBase.h"

#include "Kismet/GameplayStatics.h"
#include "../Character/BasePlayerCharacter.h"


void UMainHUDBase::NativeConstruct()
{
	Super::NativeConstruct();


	m_PlayerStatus  = nullptr;
	m_PlayerLevelUp = nullptr;
	m_Minimap		= nullptr;

	m_PlayerStatus = Cast<UPlayerStatus>(GetWidgetFromName(FName(TEXT("UI_PlayerStatus"))));
	m_PlayerLevelUp = Cast<UPlayerLevelUp>(GetWidgetFromName(FName(TEXT("UI_PlayerLevelUp"))));
	m_Minimap = Cast<UMinimap>(GetWidgetFromName(FName(TEXT("UI_Minimap"))));
	m_PlayerInfoMenu = Cast<UPlayerInfoMenu>(GetWidgetFromName(FName(TEXT("UI_PlayerInfoMenu"))));



	m_PlayerLevelUp->SetVisibility(ESlateVisibility::Hidden);
	m_PlayerInfoMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UMainHUDBase::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);


}

void UMainHUDBase::SetHP(float Ratio)
{
	m_PlayerStatus->SetHP(Ratio);
}

void UMainHUDBase::SetMP(float Ratio)
{
	m_PlayerStatus->SetMP(Ratio);
}

void UMainHUDBase::SetExp(float Ratio)
{
	m_PlayerStatus->SetExp(Ratio);
}

void UMainHUDBase::SetLevel(int32 Level)
{
	m_PlayerStatus->SetLevel(Level);
}

void UMainHUDBase::SetSkillImage(int32 SkillIndex, bool Enable)
{
	m_PlayerStatus->SetSkillImage(SkillIndex, Enable);
}

void UMainHUDBase::SetStageNumber(int32 StageNumber)
{
	m_PlayerStatus->SetStageNumber(StageNumber);
}

void UMainHUDBase::SetAttributeLevel()
{
	m_PlayerStatus->SetAttributeLevel();
}

// 캐릭터 레벨업 시 한번만 호출됨
void UMainHUDBase::ShowPlayerLevelUp(FPlayerCharacterInfo PlayerInfo)
{
	if (m_PlayerLevelUp == nullptr)
		return;


	ABasePlayerCharacter* MyPlayer = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(MyPlayer))
		return;

	TArray<FPlayerSkillUpgradeInfo> SelectedSkillArray;

	int32 UpgradableSkillCount = MyPlayer->GetPlayerInfo().PlayerUpgradeSkillArray.Num();


	if (UpgradableSkillCount <= 4) {

		for (int32 i = 0; i < UpgradableSkillCount; i++)
		{
			SelectedSkillArray.Add(MyPlayer->GetPlayerInfo().PlayerUpgradeSkillArray[i]);
		}
	}
	else {

		TArray<int32> IndexArray;
		
		while (IndexArray.Num() < 4) {

			int32 Index = FMath::RandRange(0, UpgradableSkillCount - 1);
			if (!IndexArray.Contains(Index))
				IndexArray.Add(Index);
		}
		
		for (auto i : IndexArray) {

			SelectedSkillArray.Add(MyPlayer->GetPlayerInfo().PlayerUpgradeSkillArray[i]);
		}
	}
	


	m_PlayerLevelUp->SetSkillUpgradeInfo(SelectedSkillArray);

	m_PlayerLevelUp->SetPlayerLevel(PlayerInfo.Level);
	
	m_PlayerLevelUp->SetVisibility(ESlateVisibility::Visible);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UMainHUDBase::HidePlayerLevelUp()
{
	if (m_PlayerLevelUp == nullptr)
		return;

	m_PlayerLevelUp->SetVisibility(ESlateVisibility::Hidden);

	
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UMainHUDBase::ShowPlayerInfoMenu()
{
	if (m_PlayerInfoMenu == nullptr)
		return;


	m_PlayerInfoMenu->SetInit();

	m_PlayerInfoMenu->SetVisibility(ESlateVisibility::Visible);


	//UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UMainHUDBase::HidePlayerInfoMenu()
{
	if (m_PlayerInfoMenu == nullptr)
		return;

	

	m_PlayerInfoMenu->SetVisibility(ESlateVisibility::Hidden);


	//UGameplayStatics::SetGamePaused(GetWorld(), false);
}

bool UMainHUDBase::IsPlayerLevelUpScreenShow()
{
	if (m_PlayerLevelUp == nullptr)
		return false;


	if (m_PlayerLevelUp->Visibility == ESlateVisibility::Visible)
	{
		return true;
	}

	else if (m_PlayerLevelUp->Visibility == ESlateVisibility::Hidden)
	{
		return false;
	}
	
	
	return false;
}

bool UMainHUDBase::IsPlayerInfoMenuScreenShow()
{
	if (m_PlayerInfoMenu == nullptr)
		return false;


	if (m_PlayerInfoMenu->Visibility == ESlateVisibility::Visible)
	{
		return true;
	}

	else if (m_PlayerInfoMenu->Visibility == ESlateVisibility::Hidden)
	{
		return false;
	}


	return false;
}
