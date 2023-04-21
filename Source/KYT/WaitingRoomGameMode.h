// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KYTGameModeBase.h"
#include "WaitingRoomGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API AWaitingRoomGameMode : public AKYTGameModeBase
{
	GENERATED_BODY()

public:
	AWaitingRoomGameMode();



private:




public:
	virtual void BeginPlay()	override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void Tick(float DeltaTime)	override;
};
