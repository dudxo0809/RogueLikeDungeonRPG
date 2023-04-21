// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitingRoomGameMode.h"

#include "KYTGameInstance.h"
#include "Character/CharacterInfo.h"
#include "Character/MagicianPlayerCharacter.h"
#include "Character/KnightPlayerCharacter.h"
#include "Character/BasePlayerController.h"

AWaitingRoomGameMode::AWaitingRoomGameMode()
{
}

void AWaitingRoomGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AWaitingRoomGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AWaitingRoomGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UKYTGameInstance* GameInst = GetWorld()->GetGameInstance<UKYTGameInstance>();
	E_Player_Class Class = GameInst->GetPlayerClass();

	switch (Class) {

	case E_Player_Class::Magician:
		DefaultPawnClass = AMagicianPlayerCharacter::StaticClass();
		break;

	case E_Player_Class::Knight:
		DefaultPawnClass = AKnightPlayerCharacter::StaticClass();
		break;
	}
	PlayerControllerClass = ABasePlayerController::StaticClass();

}

void AWaitingRoomGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AWaitingRoomGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
