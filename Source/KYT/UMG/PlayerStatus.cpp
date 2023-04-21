// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatus.h"

#include "../Character/BasePlayerCharacter.h"

#include "Styling/SlateBrush.h"
#include "Components/TextBlock.h"



	

void UPlayerStatus::NativeConstruct()
{
	Super::NativeConstruct();

	m_HP = Cast<UImage>(GetWidgetFromName(FName(TEXT("HP_Image"))));
	m_MP = Cast<UImage>(GetWidgetFromName(FName(TEXT("MP_Image"))));
	m_Exp = Cast<UImage>(GetWidgetFromName(FName(TEXT("Exp_Image"))));

	mPlayerLevel = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("PlayerLevel"))));

	m_Skill1 = Cast<UImage>(GetWidgetFromName(FName(TEXT("Skill1Image"))));
	m_Skill2 = Cast<UImage>(GetWidgetFromName(FName(TEXT("Skill2Image"))));
	m_Skill3 = Cast<UImage>(GetWidgetFromName(FName(TEXT("Skill3Image"))));
	m_Skill4 = Cast<UImage>(GetWidgetFromName(FName(TEXT("Skill4Image"))));

	mStageNumber = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("StageNumber"))));

	mD_HP = nullptr;
	mD_MP = nullptr;
	mD_Exp = nullptr;


	mAttributeLevel.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("ArcaneLevel")))));
	mAttributeLevel.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("FireLevel")))));
	mAttributeLevel.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("IceLevel")))));
	mAttributeLevel.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("ThunderLevel")))));
	mAttributeLevel.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("PoisonLevel")))));
	mAttributeLevel.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("HolyLevel")))));
	mAttributeLevel.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("ShadowLevel")))));
	mAttributeLevel.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("VoidLevel")))));

}

void UPlayerStatus::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);

}

void UPlayerStatus::SetHP(float Ratio)
{
	if (mD_HP == nullptr) {
		UMaterialInterface* Mat = Cast<UMaterialInterface>(m_HP->Brush.GetResourceObject());

		mD_HP = UMaterialInstanceDynamic::Create(Mat, this);

		mD_HP->SetScalarParameterValue(TEXT("Value"), Ratio);

		
		m_HP->Brush.SetResourceObject(mD_HP);
	}

	else {
		mD_HP->SetScalarParameterValue(TEXT("Value"), Ratio);
	}
	

	
}

void UPlayerStatus::SetMP(float Ratio)
{
	if (mD_MP == nullptr) {
		UMaterialInterface* Mat = Cast<UMaterialInterface>(m_MP->Brush.GetResourceObject());

		mD_MP = UMaterialInstanceDynamic::Create(Mat, this);

		mD_MP->SetScalarParameterValue(TEXT("Value"), Ratio);

		m_MP->Brush.SetResourceObject(mD_MP);
	}

	else {
		mD_MP->SetScalarParameterValue(TEXT("Value"), Ratio);
	}
}

void UPlayerStatus::SetExp(float Ratio)
{
	if (mD_Exp == nullptr) {
		UMaterialInterface* Mat = Cast<UMaterialInterface>(m_Exp->Brush.GetResourceObject());

		mD_Exp = UMaterialInstanceDynamic::Create(Mat, this);

		mD_Exp->SetScalarParameterValue(TEXT("Value"), Ratio);

		m_Exp->Brush.SetResourceObject(mD_Exp);
	}

	else {
		mD_Exp->SetScalarParameterValue(TEXT("Value"), Ratio);
	}
}

void UPlayerStatus::SetLevel(int32 Level)
{
	#define LOCTEXT_NAMESPACE "PlayerLevelNamespace"

	if (mPlayerLevel) 
	{
		FText PlayerLevelText = FText::Format(LOCTEXT("PlayerLevelFText", "Level {0} "), Level);

		mPlayerLevel->SetText(PlayerLevelText);
	}

#undef LOCTEXT_NAMESPACE

}

void UPlayerStatus::SetSkillImage(int32 SkillIndex, bool Enable)
{
	UImage* Target = nullptr;

	switch (SkillIndex) {

	case 0 :
		Target = m_Skill1;
		break;

	case 1:
		Target = m_Skill2;
		break;

	case 2:
		Target = m_Skill3;
		break;

	case 3:
		Target = m_Skill4;
		break;

	default:
		break;

	}

	if (Enable) {
		Target->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
	}
	else {
		Target->SetColorAndOpacity(FLinearColor(1, 1, 1, 0));
	}
}

void UPlayerStatus::SetStageNumber(int32 StageNumber)
{
#define LOCTEXT_NAMESPACE "StageNumberNamespace"

	if (mStageNumber)
	{
		FText StageNumberText = FText::Format(LOCTEXT("StageNumberFText", "Stage {0} "), StageNumber);

		mStageNumber->SetText(StageNumberText);
	}

#undef LOCTEXT_NAMESPACE

}

void UPlayerStatus::SetAttributeLevel()
{

	ABasePlayerCharacter* MyPlayer = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!IsValid(MyPlayer))
		return;


#define LOCTEXT_NAMESPACE "AttributeLevelNamespace"

	int32 AttributeNum = MyPlayer->GetPlayerInfo().PlayerAttributeLevel.Num();

	for (int i = 0; i < AttributeNum; i++) {

		FText AttributeLevel;

		if (MyPlayer->GetPlayerInfo().PlayerAttributeLevel[i] == MyPlayer->GetPlayerInfo().PlayerAttributeMaxLevel[i]) 
		{
			AttributeLevel = FText::FromName(TEXT("M"));
		}

		else
		{
			AttributeLevel = FText::Format(LOCTEXT("PlayerInfoFText", "{0}"), MyPlayer->GetPlayerInfo().PlayerAttributeLevel[i]);
		}
		

		mAttributeLevel[i]->SetText(AttributeLevel);
	}


#undef LOCTEXT_NAMESPACE

}
