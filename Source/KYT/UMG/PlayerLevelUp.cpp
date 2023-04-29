// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLevelUp.h"

#include "../Character/MagicianPlayerCharacter.h"
#include "../Character/KnightPlayerCharacter.h"

#include "Kismet/GameplayStatics.h"


void UPlayerLevelUp::NativeConstruct()
{
	Super::NativeConstruct();

	mPlayerLevel = nullptr;

	// Load Widget
	mPlayerLevel = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("PlayerLevel"))));

	mChoiceIcon.Add(Cast<UImage>(GetWidgetFromName(FName(TEXT("Choice1Icon")))));
	mChoiceIcon.Add(Cast<UImage>(GetWidgetFromName(FName(TEXT("Choice2Icon")))));
	mChoiceIcon.Add(Cast<UImage>(GetWidgetFromName(FName(TEXT("Choice3Icon")))));
	mChoiceIcon.Add(Cast<UImage>(GetWidgetFromName(FName(TEXT("Choice4Icon")))));

	mChoiceDescription.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Choice1Description")))));
	mChoiceDescription.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Choice2Description")))));
	mChoiceDescription.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Choice3Description")))));
	mChoiceDescription.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Choice4Description")))));

	mChoiceBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("Choice1Btn")))));
	mChoiceBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("Choice2Btn")))));
	mChoiceBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("Choice3Btn")))));
	mChoiceBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("Choice4Btn")))));

	mExitDescription = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("ExitDescription"))));

	mOkBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("Ok_Btn"))));
	mNoBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("No_Btn"))));
	

	// Add Dynamic to Button
	mChoiceBtn[0]->OnClicked.AddDynamic(this, &UPlayerLevelUp::OnChoice1BtnClicked);
	mChoiceBtn[1]->OnClicked.AddDynamic(this, &UPlayerLevelUp::OnChoice2BtnClicked);
	mChoiceBtn[2]->OnClicked.AddDynamic(this, &UPlayerLevelUp::OnChoice3BtnClicked);
	mChoiceBtn[3]->OnClicked.AddDynamic(this, &UPlayerLevelUp::OnChoice4BtnClicked);
	
	mOkBtn->OnClicked.AddDynamic(this, &UPlayerLevelUp::OnOkBtnClicked);
	mNoBtn->OnClicked.AddDynamic(this, &UPlayerLevelUp::OnNoBtnClicked);


	mOkBtn->SetIsEnabled(false);


	mExitDescriptionArray.Add(TEXT("Cancel : Return 15% of Exp "));
	mExitDescriptionArray.Add(TEXT("5, 10, 15 Level : New Skill"));
	mExitDescriptionArray.Add(TEXT("Arcance Max : Open New Attribute"));
	mExitDescriptionArray.Add(TEXT("Cancel : Return 15% of Exp "));
	mExitDescriptionArray.Add(TEXT("Cancel : Return 15% of Exp "));
	mExitDescriptionArray.Add(TEXT("Cancel : Return 15% of Exp "));
	

}





void UPlayerLevelUp::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);

}

void UPlayerLevelUp::SetPlayerLevel(int32 Level)
{

#define LOCTEXT_NAMESPACE "PlayerLevelNamespace"

	if (mPlayerLevel) 
	{
		FText PlayerLevelText = FText::Format(LOCTEXT("PlayerLevelFText", "Level {0} "), Level);

		mPlayerLevel->SetText(PlayerLevelText);
	}

#undef LOCTEXT_NAMESPACE

}

void UPlayerLevelUp::SetSkillUpgradeInfo(TArray<FPlayerSkillUpgradeInfo> InfoArray)
{

	for (int32 i = 0; i < InfoArray.Num(); i++)
	{
		mChoiceIcon[i]->SetBrushFromTexture(Cast<UTexture2D>(InfoArray[i].Icon));
		mChoiceDescription[i]->SetText(FText::FromName(InfoArray[i].Description));
	}

	SetExitDescriptionRandom();

	mPlayerSkillUpgradeArray = InfoArray;
}

FName UPlayerLevelUp::SetExitDescriptionRandom()
{
	int32 ExitDescriptionNum = mExitDescriptionArray.Num();

	int32 Index = FMath::RandRange(0, ExitDescriptionNum - 1);

	FText Desc =  FText::FromName(mExitDescriptionArray[Index]);

	mExitDescription->SetText(Desc);


	return mExitDescriptionArray[Index];
}

void UPlayerLevelUp::OnChoice1BtnClicked()
{
	bool First = true;

	for (auto Btn : mChoiceBtn) {

		if (!Btn->GetIsEnabled()) {
			// Not First!
			// some btn already picked!
			First = false;
		}
	}
	
	// if Notclicked : 
	// ���� ���õ� ��ư�����ϰ� ������ ��Ȱ��ȭ
	// OK ��ư Ȱ��ȭ
	if (First) 
	{
		for (auto Btn : mChoiceBtn) 
		{
			Btn->SetIsEnabled(false);
		}
		mChoiceBtn[0]->SetIsEnabled(true);
		mOkBtn->SetIsEnabled(true);
	}
	// if Clicked :
	// ������ ��ư Ȱ��ȭ
	// OK ��ư ��Ȱ��ȭ
	else 
	{
		for (auto Btn : mChoiceBtn) 
		{
			Btn->SetIsEnabled(true);
		}
		mOkBtn->SetIsEnabled(false);
	}
}

void UPlayerLevelUp::OnChoice2BtnClicked()
{
	bool First = true;

	for (auto Btn : mChoiceBtn) {

		if (!Btn->GetIsEnabled()) {
			
			First = false;
		}
	}

	
	if (First)
	{
		for (auto Btn : mChoiceBtn)
		{
			Btn->SetIsEnabled(false);
		}
		mChoiceBtn[1]->SetIsEnabled(true);
		mOkBtn->SetIsEnabled(true);
	}
	else
	{
		for (auto Btn : mChoiceBtn)
		{
			Btn->SetIsEnabled(true);
		}
		mOkBtn->SetIsEnabled(false);
	}
}

void UPlayerLevelUp::OnChoice3BtnClicked()
{
	bool First = true;

	for (auto Btn : mChoiceBtn) {

		if (!Btn->GetIsEnabled()) {

			First = false;
		}
	}


	if (First)
	{
		for (auto Btn : mChoiceBtn)
		{
			Btn->SetIsEnabled(false);
		}
		mChoiceBtn[2]->SetIsEnabled(true);
		mOkBtn->SetIsEnabled(true);
	}
	else
	{
		for (auto Btn : mChoiceBtn)
		{
			Btn->SetIsEnabled(true);
		}
		mOkBtn->SetIsEnabled(false);
	}
}

void UPlayerLevelUp::OnChoice4BtnClicked()
{
	bool First = true;

	for (auto Btn : mChoiceBtn) {

		if (!Btn->GetIsEnabled()) {

			First = false;
		}
	}


	if (First)
	{
		for (auto Btn : mChoiceBtn)
		{
			Btn->SetIsEnabled(false);
		}
		mChoiceBtn[3]->SetIsEnabled(true);
		mOkBtn->SetIsEnabled(true);
	}
	else
	{
		for (auto Btn : mChoiceBtn)
		{
			Btn->SetIsEnabled(true);
		}
		mOkBtn->SetIsEnabled(false);
	}
}


void UPlayerLevelUp::OnOkBtnClicked()
{
	// ���õ� �׸��� ��ȭ ���� �÷��̾�� ����
	// ���õ� ��ȭ���� // Enum type
	// 
	// 
	int32 ChoiceSkillIndex = 0;
	for (int32 i = 0; i < mPlayerSkillUpgradeArray.Num(); i++) {

		if (mChoiceBtn[i]->GetIsEnabled()) {

			ChoiceSkillIndex = i;
			break;
		}
	}

	FPlayerSkillUpgradeInfo UpgradeInfo = mPlayerSkillUpgradeArray[ChoiceSkillIndex];

	// Basic Ÿ��
	if(UpgradeInfo.IsBasic)
	{
		ABasePlayerCharacter* MyPlayer = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (IsValid(MyPlayer))
		{
			if (UpgradeInfo.BasicUpgradeInfo.bIsExp) {

				FPlayerCharacterInfo Info = MyPlayer->GetPlayerInfo();
				Info.BasicUpgradeInfo.mExpLevel++;

				MyPlayer->SetPlayerInfo(Info);
			}

			else if (UpgradeInfo.BasicUpgradeInfo.bIsHP) {

				FPlayerCharacterInfo Info = MyPlayer->GetPlayerInfo();
				Info.BasicUpgradeInfo.mHPLevel++;

				Info.HPMax *= 1.15f;
				Info.HP = Info.HPMax;

				MyPlayer->SetPlayerInfo(Info);
			}

			else if (UpgradeInfo.BasicUpgradeInfo.bIsMP) {

				FPlayerCharacterInfo Info = MyPlayer->GetPlayerInfo();
				Info.BasicUpgradeInfo.mMPLevel++;

				Info.MPMax *= 1.15f;
				Info.MP = Info.MPMax;

				MyPlayer->SetPlayerInfo(Info);
			}

			else if (UpgradeInfo.BasicUpgradeInfo.bIsArmor) {

				FPlayerCharacterInfo Info = MyPlayer->GetPlayerInfo();
				Info.BasicUpgradeInfo.mArmorLevel++;

				Info.ArmorPoint *= 1.2f;

				MyPlayer->SetPlayerInfo(Info);
			}
		}
	}


	// �Ӽ���ȭ Ÿ��
	if (UpgradeInfo.IsAttribute) 
	{
		ABasePlayerCharacter* MyPlayer =  Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (IsValid(MyPlayer)) 
		{
			uint8 AttributeTypeIndex = (uint8)UpgradeInfo.AttributeType;


			int32 BeforeAttributeLevel = MyPlayer->GetPlayerInfo().PlayerAttributeLevel[AttributeTypeIndex];
			MyPlayer->SetAttributeLevel(UpgradeInfo.AttributeType, BeforeAttributeLevel + 1);
		}
	}

	// ����ü ��ȭ Ÿ��
	else if (UpgradeInfo.IsProjectile) 
	{
		AMagicianPlayerCharacter* MyMagician = Cast<AMagicianPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (IsValid(MyMagician))
		{
			if (UpgradeInfo.IsProjectileHoming)
			{
				MyMagician->SetHoming(true);
			}

			else if (UpgradeInfo.IsProjectileDuplicate)
			{
				MyMagician->SetDuplicate(true);
			}

			else if (UpgradeInfo.IsProjectileDuplicateProbability)
			{
				float BefProb = MyMagician->GetProjectileDuplicateProbability();
				float NewProb = BefProb + UpgradeInfo.IncreaseValue_float;

				MyMagician->SetProjectileDuplicateProbability(NewProb);
			}

			else if (UpgradeInfo.IsProjectileSpeed)
			{
				float BeforeSpeed = MyMagician->GetProjectileSpeed();
				float NewSpeed = BeforeSpeed + UpgradeInfo.IncreaseValue_float;
				
				MyMagician->SetProjectileSpeed(NewSpeed);
			}

			else if (UpgradeInfo.IsProjectileScale)
			{
				float BeforeScale = MyMagician->GetProjectileScale();
				float NewScale = BeforeScale + UpgradeInfo.IncreaseValue_float;
				
				MyMagician->SetProjectileScale(NewScale);
			}

			else if (UpgradeInfo.IsProjectileDamageScale)
			{
				float BeforeScale = MyMagician->GetProjectileDamageScale();
				float NewScale = BeforeScale + UpgradeInfo.IncreaseValue_float;
				
				MyMagician->SetProjectileDamageScale(NewScale);
			}

			else if (UpgradeInfo.IsProjectileDuplicateCount)
			{
				int32 BeforeCount = MyMagician->GetProjectileDuplicateCount();
				int32 NewCount = BeforeCount + UpgradeInfo.IncreaseValue_int32;

				MyMagician->SetProjectileDuplicateCount(NewCount);
			}
		}
	}

	


	// â�� �ݰ� Pause ǰ
	for (auto Btn : mChoiceBtn)
	{
		Btn->SetIsEnabled(true);
	}
	mOkBtn->SetIsEnabled(false);

	this->SetVisibility(ESlateVisibility::Hidden);

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UPlayerLevelUp::OnNoBtnClicked()
{
	// �÷��̾��� ������ 1 ���߰� ����ġ 30% ��ȯ
	AMagicianPlayerCharacter* MyMagician = Cast<AMagicianPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(MyMagician))
	{
		// ������ ����ġ
		// 
		// 1 : 1000 ����
		// 2 : 1500 
		// 3 : 2000
		//
		// 500�� ����
		
		MyMagician->DecreasePlayerLevel();

		float LevelUpExp = 500 + (500 * MyMagician->GetPlayerInfo().Level);

		MyMagician->GetExp(LevelUpExp * 0.15f);
	}
	
	
	// â�� �ݰ� Pause ǰ
	for (auto Btn : mChoiceBtn)
	{
		Btn->SetIsEnabled(true);
	}
	mOkBtn->SetIsEnabled(false);

	this->SetVisibility(ESlateVisibility::Hidden);

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}
