// Fill out your copyright notice in the Description page of Project Settings.


#include "KYTGameInstance.h"




UKYTGameInstance::UKYTGameInstance() : 
	m_PlayerTable(nullptr),
	m_PlayerClass(E_Player_Class::None)
{
	
	
	static ConstructorHelpers::FObjectFinder<UDataTable>	PlayerTable(TEXT("DataTable'/Game/KYT/Player/DataTable/DT_PlayerCharacter.DT_PlayerCharacter'"));
	if (PlayerTable.Succeeded())
		m_PlayerTable = PlayerTable.Object;
	
	static ConstructorHelpers::FObjectFinder<UDataTable>	PlayerSkillUpgradeTable(TEXT("DataTable'/Game/KYT/Player/DataTable/DT_PlayerSkillUpgrade.DT_PlayerSkillUpgrade'"));
	if (PlayerSkillUpgradeTable.Succeeded())
		m_PlayerSkillUpgradeTable = PlayerSkillUpgradeTable.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable>	MonsterTable(TEXT("DataTable'/Game/KYT/Monster/DataTable/DT_Monster.DT_Monster'"));
	if (MonsterTable.Succeeded())
		m_MonsterTable = MonsterTable.Object;


	// Default Volume Scale
	FVolumeScale Volume;
	Volume.MasterVolumeScale = 0.6f;
	Volume.BGMVolumeScale = 0.4f;
	Volume.AttackVolumeScale = 0.5f;
	Volume.SkillVolumeScale = 0.3f;
	Volume.MonsterVolumeScale = 0.4f;

	m_VolumeScale = Volume;
}


UKYTGameInstance::~UKYTGameInstance()
{
}

void UKYTGameInstance::Init()
{
	Super::Init();


	m_PlayerClass = E_Player_Class::Magician;
	//m_PlayerClass = E_Player_Class::Knight;
}

const FPlayerCharacterTable* UKYTGameInstance::FindPlayerTable(const FName& Name)
{
	return m_PlayerTable->FindRow<FPlayerCharacterTable>(Name, TEXT(""));
}

const TArray<FPlayerSkillUpgradeTable*> UKYTGameInstance::FindPlayerSkillUpgradeTable()
{
	TArray<FPlayerSkillUpgradeTable*> ReturnArray;
	
	m_PlayerSkillUpgradeTable->GetAllRows<FPlayerSkillUpgradeTable>(TEXT(""), ReturnArray);

	return ReturnArray;
}

const FMonsterTableBase* UKYTGameInstance::FindMonsterTable(const FName& Name)
{
	return m_MonsterTable->FindRow<FMonsterTableBase>(Name, TEXT(""));
}
