// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomRoomGameMode.h"

#include "../SaveGame/DungeonSaveGame.h"

#include "RandomRoomGenerator.h"
#include "FloorData.h"
#include "RoomData.h"
#include "RoomBase.h"

#include "../KYTGameInstance.h"
#include "../Character/CharacterInfo.h"
#include "../Character/MagicianPlayerCharacter.h"
#include "../Character/KnightPlayerCharacter.h"
#include "../Character/BasePlayerController.h"
#include "../Trigger/MonsterSpawnTrigger.h"
#include "../Trigger/BossSpawnTrigger.h"


ARandomRoomGameMode::ARandomRoomGameMode(): 
	mFloorData(nullptr)
{

	// ARoomBase* Room = LoadObject<ARoomBase>(nullptr, TEXT("Blueprint'/Game/KYT/BluePrint/BP_RoomBase.BP_RoomBase_C'"));
	// UI_StartHUD 블루프린트 클래스 의 UClass 정보를 가져온다.
	ConstructorHelpers::FClassFinder<ARoomBase> finder1(TEXT("Blueprint'/Game/KYT/BluePrint/Room/BP_RoomBase1.BP_RoomBase1_C'"));
	ConstructorHelpers::FClassFinder<ARoomBase> finder2(TEXT("Blueprint'/Game/KYT/BluePrint/Room/BP_RoomBase2.BP_RoomBase2_C'"));
	ConstructorHelpers::FClassFinder<ARoomBase> finder3(TEXT("Blueprint'/Game/KYT/BluePrint/Room/BP_RoomBase3.BP_RoomBase3_C'"));
	ConstructorHelpers::FClassFinder<ARoomBase> finder4(TEXT("Blueprint'/Game/KYT/BluePrint/Room/BP_RoomBase4.BP_RoomBase4_C'"));

	ConstructorHelpers::FClassFinder<ARoomBase> finder_Init(TEXT("Blueprint'/Game/KYT/BluePrint/Room/BP_InitRoom.BP_InitRoom_C'"));
	ConstructorHelpers::FClassFinder<ARoomBase> finder_Boss(TEXT("Blueprint'/Game/KYT/BluePrint/Room/BP_BossRoom.BP_BossRoom_C'"));




	if (finder1.Succeeded()) {
		m_RoomBaseClass.Add(finder1.Class);
	}
	if (finder2.Succeeded()) {
		m_RoomBaseClass.Add(finder2.Class);
	}
	if (finder3.Succeeded()) {
		m_RoomBaseClass.Add(finder3.Class);
	}
	if (finder4.Succeeded()) {
		m_RoomBaseClass.Add(finder4.Class);
	}

	if (finder_Init.Succeeded()) {
		m_RoomInitClass = finder_Init.Class;
	}

	if (finder_Boss.Succeeded()) {
		m_RoomBossClass = finder_Boss.Class;
	}
	
	
	

}

void ARandomRoomGameMode::BeginPlay()
{
	Super::BeginPlay();

	

	// Sound
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/RPG_Dungeon_Themes/WAVs/Dungeon_9_Defenseless/WAV_Defenseless_Version_01_LOOP.WAV_Defenseless_Version_01_LOOP'"));

	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);

		UKYTGameInstance* Inst = Cast<UKYTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		float MasterVolumeScale = Inst->GetVolume().MasterVolumeScale;
		float BGMVolumeScale = Inst->GetVolume().BGMVolumeScale * MasterVolumeScale;

		mAudio->SetVolumeMultiplier(BGMVolumeScale);
		
		mAudio->Play();
	}
	

	// 위젯 블루프린트 UClass 정보를 이용해서 객체를 만들어낸다.
	if (IsValid(m_MainHUDClass))
	{
		// 생성한 객체의 주소를 m_MainHUD 에 받아둔다.
		m_MainHUD = Cast<UMainHUDBase>(CreateWidget(GetWorld(), m_MainHUDClass));
		if (IsValid(m_MainHUD))
		{
			m_MainHUD->AddToViewport();
			
		}
	}

	// 위젯 블루프린트 UClass 정보를 이용해서 객체를 만들어낸다.
	for (auto& i : m_RoomBaseClass) {
		if (IsValid(i)) {
			mRoomBaseArray.Add(Cast<ARoomBase>(i.GetDefaultObject()));
		}
	}
	mRoomInit = Cast<ARoomBase>(m_RoomInitClass.GetDefaultObject());
	mRoomBoss = Cast<ARoomBase>(m_RoomBossClass.GetDefaultObject());
	
	
	
	int32 N = (int32)EFloorInfo::RoomY;
	int32 M = (int32)EFloorInfo::RoomX;


	CRandomRoomGenerator* RandomRoomGenerator = CRandomRoomGenerator::GetInst();
	mFloorData = RandomRoomGenerator->MakeFloorData(N, M);



	//mFloorData;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			
			ERoomType RoomType = mFloorData->GetRoomData(i, j)->GetRoomType();
			

			int32 rand = FMath::RandRange(0, 3);

		

			if (RoomType == ERoomType::Normal) {

				FActorSpawnParameters	SpawnParam;

				ARoomBase* Room = GetWorld()->SpawnActor<ARoomBase>(mRoomBaseArray[rand]->GetClass(), FVector(0, 0, 0) + FVector(4000 * j, 4000 * i, 100), FRotator(0, 0, 0), SpawnParam);
				//Room->SetActorScale3D(FVector(4, 4, 1));
				
				for (int32 dir = 0; dir < 4; dir++) {

					if (mFloorData->GetRoomData(i, j)->GetIsWall(dir) == false) {
						Room->SetWallStaticMeshOff(dir);
					}
				}

				AMonsterSpawnTrigger* MonsterTrigger = GetWorld()->SpawnActor<AMonsterSpawnTrigger>(FVector(0, 0, 0) + FVector(4000 * j, 4000 * i, 100), FRotator(0, 0, 0), SpawnParam);
				MonsterTrigger->SetRoom(Room);


				MonsterTrigger->SetActorScale3D(FVector(55, 55, 10));

			}
			else if (RoomType == ERoomType::Init) {

				FActorSpawnParameters	SpawnParam;

				ARoomBase* Room = GetWorld()->SpawnActor<ARoomBase>(mRoomInit->GetClass(), FVector(0, 0, 0) + FVector(4000 * j, 4000 * i, 100), FRotator(0, 0, 0), SpawnParam);
				//Room->SetActorScale3D(FVector(4, 4, 1));

				for (int32 dir = 0; dir < 4; dir++) {

					if (mFloorData->GetRoomData(i, j)->GetIsWall(dir) == false) {
						Room->SetWallStaticMeshOff(dir);
					}
				}
			}

			else if (RoomType == ERoomType::Boss) {

				FActorSpawnParameters	SpawnParam;

				ARoomBase* Room = GetWorld()->SpawnActor<ARoomBase>(mRoomBoss->GetClass(), FVector(0, 0, 0) + FVector(4000 * j, 4000 * i, 100), FRotator(0, 0, 0), SpawnParam);
				//Room->SetActorScale3D(FVector(4, 4, 1));

				mBossRoomPos.X = Room->GetActorLocation().X;
				mBossRoomPos.Y = Room->GetActorLocation().Y;


				for (int32 dir = 0; dir < 4; dir++) {

					if (mFloorData->GetRoomData(i, j)->GetIsWall(dir) == false) {
						Room->SetWallStaticMeshOff(dir);
					}
				}

				ABossSpawnTrigger* BossTrigger = GetWorld()->SpawnActor<ABossSpawnTrigger>(FVector(0, 0, 0) + FVector(4000 * j, 4000 * i, 100), FRotator(0, 0, 0), SpawnParam);
				BossTrigger->SetRoom(Room);


				BossTrigger->SetActorScale3D(FVector(55, 55, 10));
			}


		}
	}


}

void ARandomRoomGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ARandomRoomGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
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

void ARandomRoomGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

}

void ARandomRoomGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector2D ARandomRoomGameMode::GetBossRoomPosition()
{
	return mBossRoomPos;
}

UDungeonSaveGame* ARandomRoomGameMode::CreateSaveGame()
{
	ABasePlayerCharacter* MyPlayer = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!IsValid(MyPlayer))
		return nullptr;

	// SaveGame
	UDungeonSaveGame* MySaveGame = NewObject<UDungeonSaveGame>();

	MySaveGame->mPlayerInfo.AttackPoint = MyPlayer->GetPlayerInfo().AttackPoint;
	MySaveGame->mPlayerInfo.ArmorPoint = MyPlayer->GetPlayerInfo().ArmorPoint;
	MySaveGame->mPlayerInfo.HP = MyPlayer->GetPlayerInfo().HP;
	MySaveGame->mPlayerInfo.HPMax = MyPlayer->GetPlayerInfo().HPMax;
	MySaveGame->mPlayerInfo.MP = MyPlayer->GetPlayerInfo().MP;
	MySaveGame->mPlayerInfo.MPMax = MyPlayer->GetPlayerInfo().MPMax;
	MySaveGame->mPlayerInfo.Level = MyPlayer->GetPlayerInfo().Level;
	MySaveGame->mPlayerInfo.Exp = MyPlayer->GetPlayerInfo().Exp;
	MySaveGame->mPlayerInfo.Gold = MyPlayer->GetPlayerInfo().Gold;
	MySaveGame->mPlayerInfo.MoveSpeed = MyPlayer->GetPlayerInfo().MoveSpeed;
	MySaveGame->mPlayerInfo.Mesh = MyPlayer->GetPlayerInfo().Mesh;

	// Player Basic2
	MySaveGame->mPlayerInfo.PlayerClass = MyPlayer->GetPlayerInfo().PlayerClass;
	MySaveGame->mPlayerInfo.BaseAttackDistance = MyPlayer->GetPlayerInfo().BaseAttackDistance;
	MySaveGame->mPlayerInfo.PlayerAttribute = MyPlayer->GetPlayerInfo().PlayerAttribute;
	MySaveGame->mPlayerInfo.PlayerAttributeLevel = MyPlayer->GetPlayerInfo().PlayerAttributeLevel;
	MySaveGame->mPlayerInfo.PlayerAttributeMaxLevel = MyPlayer->GetPlayerInfo().PlayerAttributeMaxLevel;


	// Baisic Upgrade Info
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.bIsExp = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.bIsExp;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.bIsHP = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.bIsHP;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.bIsMP = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.bIsMP;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.bIsArmor = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.bIsArmor;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.mExpLevel = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.mExpLevel;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.mExpMaxLevel = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.mExpMaxLevel;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.mHPLevel = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.mHPLevel;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.mHPMaxLevel = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.mHPMaxLevel;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.mMPLevel = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.mMPLevel;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.mMPMaxLevel = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.mMPMaxLevel;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.mArmorLevel = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.mArmorLevel;
	MySaveGame->mPlayerInfo.BasicUpgradeInfo.mArmorMaxLevel = MyPlayer->GetPlayerInfo().BasicUpgradeInfo.mArmorMaxLevel;


	//Projectile
	MySaveGame->mPlayerInfo.ProjectileInfo.mHoming = MyPlayer->GetPlayerInfo().ProjectileInfo.mHoming;
	MySaveGame->mPlayerInfo.ProjectileInfo.mDuplicate = MyPlayer->GetPlayerInfo().ProjectileInfo.mDuplicate;
	MySaveGame->mPlayerInfo.ProjectileInfo.mDuplicateProbability = MyPlayer->GetPlayerInfo().ProjectileInfo.mDuplicateProbability;
	MySaveGame->mPlayerInfo.ProjectileInfo.mMaxDuplicateProbability = MyPlayer->GetPlayerInfo().ProjectileInfo.mMaxDuplicateProbability;
	MySaveGame->mPlayerInfo.ProjectileInfo.mDuplicateCount = MyPlayer->GetPlayerInfo().ProjectileInfo.mDuplicateCount;
	MySaveGame->mPlayerInfo.ProjectileInfo.mMaxDuplicateCount = MyPlayer->GetPlayerInfo().ProjectileInfo.mMaxDuplicateCount;
	MySaveGame->mPlayerInfo.ProjectileInfo.mProjectileSpeed = MyPlayer->GetPlayerInfo().ProjectileInfo.mProjectileSpeed;
	MySaveGame->mPlayerInfo.ProjectileInfo.mMaxProjectileSpeed = MyPlayer->GetPlayerInfo().ProjectileInfo.mMaxProjectileSpeed;
	MySaveGame->mPlayerInfo.ProjectileInfo.mProjectileScale = MyPlayer->GetPlayerInfo().ProjectileInfo.mProjectileScale;
	MySaveGame->mPlayerInfo.ProjectileInfo.mMaxProjectileScale = MyPlayer->GetPlayerInfo().ProjectileInfo.mMaxProjectileScale;
	MySaveGame->mPlayerInfo.ProjectileInfo.mProjectileDamage = MyPlayer->GetPlayerInfo().ProjectileInfo.mProjectileDamage;
	MySaveGame->mPlayerInfo.ProjectileInfo.mProjectileDamageScale = MyPlayer->GetPlayerInfo().ProjectileInfo.mProjectileDamageScale;
	MySaveGame->mPlayerInfo.ProjectileInfo.mMaxProjectileDamageScale = MyPlayer->GetPlayerInfo().ProjectileInfo.mMaxProjectileDamageScale;


	//Skill & Attribute
	MySaveGame->mSkillEnable = MyPlayer->mSkillEnable;
	MySaveGame->mSkillEffectAttributeIndex = MyPlayer->GetSkillEffectAttributeIndex();


	// Dungeon Stage Number
	MySaveGame->mStageNum = this->mStageNum;





	return MySaveGame;
}

void ARandomRoomGameMode::SaveGame(int32 SaveIndex)
{
	mSaveGame = CreateSaveGame();

	if (mSaveGame == nullptr)
		return;


	//FString FullPath = FPaths::ProjectSavedDir() + TEXT("SaveGames/Save.txt");
	FString FullPath = FPaths::ProjectSavedDir() + TEXT("SaveGames/") + FString::FromInt(SaveIndex) + TEXT("/Save.txt");

	FArchive* Writer = IFileManager::Get().CreateFileWriter(
		*FullPath);

	if (Writer)
	{
		// Player Basic1
		*Writer << mSaveGame->mPlayerInfo.Name;
		*Writer << mSaveGame->mPlayerInfo.AttackPoint;
		*Writer << mSaveGame->mPlayerInfo.ArmorPoint;
		*Writer << mSaveGame->mPlayerInfo.HP;
		*Writer << mSaveGame->mPlayerInfo.HPMax;
		*Writer << mSaveGame->mPlayerInfo.MP;
		*Writer << mSaveGame->mPlayerInfo.MPMax;
		*Writer << mSaveGame->mPlayerInfo.Level;
		*Writer << mSaveGame->mPlayerInfo.Exp;
		*Writer << mSaveGame->mPlayerInfo.Gold;
		*Writer << mSaveGame->mPlayerInfo.MoveSpeed;
		*Writer << mSaveGame->mPlayerInfo.Mesh;

		// Player Basic2
		*Writer << mSaveGame->mPlayerInfo.PlayerClass;
		*Writer << mSaveGame->mPlayerInfo.BaseAttackDistance;
		*Writer << mSaveGame->mPlayerInfo.PlayerAttribute;
		*Writer << mSaveGame->mPlayerInfo.PlayerAttributeLevel;
		*Writer << mSaveGame->mPlayerInfo.PlayerAttributeMaxLevel;

		// Baisic Upgrade Info
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.bIsExp;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.bIsHP;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.bIsMP;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.bIsArmor;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.mExpLevel;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.mExpMaxLevel;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.mHPLevel;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.mHPMaxLevel;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.mMPLevel;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.mMPMaxLevel;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.mArmorLevel;
		*Writer << mSaveGame->mPlayerInfo.BasicUpgradeInfo.mArmorMaxLevel;


		//Projectile
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mHoming;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mDuplicate;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mDuplicateProbability;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mMaxDuplicateProbability;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mDuplicateCount;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mMaxDuplicateCount;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mProjectileSpeed;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mMaxProjectileSpeed;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mProjectileScale;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mMaxProjectileScale;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mProjectileDamage;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mProjectileDamageScale;
		*Writer << mSaveGame->mPlayerInfo.ProjectileInfo.mMaxProjectileDamageScale;

		//Skill & Attribute
		*Writer << mSaveGame->mSkillEnable;
		*Writer << mSaveGame->mSkillEffectAttributeIndex;


		// Dungeon Stage Number
		*Writer << mSaveGame->mStageNum;


		// 사용이 끝났다면 스트림을 닫아주고 제거해야 한다.
		Writer->Close();

		delete Writer;
	}

}
