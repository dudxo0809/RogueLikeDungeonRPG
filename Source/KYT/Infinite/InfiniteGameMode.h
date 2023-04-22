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

	TSubclassOf<ARoomBase>	m_RoomInitClass;
	ARoomBase* mRoomInit;
};
