// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHP.h"

void UMonsterHP::NativeConstruct()
{
	Super::NativeConstruct();


	mHP_Percent = Cast<UProgressBar>(GetWidgetFromName(FName(TEXT("HP_Progress"))));
	mMonsterLevel = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Level_Text"))));
}

void UMonsterHP::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);



}

void UMonsterHP::SetHPPercent(float Ratio)
{
	mHP_Percent->SetPercent(Ratio);
}

void UMonsterHP::SetLevel(int32 Level)
{
#define LOCTEXT_NAMESPACE "MonsterLevelNamespace"

	if (mMonsterLevel)
	{
		FText MonsterLevelText = FText::Format(LOCTEXT("MonsterLevelFText", "{0}"), Level);

		mMonsterLevel->SetText(MonsterLevelText);
	}

#undef LOCTEXT_NAMESPACE
}

