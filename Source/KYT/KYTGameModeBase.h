// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include <Blueprint\UserWidget.h>
#include "UMG/MainHUDBase.h"


#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "KYTGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API AKYTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	
protected:

	TSubclassOf<UUserWidget>	m_MainHUDClass;
	UMainHUDBase* m_MainHUD;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UAudioComponent* mAudio;


public:
	AKYTGameModeBase();

public:
	virtual void BeginPlay()	override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);
	virtual void Tick(float DeltaTime)	override;


public:
	UMainHUDBase* GetMainHUD() { return m_MainHUD; }


};
