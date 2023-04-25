// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../KYTGameModeBase.h"
#include "InfiniteGameMode.generated.h"

/**
 * 
 */
class ARoomBase;

UCLASS()
class KYT_API AInfiniteGameMode : public AKYTGameModeBase
{
	GENERATED_BODY()
	


public:
	AInfiniteGameMode();


private:

	TSubclassOf<ARoomBase>	m_RoomInfiniteClass;
	ARoomBase* mRoomInfinite;



public:
	virtual void BeginPlay()	override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void Tick(float DeltaTime)	override;


};
