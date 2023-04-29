// Fill out your copyright notice in the Description page of Project Settings.


#include "Setting.h"

#include "../KYTGameInstance.h"

void USetting::NativeConstruct()
{
	Super::NativeConstruct();

	m_SaveBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("Save_Btn"))));
	m_ExitBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("Exit_Btn"))));
	m_CloseBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("Close_Btn"))));


	// Add Dynamic
	m_SaveBtn->OnClicked.AddDynamic(this, &USetting::OnSaveBtnClicked);
	m_ExitBtn->OnClicked.AddDynamic(this, &USetting::OnExitBtnClicked);
	m_CloseBtn->OnClicked.AddDynamic(this, &USetting::OnExitBtnClicked);
}

void USetting::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);


}

void USetting::OnSaveBtnClicked()
{
	// ���� �����̴��� �������� GameInstance�� Sound ���� ����

	// �������Ʈ���� �۾���

}

void USetting::OnExitBtnClicked()
{
	SetVisibility(ESlateVisibility::Hidden);

}
