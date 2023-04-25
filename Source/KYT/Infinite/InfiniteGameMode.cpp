// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteGameMode.h"

#include "../RandomRoom/RoomBase.h"


#include "../KYTGameInstance.h"
#include "../Character/CharacterInfo.h"
#include "../Character/MagicianPlayerCharacter.h"
#include "../Character/KnightPlayerCharacter.h"
#include "../Character/BasePlayerController.h"


AInfiniteGameMode::AInfiniteGameMode() 
{


	ConstructorHelpers::FClassFinder<ARoomBase> finder(TEXT("Blueprint'/Game/KYT/BluePrint/Room/BP_InfiniteRoom.BP_InfiniteRoom_C'"));

	if (finder.Succeeded()) {

		m_RoomInfiniteClass = finder.Class;
	}


}

void AInfiniteGameMode::BeginPlay()
{
	Super::BeginPlay();



	mRoomInfinite = Cast<ARoomBase>(m_RoomInfiniteClass.GetDefaultObject());


	FActorSpawnParameters	SpawnParam;
	ARoomBase* Room = GetWorld()->SpawnActor<ARoomBase>(mRoomInfinite->GetClass(), FVector(0, 0, 0) , FRotator(0, 0, 0), SpawnParam);

	

}

void AInfiniteGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AInfiniteGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
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

void AInfiniteGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);



}

void AInfiniteGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}
