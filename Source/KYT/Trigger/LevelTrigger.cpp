// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTrigger.h"

#include "../Character/BasePlayerCharacter.h"
#include "../RandomRoom/RandomRoomgameMode.h"

#include "../KYTGameInstance.h"


// Sets default values
ALevelTrigger::ALevelTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

void ALevelTrigger::TriggerBegin(const FHitResult& SweepResult, AActor* OtherActor)
{
	ABasePlayerCharacter* Player = Cast<ABasePlayerCharacter>(OtherActor);
	if (!IsValid(Player)) {

		//
		return;
	}

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
	
	



	//Player->SavePlayer();
	ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode)) {

		int32 CurrentStageNum = MyGameMode->GetStageNumber();

		MyGameMode->SetStageNumber(CurrentStageNum + 1);

		MyGameMode->SaveGame(CurrentSaveIndex);

		UGameplayStatics::OpenLevel(GetWorld(), mLevelName);
	}

	
}

void ALevelTrigger::TriggerEnd()
{
}
