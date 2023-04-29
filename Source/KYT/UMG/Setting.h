// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"

#include "Setting.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API USetting : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UButton* m_SaveBtn;
	UButton* m_ExitBtn;
	UButton* m_CloseBtn;


public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;



public:

	UFUNCTION()
		void OnSaveBtnClicked();

	UFUNCTION()
		void OnExitBtnClicked();


};
