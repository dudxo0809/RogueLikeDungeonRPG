// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfoMenu.h"

#include "../Character/BasePlayerCharacter.h"
#include "../RandomRoom/RandomRoomGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "../KYTGameInstance.h"


void UPlayerInfoMenu::SetInit()
{
	// Set Init Button Enable
	ABasePlayerCharacter* MyPlayer = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(MyPlayer))
	{
		for (int32 i = 0; i < 8; i++) {

			if (MyPlayer->GetPlayerInfo().PlayerAttributeLevel[i] == 0) {

				mAttributeBtn[i]->SetIsEnabled(false);
			}
			else {

				mAttributeBtn[i]->SetIsEnabled(true);
			}
		}
	}

	mOkBtn->SetIsEnabled(false);

	// Setting Player Info
	// Load to ABasePlayerCharacter


#define LOCTEXT_NAMESPACE "PlayerInfoNamespace"

	
	FText HPText = FText::Format(LOCTEXT("PlayerInfoFText", "HP   {0}/{1} "), MyPlayer->GetPlayerInfo().HP, MyPlayer->GetPlayerInfo().HPMax);
	FText MPText = FText::Format(LOCTEXT("PlayerInfoFText", "MP   {0}/{1} "), MyPlayer->GetPlayerInfo().MP, MyPlayer->GetPlayerInfo().MPMax);
	FText AttackText = FText::Format(LOCTEXT("PlayerInfoFText", "Attack   {0} "), MyPlayer->GetPlayerInfo().AttackPoint);
	FText ArmorText = FText::Format(LOCTEXT("PlayerInfoFText", "Armor   {0} "), MyPlayer->GetPlayerInfo().ArmorPoint);
	FText SpeedText = FText::Format(LOCTEXT("PlayerInfoFText", "Speed   {0} "),  MyPlayer->GetPlayerInfo().MoveSpeed);
	FText GoldText = FText::Format(LOCTEXT("PlayerInfoFText", "Gold   {0} "), MyPlayer->GetPlayerInfo().Gold);

	float LevelUpExp = 500 + (500 * MyPlayer->GetPlayerInfo().Level);
	FText ExpText = FText::Format(LOCTEXT("PlayerInfoFText", "Exp   {0}/{1} "), MyPlayer->GetPlayerInfo().Exp, LevelUpExp);

	mPlayerInfo[0]->SetText(HPText);
	mPlayerInfo[1]->SetText(MPText);
	mPlayerInfo[2]->SetText(AttackText);
	mPlayerInfo[3]->SetText(ArmorText);
	mPlayerInfo[4]->SetText(SpeedText);
	mPlayerInfo[5]->SetText(GoldText);
	mPlayerInfo[6]->SetText(ExpText);
	


#undef LOCTEXT_NAMESPACE


}

void UPlayerInfoMenu::NativeConstruct()
{
	Super::NativeConstruct();




	mAttributeBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("ArcaneBtn")))));
	mAttributeBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("FireBtn")))));
	mAttributeBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("IceBtn")))));
	mAttributeBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("ThunderBtn")))));
	mAttributeBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("PoisonBtn")))));
	mAttributeBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("HolyBtn")))));
	mAttributeBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("ShadowBtn")))));
	mAttributeBtn.Add(Cast<UButton>(GetWidgetFromName(FName(TEXT("VoidBtn")))));
	

	mOkBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("OkBtn"))));
	mNoBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("NoBtn"))));

	mChooseAttributeDescription = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("ChooseAttributeDescription"))));


	mSaveGameBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("SaveGameBtn"))));
	mEndGameBtn = Cast<UButton>(GetWidgetFromName(FName(TEXT("EndGameBtn"))));




	// Add Dynamic

	mAttributeBtn[0]->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnArcaneBtnClicked);
	mAttributeBtn[1]->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnFireBtnClicked);
	mAttributeBtn[2]->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnIceBtnClicked);
	mAttributeBtn[3]->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnThunderBtnClicked);
	mAttributeBtn[4]->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnPoisonBtnClicked);
	mAttributeBtn[5]->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnHolyBtnClicked);
	mAttributeBtn[6]->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnShadowBtnClicked);
	mAttributeBtn[7]->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnVoidBtnClicked);
	
	
	
	mOkBtn->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnOkBtnClicked);
	mNoBtn->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnNoBtnClicked);

	mSaveGameBtn->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnSaveGameBtnClicked);
	mEndGameBtn->OnClicked.AddDynamic(this, &UPlayerInfoMenu::OnEndGameBtnClicked);


	// PlayerInfo
	mPlayerInfo.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("HP_Text")))));
	mPlayerInfo.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("MP_Text")))));
	mPlayerInfo.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Attack_Text")))));
	mPlayerInfo.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Armor_Text")))));
	mPlayerInfo.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Speed_Text")))));
	mPlayerInfo.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Gold_Text")))));
	mPlayerInfo.Add(Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Exp_Text")))));
	
#define LOCTEXT_NAMESPACE "AttributeNmaeNamespace"

	mAttributeName.Add(LOCTEXT("AttributeNmaeNamespace", "Arcane"));
	mAttributeName.Add(LOCTEXT("AttributeNmaeNamespace", "Fire"));
	mAttributeName.Add(LOCTEXT("AttributeNmaeNamespace", "Ice"));
	mAttributeName.Add(LOCTEXT("AttributeNmaeNamespace", "Thunder"));
	mAttributeName.Add(LOCTEXT("AttributeNmaeNamespace", "Poison"));
	mAttributeName.Add(LOCTEXT("AttributeNmaeNamespace", "Holy"));
	mAttributeName.Add(LOCTEXT("AttributeNmaeNamespace", "Shadow"));
	mAttributeName.Add(LOCTEXT("AttributeNmaeNamespace", "Void"));

#undef LOCTEXT_NAMESPACE
}

void UPlayerInfoMenu::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);



}

void UPlayerInfoMenu::OnMyBtnClicked(int32 Index)
{
	ABasePlayerCharacter* MyPlayer = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (!IsValid(MyPlayer)) {

		return;
	}


	bool First = true;

	for (int32 i = 0; i < mAttributeBtn.Num(); i++) {

		if (!mAttributeBtn[i]->GetIsEnabled() && MyPlayer->GetPlayerInfo().PlayerAttributeLevel[i] > 0) {
			// Not First!
			// some btn already picked!
			First = false;
		}
	}


	// if Notclicked : 
	// 현재 선택된 버튼제외하고 나머지 비활성화
	// OK 버튼 활성화
	if (First)
	{
		for (auto Btn : mAttributeBtn)
		{
			Btn->SetIsEnabled(false);
		}
		mAttributeBtn[Index]->SetIsEnabled(true);
		mOkBtn->SetIsEnabled(true);


		// 속성 변화 텍스트 표시
#define LOCTEXT_NAMESPACE "PlayerLevelNamespace"

		if (mChooseAttributeDescription)
		{
			// Get Attribute Text
		
			FText BeforeAtt = mAttributeName[MyPlayer->GetSkillEffectAttributeIndex()];
			FText AfterAtt = mAttributeName[Index];

			FText AttributeChangeText = FText::Format(LOCTEXT("PlayerLevelFText", "{0} -> {1} "),BeforeAtt, AfterAtt);

			mChooseAttributeDescription->SetText(AttributeChangeText);
		}

#undef LOCTEXT_NAMESPACE

	}
	// if Clicked :
	// 나머지 버튼 활성화
	// OK 버튼 비활성화
	else
	{
		for (int32 i = 0; i < mAttributeBtn.Num(); i++)
		{
			if (MyPlayer->GetPlayerInfo().PlayerAttributeLevel[i] > 0) {

				mAttributeBtn[i]->SetIsEnabled(true);
			}
		}
		mOkBtn->SetIsEnabled(false);
	}
}

void UPlayerInfoMenu::OnArcaneBtnClicked()
{	
	OnMyBtnClicked(0);
}

void UPlayerInfoMenu::OnFireBtnClicked()
{
	OnMyBtnClicked(1);
}

void UPlayerInfoMenu::OnIceBtnClicked()
{
	OnMyBtnClicked(2);
}

void UPlayerInfoMenu::OnThunderBtnClicked()
{
	OnMyBtnClicked(3);
}

void UPlayerInfoMenu::OnPoisonBtnClicked()
{
	OnMyBtnClicked(4);
}

void UPlayerInfoMenu::OnHolyBtnClicked()
{
	OnMyBtnClicked(5);
}

void UPlayerInfoMenu::OnShadowBtnClicked()
{
	OnMyBtnClicked(6);
}

void UPlayerInfoMenu::OnVoidBtnClicked()
{
	OnMyBtnClicked(7);
}

void UPlayerInfoMenu::OnOkBtnClicked()
{
	ABasePlayerCharacter* MyPlayer = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!IsValid(MyPlayer))
		return;


	for (int32 i = 0; i < mAttributeBtn.Num(); i++) {

		if (mAttributeBtn[i]->GetIsEnabled()) {

			MyPlayer->SetAttribute((EPlayerAttribute)i);

			break;
		}
	}

	this->SetVisibility(ESlateVisibility::Hidden);

	return;
}

void UPlayerInfoMenu::OnNoBtnClicked()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerInfoMenu::OnSaveGameBtnClicked()
{
	// 저장할 Save Slot 지정

	int32 CurrentSaveIndex = 0;

	UKYTGameInstance* MyGameInst = Cast<UKYTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(MyGameInst)) {

		CurrentSaveIndex = MyGameInst->GetCurrentSaveIndex();

		// NewGame 으로 게임을 진입한 경우
		if (CurrentSaveIndex == -1) {

			// NewGame일때 : 남아있는 Save Slot중 가장 앞의것에 저장
			// 만약 남은 Save Slot이 없다면 4번 Slot에 저장
			for (int32 i = 0; i < 4; i++) {

				FString FullPath = FPaths::ProjectSavedDir() + TEXT("SaveGames/") + FString::FromInt(i) + TEXT("/Save.txt");

				TSharedPtr<FArchive>	Reader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));

				// Save 파일이 존재하지 않음
				if (!Reader.IsValid()) {

					CurrentSaveIndex = i;

					break;
				}

				// 있으면 continue;
			}
		}

		if (CurrentSaveIndex == -1)
			CurrentSaveIndex = 3;
	}


	// Save
	ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode)) {

		int32 CurrentStageNum = MyGameMode->GetStageNumber();

		MyGameMode->SetStageNumber(CurrentStageNum);

		MyGameMode->SaveGame(CurrentSaveIndex);
	}
}

void UPlayerInfoMenu::OnEndGameBtnClicked()
{
	UKYTGameInstance* MyGameInst = Cast<UKYTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(MyGameInst)) {

		// Set Save Index to GameInstance

		// Open Level
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
	}
}
