// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"

#include "Character/CharacterInfo.h"
#include "Monster/MonsterInfo.h"

#include "KYTGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API UKYTGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UKYTGameInstance();
	~UKYTGameInstance();

private:
	UDataTable* m_PlayerTable;
	UDataTable* m_PlayerSkillUpgradeTable;
	UDataTable* m_MonsterTable;


	E_Player_Class m_PlayerClass;


private:

	int32 m_CurrentSaveIndex;

private:

	FVolumeScale m_VolumeScale;


public:

	UFUNCTION(BlueprintCallable)
	void SetVolume(FVolumeScale VolumeScale) {

		m_VolumeScale = VolumeScale;
	}

	UFUNCTION(BlueprintCallable)
	FVolumeScale GetVolume() {

		return m_VolumeScale;
	}


public:

	int32 GetCurrentSaveIndex() {

		return m_CurrentSaveIndex;
	}
	void SetCurrentSaveIndex(int32 Index) {

		m_CurrentSaveIndex = Index;
	}


public:
	virtual void Init();

public:
	const FPlayerCharacterTable* FindPlayerTable(const FName& Name);
	const TArray<FPlayerSkillUpgradeTable*> FindPlayerSkillUpgradeTable();
	const FMonsterTableBase* FindMonsterTable(const FName& Name);


	E_Player_Class GetPlayerClass() { return m_PlayerClass; }
	void SetPlayerClass(E_Player_Class Class) { m_PlayerClass = Class; }
	
};
