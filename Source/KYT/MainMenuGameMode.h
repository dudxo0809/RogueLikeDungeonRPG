// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYTGameModeBase.h"


#include "UMG/MainMenu.h"


#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API AMainMenuGameMode : public AKYTGameModeBase
{
	GENERATED_BODY()
	

public:

	AMainMenuGameMode();



private:


	TSubclassOf<UUserWidget> m_MainMenuClass;
	UMainMenu* m_MainMenu;






public:
	virtual void BeginPlay()	override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void Tick(float DeltaTime)	override;

};
