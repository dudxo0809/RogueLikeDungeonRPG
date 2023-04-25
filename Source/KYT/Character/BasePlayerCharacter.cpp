// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCharacter.h"

#include "../KYTGameInstance.h"
#include "PlayerAnimInstance.h"
#include "BasePlayerController.h"

#include "CameraAnimationSequence.h"
#include "Components/SceneCaptureComponent2D.h"

#include "../RandomRoom/RandomRoomGameMode.h"



ABasePlayerCharacter::ABasePlayerCharacter() :
	mMoveForwardDir(0.f),
	mDeath(false),
	mHitActor(nullptr),
	mWeapon(nullptr)
	
{
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// SpringArm�� Mesh�� Child�� �����Ѵ�.
	mSpringArm->SetupAttachment(GetMesh());

	// Camera ������Ʈ�� SpringArm ������Ʈ�� �ڽ� ������Ʈ�� �ٿ��ش�.
	mCamera->SetupAttachment(mSpringArm);

	mSpringArm->TargetArmLength = 1500.f;

	mSpringArm->SetRelativeLocation(FVector(0.0, 0.0, 160.0));
	mSpringArm->SetRelativeRotation(FRotator(300.0, 90.0, 0));

	mSpringArm->bDoCollisionTest = false;


	

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetCanBeDamaged(true);



	mMovable = true;

	mSkillEffectAttributeIndex = 0;

	mSkillEnable.Empty();

	mSkillEnable = { 1,0,0,0 };
	
	
	mSceneCapture2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture2D"));
	mSceneCapture2D->SetupAttachment(GetMesh());

	mSceneCapture2D->SetRelativeLocation(FVector(0.0, 0.0, 7000.0));
	mSceneCapture2D->SetRelativeRotation(FRotator(-90, 0, 90));


	// Load RenderTarget : BP Minimap
	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D>	TextureTarget2D(TEXT("TextureRenderTarget2D'/Game/KYT/UMG/RT_Minimap.RT_Minimap'"));
	if (TextureTarget2D.Succeeded()) {

		mSceneCapture2D->TextureTarget = TextureTarget2D.Object;
		mSceneCapture2D->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterial> finder(TEXT("Material'/Game/KYT/UMG/MT_Minimap.MT_Minimap'"));
	if (finder.Succeeded())
	{
		mMinimapMaterial = finder.Object;
	}
	

	mNormalAttackVolume = 0.5f;
	mSkillVolume = 0.6f;

}

void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UKYTGameInstance* GameInst = GetWorld()->GetGameInstance<UKYTGameInstance>();

	const FPlayerCharacterTable* Info = GameInst->FindPlayerTable(mPlayerTableRowName);


	int32 CurrentSaveIndex = -1;
	
	UKYTGameInstance* MyGameInst = Cast<UKYTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(MyGameInst)) {

		CurrentSaveIndex = MyGameInst->GetCurrentSaveIndex();
	}
	

	// Load Plaer Info from SaveGame
	FString FullPath = FPaths::ProjectSavedDir() + TEXT("SaveGames/") + FString::FromInt(CurrentSaveIndex) +  TEXT("/Save.txt");

	TSharedPtr<FArchive>	Reader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));
	if (Reader.IsValid())
	{
		// Player Basic1
		*Reader.Get() << mInfo.Name;
		*Reader.Get() << mInfo.AttackPoint;
		*Reader.Get() << mInfo.ArmorPoint;
		*Reader.Get() << mInfo.HP;
		*Reader.Get() << mInfo.HPMax;
		*Reader.Get() << mInfo.MP;
		*Reader.Get() << mInfo.MPMax;
		*Reader.Get() << mInfo.Level;
		*Reader.Get() << mInfo.Exp;
		*Reader.Get() << mInfo.Gold;
		*Reader.Get() << mInfo.MoveSpeed;
		*Reader.Get() << mInfo.Mesh;
	
		// Player Basic2
		*Reader.Get() << mInfo.PlayerClass;
		*Reader.Get() << mInfo.BaseAttackDistance;
		*Reader.Get() << mInfo.PlayerAttribute;
		*Reader.Get() << mInfo.PlayerAttributeLevel;
		*Reader.Get() << mInfo.PlayerAttributeMaxLevel;
		

		// Baisic Upgrade Info
		*Reader.Get() << mInfo.BasicUpgradeInfo.bIsExp;
		*Reader.Get() << mInfo.BasicUpgradeInfo.bIsHP;
		*Reader.Get() << mInfo.BasicUpgradeInfo.bIsMP;
		*Reader.Get() << mInfo.BasicUpgradeInfo.bIsArmor;
		*Reader.Get() << mInfo.BasicUpgradeInfo.mExpLevel;
		*Reader.Get() << mInfo.BasicUpgradeInfo.mExpMaxLevel;
		*Reader.Get() << mInfo.BasicUpgradeInfo.mHPLevel;
		*Reader.Get() << mInfo.BasicUpgradeInfo.mHPMaxLevel;
		*Reader.Get() << mInfo.BasicUpgradeInfo.mMPLevel;
		*Reader.Get() << mInfo.BasicUpgradeInfo.mMPMaxLevel;
		*Reader.Get() << mInfo.BasicUpgradeInfo.mArmorLevel;
		*Reader.Get() << mInfo.BasicUpgradeInfo.mArmorMaxLevel;


		//Projectile
		*Reader.Get() << mInfo.ProjectileInfo.mHoming;
		*Reader.Get() << mInfo.ProjectileInfo.mDuplicate;
		*Reader.Get() << mInfo.ProjectileInfo.mDuplicateProbability;
		*Reader.Get() << mInfo.ProjectileInfo.mMaxDuplicateProbability;
		*Reader.Get() << mInfo.ProjectileInfo.mDuplicateCount;
		*Reader.Get() << mInfo.ProjectileInfo.mMaxDuplicateCount;
		*Reader.Get() << mInfo.ProjectileInfo.mProjectileSpeed;
		*Reader.Get() << mInfo.ProjectileInfo.mMaxProjectileSpeed;
		*Reader.Get() << mInfo.ProjectileInfo.mProjectileScale;
		*Reader.Get() << mInfo.ProjectileInfo.mMaxProjectileScale;
		*Reader.Get() << mInfo.ProjectileInfo.mProjectileDamage;
		*Reader.Get() << mInfo.ProjectileInfo.mProjectileDamageScale;
		*Reader.Get() << mInfo.ProjectileInfo.mMaxProjectileDamageScale;
	
		//Skill & Attribute
		*Reader.Get() << mSkillEnable;
		*Reader.Get() << mSkillEffectAttributeIndex;


		// Set Dungeon Stage
		int32 StageNum;
		*Reader.Get() << StageNum;

		ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(MyGameMode)) {

			MyGameMode->SetStageNumber(StageNum);
		}

	}
	else {

		mInfo.Name = Info->Name;
		mInfo.AttackPoint = Info->AttackPoint;
		mInfo.ArmorPoint = Info->ArmorPoint;
		mInfo.HP = Info->HP;
		mInfo.HPMax = Info->HP;
		mInfo.MP = Info->MP;
		mInfo.MPMax = Info->MP;
		mInfo.Level = Info->Level;
		mInfo.Exp = Info->Exp;
		mInfo.Gold = Info->Gold;
		mInfo.MoveSpeed = Info->MoveSpeed;
		mInfo.BaseAttackDistance = Info->BaseAttackDistance;

		mInfo.PlayerAttributeLevel = Info->PlayerAttributeLevel;
		mInfo.PlayerAttributeMaxLevel = Info->PlayerAttributeMaxLevel;

		mInfo.Mesh = Info->Mesh;

		mInfo.BasicUpgradeInfo = Info->BasicUpgradeInfo;

		mInfo.ProjectileInfo = Info->ProjectileInfo;

		// Stage 1
		ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (IsValid(MyGameMode)) {

			MyGameMode->SetStageNumber(1);
		}
	}

	mInfo.Mesh = Info->Mesh;

	mInfo.SkillDataArray = Info->SkillDataArray;
	mInfo.SkillEffect = Info->SkillEffect;

	mNormalAttackCameraShakeSequence =
		LoadObject<UCameraAnimationSequence>(nullptr, TEXT("CameraAnimationSequence'/Game/KYT/BluePrint/CameraShake/CAS_Player_Attack.CAS_Player_Attack'"));


	GetMesh()->SetSkeletalMesh(mInfo.Mesh);
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -88.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	GetCharacterMovement()->JumpZVelocity = 650.f;
	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	SetAttribute((EPlayerAttribute)mSkillEffectAttributeIndex);

	mAnimInst->Start();

	SyncPlayerStatus();
	
}

void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	SyncPlayerStatus();
}

void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis<ABasePlayerCharacter>(TEXT("MoveForward"),
		this, &ABasePlayerCharacter::MoveForward);

	PlayerInputComponent->BindAxis<ABasePlayerCharacter>(TEXT("MoveSide"),
		this, &ABasePlayerCharacter::MoveSide);

	PlayerInputComponent->BindAxis<ABasePlayerCharacter>(TEXT("RotationCameraZ"),
		this, &ABasePlayerCharacter::RotationCameraZ);

	PlayerInputComponent->BindAxis<ABasePlayerCharacter>(TEXT("CameraZoom"),
		this, &ABasePlayerCharacter::CameraZoom);

	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("Jump"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::Jump);

	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("MouseMove"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::MouseMove);

	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("NormalAttack"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::NormalAttack);
	


	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("Skill1"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::Skill1);

	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("Skill2"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::Skill2);

	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("Skill3"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::Skill3);

	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("Skill4"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::Skill4);


	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("Dash"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::Dash);


	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("PlayerInfoMenu"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::PlayerInfoMenu);

	PlayerInputComponent->BindAction<ABasePlayerCharacter>(TEXT("Test"),
		EInputEvent::IE_Pressed, this,
		&ABasePlayerCharacter::Test);

}

void ABasePlayerCharacter::MoveForward(float Scale)
{
	if (mDeath)
		return;

	if (!mMovable)
		return;

	mMoveForwardDir = Scale;

	if (Scale == 0.f)
		return;

	// AddMovementInput : ĳ���� Ŭ�������� ĳ���� �����Ʈ ������Ʈ��
	// �̿��Ͽ� �̵��ϴ� ����� �������� �Լ��̴�.
	// GetActorForwardVector() : �� ������ ���� ���⺤�͸� ���´�.
	AddMovementInput(GetActorForwardVector(), Scale);
}

void ABasePlayerCharacter::MoveSide(float Scale)
{
	if (mDeath)
		return;

	if (!mMovable)
		return;
	
	if (mMoveForwardDir == 1.f)
	{
		// wŰ�� ���� ���¿��� a, d�� ���� ����.
		if (Scale == 0.f) {
			mAnimInst->SetMoveDir(0.f);
			mMoveDir = 0.f;
		}
		// wŰ�� ���� ���¿��� ���������� �̵�.
		else if (Scale == 1.f) {
			mAnimInst->SetMoveDir(45.f);
			mMoveDir = 45.f;
		}
		// wŰ�� ���� ���¿��� �������� �̵�.
		else if (Scale == -1.f) {
			mAnimInst->SetMoveDir(-45.f);
			mMoveDir = -45.f;
		}
	}

	else if (mMoveForwardDir == -1.f)
	{
		// sŰ�� ���� ���¿��� a, d�� ���� ����.
		if (Scale == 0.f) {
			mAnimInst->SetMoveDir(180.f);
			mMoveDir = 180.f;
		}
		// sŰ�� ���� ���¿��� ���������� �̵�.
		else if (Scale == 1.f) {
			mAnimInst->SetMoveDir(135.f);
			mMoveDir = 135.f;
		}
		// sŰ�� ���� ���¿��� �������� �̵�.
		else if (Scale == -1.f) {
			mAnimInst->SetMoveDir(-135.f);
			mMoveDir = -135.f;
		}
	}

	else
	{
		// �ƹ� Ű�� ������ ���� ���
		if (Scale == 0.f) {
			mAnimInst->SetMoveDir(0.f);
			mMoveDir = 0.f;
		}
		// ���������� �̵�.
		else if (Scale == 1.f) {
			mAnimInst->SetMoveDir(90.f);
			mMoveDir = 90.f;
		}
		// �������� �̵�.
		else if (Scale == -1.f) {
			mAnimInst->SetMoveDir(-90.f);
			mMoveDir = -90.f;
		}
	}

	if (Scale == 0.f)
		return;

	// AddMovementInput : ĳ���� Ŭ�������� ĳ���� �����Ʈ ������Ʈ��
	// �̿��Ͽ� �̵��ϴ� ����� �������� �Լ��̴�.
	// GetActorRightVector() : �� ������ ������ ���⺤�͸� ���´�.
	AddMovementInput(GetActorRightVector(), Scale);

	
}



void ABasePlayerCharacter::Jump()
{
	if (mDeath)
		return;

	if (!mMovable)
		return;

	// ������� ��� �� ���� ������ ������ �����ϵ��� �Ѵ�.
	else if (mAnimInst->GetPlayerAnimType() != EPlayerAnimType::Ground)
		return;

	ACharacter::Jump();


	mAnimInst->Jump();
}

void ABasePlayerCharacter::MouseMove()
{


}

void ABasePlayerCharacter::NormalAttack()
{
	if (mDeath)
		return;

	if (mAnimInst->Attack()) {
		// ������ ó�� �߰�

		
	}
	else {

		
	}
	

}


void ABasePlayerCharacter::NormalAttackEffect(int32 ComboCount)
{

}




void ABasePlayerCharacter::RotationCameraZ(float Scale)
{
	if (mDeath)
		return;

	if (Scale == 0.f)
		return;

	Scale *= 0.5f;

	//mSpringArm->AddRelativeRotation(FRotator(0.f, Scale * 180.f * GetWorld()->GetDeltaSeconds(), 0.f));
	AddControllerYawInput(Scale * 180.f * GetWorld()->GetDeltaSeconds());
}


void ABasePlayerCharacter::CameraZoom(float Scale)
{
	if (Scale == 0.f)
		return;


	mSpringArm->TargetArmLength += Scale * -5.f;


	float	CameraZoomMin = 100.f, CameraZoomMax = 2500.f;

	if (mSpringArm->TargetArmLength < CameraZoomMin)
		mSpringArm->TargetArmLength = CameraZoomMin;

	else if (mSpringArm->TargetArmLength > CameraZoomMax)
		mSpringArm->TargetArmLength = CameraZoomMax;
}

void ABasePlayerCharacter::SetPlayerMovable(bool Movable)
{
	if (Movable) {

		mMovable = true;
	}
	else {
		mMovable = false;
		mStopLocation = GetActorLocation();
	}
}



void ABasePlayerCharacter::SetAttribute(EPlayerAttribute PlayerAttribute)
{

	mInfo.PlayerAttribute = PlayerAttribute;
	
	mSkillEffectAttributeIndex = (int32)PlayerAttribute;

}




void ABasePlayerCharacter::PlayerLevelUpScreen()
{
	ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!IsValid(MyGameMode)) 
	{
		return;
	}
	
	UMainHUDBase* MainHUD = MyGameMode->GetMainHUD();

	MainHUD->ShowPlayerLevelUp(mInfo);




}




float ABasePlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	int32 Damage = (int32)Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage = Damage - mInfo.ArmorPoint;

	Damage = Damage < 1 ? 1 : Damage;

	mInfo.HP -= Damage;

	if (mInfo.HP <= 0)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// �׾���.
		//mAnimInst->ChangeAnim(EPlayerAnimType::Death);

		mAnimInst->SetPlayerAnimType(EPlayerAnimType::Death);

		mDeath = true;
	
		mInfo.MP = 0;

		SyncPlayerStatus();
	}

	else
	{
		//mAnimInst->Hit();

		SyncPlayerStatus();
	}

	return Damage;
}

void ABasePlayerCharacter::UseSkill(int32 SkillNumber)
{


}

void ABasePlayerCharacter::ApplyDamage(int32 SkillNumber)
{
}

void ABasePlayerCharacter::Skill1()
{
}

void ABasePlayerCharacter::Skill2()
{
}

void ABasePlayerCharacter::Skill3()
{
}

void ABasePlayerCharacter::Skill4()
{
}

void ABasePlayerCharacter::Dash()
{
}

void ABasePlayerCharacter::GetExp(float Exp)
{
	// ������ ����ġ
	// 
	// 1 : 1000 ����
	// 2 : 1500 
	// 3 : 2000
	//
	// 500�� ����

	mInfo.Exp += Exp;

	float LevelUpExp = 500 + (500 * mInfo.Level);

	if (mInfo.Exp > LevelUpExp) {

		mInfo.Exp = mInfo.Exp - LevelUpExp;
		mInfo.Level += 1;

		LevelUp();
	}

	// 
	SyncPlayerStatus();

}

void ABasePlayerCharacter::LevelUp()
{

	// ������ ��
	// �÷��̾ ���׷��̵� ������ �׸� ���� ������Ʈ�Ѵ�.
	UKYTGameInstance* GameInst = GetWorld()->GetGameInstance<UKYTGameInstance>();

	TArray<FPlayerSkillUpgradeTable*> SkillUpgradeArray = GameInst->FindPlayerSkillUpgradeTable();

	mInfo.PlayerUpgradeSkillArray.Empty();

	

	for (auto Info : SkillUpgradeArray) {

		bool bAddUpgradeInfo = true;

		if (mInfo.Level < Info->LimitLevel)
			bAddUpgradeInfo = false;

		else if (!(mInfo.PlayerClass == Info->LimitPlayerClass || Info->LimitPlayerClass == E_Player_Class::None))
			bAddUpgradeInfo = false;


		// �⺻ �ɷ�ġ ��ȭ
		else if (Info->IsBasic) 
		{

		}


		// �Ӽ� ��ȭ
		else if (Info->IsAttribute) 
		{
			int32 AttributeIndex = (int32)Info->AttributeType;

			// �ִ� ������ �޼��� �Ӽ���ȭ�� �н���
			if (mInfo.PlayerAttributeLevel[AttributeIndex] >= mInfo.PlayerAttributeMaxLevel[AttributeIndex])
				bAddUpgradeInfo = false;

			// Arcane Type�� �Ӽ��� Max�� ��ȭ�ؾ� ���ο� �Ӽ��� ��ȭ�� �� ����
			if (Info->AttributeType == EPlayerAttribute::Fire ||
				Info->AttributeType == EPlayerAttribute::Ice || 
				Info->AttributeType == EPlayerAttribute::Thunder || 
				Info->AttributeType == EPlayerAttribute::Poison) {

				if (mInfo.PlayerAttributeLevel[(int32)EPlayerAttribute::Arcane] < mInfo.PlayerAttributeMaxLevel[(int32)EPlayerAttribute::Arcane])
					bAddUpgradeInfo = false;
			}

			// Fire, Ice, Thunder, Poison �� �ϳ��� Max��ȭ�ؾ� Holy, Shadow ��ȭ����
			else if (Info->AttributeType == EPlayerAttribute::Holy ||
				Info->AttributeType == EPlayerAttribute::Shadow) {

				if (mInfo.PlayerAttributeLevel[(int32)EPlayerAttribute::Fire] < mInfo.PlayerAttributeMaxLevel[(int32)EPlayerAttribute::Fire] && 
					mInfo.PlayerAttributeLevel[(int32)EPlayerAttribute::Ice] < mInfo.PlayerAttributeMaxLevel[(int32)EPlayerAttribute::Ice] &&
					mInfo.PlayerAttributeLevel[(int32)EPlayerAttribute::Thunder] < mInfo.PlayerAttributeMaxLevel[(int32)EPlayerAttribute::Thunder] &&
					mInfo.PlayerAttributeLevel[(int32)EPlayerAttribute::Poison] < mInfo.PlayerAttributeMaxLevel[(int32)EPlayerAttribute::Poison])

					bAddUpgradeInfo = false;
			}

			// Holy, Shadow �� �ϳ��� Max��ȭ�ؾ� Void��ȭ����
			else if (Info->AttributeType == EPlayerAttribute::Void) {

				if (mInfo.PlayerAttributeLevel[(int32)EPlayerAttribute::Holy] < mInfo.PlayerAttributeMaxLevel[(int32)EPlayerAttribute::Holy] &&
					mInfo.PlayerAttributeLevel[(int32)EPlayerAttribute::Shadow] < mInfo.PlayerAttributeMaxLevel[(int32)EPlayerAttribute::Shadow])

					bAddUpgradeInfo = false;
			}
		}

		// Projectile ��ȭ
		else if (Info->IsProjectile)
		{
			if (Info->IsProjectileHoming) 
			{
				if (mInfo.ProjectileInfo.mHoming)
					bAddUpgradeInfo = false;

			}
			else if(Info->IsProjectileDuplicate)
			{
				if (mInfo.ProjectileInfo.mDuplicate)
					bAddUpgradeInfo = false;

			}
			else if(Info->IsProjectileDuplicateProbability)
			{
				if (mInfo.ProjectileInfo.mDuplicate == false)
					bAddUpgradeInfo = false;

				if (mInfo.ProjectileInfo.mDuplicateProbability >= mInfo.ProjectileInfo.mMaxDuplicateProbability)
					bAddUpgradeInfo = false;

			}
			else if (Info->IsProjectileSpeed)
			{
				if (mInfo.ProjectileInfo.mProjectileSpeed >= mInfo.ProjectileInfo.mMaxProjectileSpeed)
					bAddUpgradeInfo = false;

			}
			else if (Info->IsProjectileScale)
			{
				if (mInfo.ProjectileInfo.mProjectileScale >= mInfo.ProjectileInfo.mMaxProjectileScale)
					bAddUpgradeInfo = false;

			}
			else if (Info->IsProjectileDamageScale)
			{
				if (mInfo.ProjectileInfo.mProjectileDamageScale >= mInfo.ProjectileInfo.mMaxProjectileDamageScale)
					bAddUpgradeInfo = false;

			}
			else if (Info->IsProjectileDuplicateCount)
			{
				if (mInfo.ProjectileInfo.mDuplicate == false)
					bAddUpgradeInfo = false;

				if (mInfo.ProjectileInfo.mDuplicateCount >= mInfo.ProjectileInfo.mMaxDuplicateCount)
					bAddUpgradeInfo = false;

			}

		}

		if (bAddUpgradeInfo == false)
			continue;

		FPlayerSkillUpgradeInfo Skill;

		Skill.Name = Info->Name;
		Skill.Description = Info->Description;
		Skill.Icon = Info->Icon;
		Skill.IncreaseValue_float = Info->IncreaseValue_float;
		Skill.IncreaseValue_int32 = Info->IncreaseValue_int32;

		Skill.IsAttribute = Info->IsAttribute;
		Skill.IsProjectile = Info->IsProjectile;

		Skill.AttributeType = Info->AttributeType;

		Skill.IsProjectileHoming = Info->IsProjectileHoming;
		Skill.IsProjectileDuplicate = Info->IsProjectileDuplicate;
		Skill.IsProjectileDuplicateCount = Info->IsProjectileDuplicateCount;
		Skill.IsProjectileScale = Info->IsProjectileScale;
		Skill.IsProjectileDamageScale = Info->IsProjectileDamageScale;
		Skill.IsProjectileSpeed = Info->IsProjectileSpeed;

		mInfo.PlayerUpgradeSkillArray.Add(Skill);
	}

	// Player
	// 
	// Attack, Armor 1.05 ��
	// 
	// HP. MP 1.1  ��
	mInfo.AttackPoint *= 1.05f;
	mInfo.ArmorPoint *= 1.05f;
	mInfo.HPMax *= 1.1f;
	mInfo.MPMax *= 1.1f;


	mInfo.HP = mInfo.HPMax;
	mInfo.MP = mInfo.MPMax;
	//

	PlayerLevelUpScreen();

	// HUD
	//
	// ������ ȭ�� ����
	// 
	// Ư�� ���� �޼��� �÷��̾� ��ų �ϳ��� �ر�
	// Ư�� ���� �޼��� ���� �Ӽ� �ر� (���� Ŭ�������� ����)
	//
	// 
	// 5 : Skill1
	// 10 : Skill2
	// 15 : Skill3
	// 20 : Skill4

	

	switch (mInfo.Level) {

	case 5 :
		mSkillEnable[1] = true;
		break;

	case 10:
		mSkillEnable[2] = true;
		break;

	case 15:
		mSkillEnable[3] = true;
		break;


	default:
		break;
	}

}

void ABasePlayerCharacter::PlayerInfoMenu()
{
	ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!IsValid(MyGameMode))
		return;

	if (!MyGameMode->GetMainHUD()->IsPlayerInfoMenuScreenShow()) {

		MyGameMode->GetMainHUD()->ShowPlayerInfoMenu();

	}
	else {

		MyGameMode->GetMainHUD()->HidePlayerInfoMenu();
	}

}

void ABasePlayerCharacter::SyncPlayerStatus()
{

	ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (IsValid(MyGameMode)) {

		UMainHUDBase* MainHUD =  MyGameMode->GetMainHUD();
		
		// Player HP & MP
		MainHUD->SetHP((float)mInfo.HP / mInfo.HPMax);
		MainHUD->SetMP((float)mInfo.MP / mInfo.MPMax);

		//Playe Exp
		float LevelUpExp = 500 + (500 * mInfo.Level);

		MainHUD->SetExp((float)mInfo.Exp / LevelUpExp);

		// Player Level
		MainHUD->SetLevel(mInfo.Level);

		// skill Icon
		for (int32 i = 0; i < 4; i++) {

			MainHUD->SetSkillImage(i, mSkillEnable[i]);
		}	

		//Staqge Number
		int32 CurrentStageNumber = MyGameMode->GetStageNumber();

		MainHUD->SetStageNumber(CurrentStageNumber);


		// Player Attribute Level
		MainHUD->SetAttributeLevel();
	}

}

// �׽�Ʈ�� �Լ�
// Ctrl
void ABasePlayerCharacter::Test()
{
	/*
	ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!IsValid(MyGameMode))
	{
		return;
	}
	UMainHUDBase* MainHUD = MyGameMode->GetMainHUD();

	if (!MainHUD->IsPlayerLevelUpScreenShow())
		MainHUD->ShowPlayerLevelUp(mInfo);
	else
		MainHUD->HidePlayerLevelUp();


	*/
}
