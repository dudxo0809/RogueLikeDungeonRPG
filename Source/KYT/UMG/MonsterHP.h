// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "MonsterHP.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API UMonsterHP : public UUserWidget
{
	GENERATED_BODY()
	

private:

	UProgressBar* mHP_Percent;
	UTextBlock* mMonsterLevel;


public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;

public:

	void SetHPPercent(float Ratio);
	void SetLevel(int32 Level);
};
