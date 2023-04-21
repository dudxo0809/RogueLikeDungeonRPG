// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/Image.h>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatus.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class KYT_API UPlayerStatus : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UImage* m_HP;
	UImage* m_MP;
	UImage* m_Exp;

	UTextBlock* mPlayerLevel;

	UImage* m_Skill1;
	UImage* m_Skill2;
	UImage* m_Skill3;
	UImage* m_Skill4;
	
	UMaterialInstanceDynamic* mD_HP;
	UMaterialInstanceDynamic* mD_MP;
	UMaterialInstanceDynamic* mD_Exp;

private:

	TArray<UTextBlock*> mAttributeLevel;

private:

	UTextBlock* mStageNumber;

	



public:

	

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


public:
	
	void SetHP(float Ratio);
	void SetMP(float Ratio);
	void SetExp(float Ratio);

	void SetLevel(int32 Level);

	void SetSkillImage(int32 SkillIndex, bool Enable);

	void SetStageNumber(int32 StageNumber);

	void SetAttributeLevel();

};
