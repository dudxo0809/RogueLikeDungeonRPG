// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMonster.h"

#include "MonsterSpawnPoint.h"
#include "../KYTGameInstance.h"
#include "MonsterAIController.h"
#include "MonsterAnimInstance.h"

#include "../UMG/MonsterHP.h"

#include "../RandomRoom/RandomRoomGameMode.h"

#include "../Character/BasePlayerCharacter.h"
#include "../Character/MagicianPlayerCharacter.h"

#include "../Skill/Projectile.h"
#include "ExpProjectile.h"

ABaseMonster::ABaseMonster()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterAIController::StaticClass();
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
	GetCapsuleComponent()->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;


	// 몬스터의 HP UI 를 표현해 줄 WidgetComponent 를 추가한다.
	mWidgetComopnent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetCom"));
	mWidgetComopnent->SetupAttachment(GetMesh());

	ConstructorHelpers::FClassFinder<UUserWidget>
		finder(TEXT("WidgetBlueprint'/Game/KYT/UMG/UI_MonsterHP.UI_MonsterHP_C'"));

	if (finder.Succeeded())
	{
		mMonsterHPClass = finder.Class;
	}

	mExpProjectile = nullptr;

	mStageNum = 1;

	mDead = false;
	mDestroyStart = false;

	mAttackLocationDist = 60.f;

	mDestroyTime = 10.f;
	mDestroyCurrentTime = 0.f;

}

void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();

	UKYTGameInstance* GameInst =
		GetWorld()->GetGameInstance<UKYTGameInstance>();

	const FMonsterTableBase* TableInfo =
		GameInst->FindMonsterTable(mMonsterTableRowName);


	ARandomRoomGameMode* MyGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode)) {

		mStageNum = MyGameMode->GetStageNumber();
	}
	float MonsterAbilityScale = 1 + (0.5 * (mStageNum - 1));


	if (TableInfo)
	{
		// Set Monster Level first
		int32 LevelOffset = FMath::RandRange(0, 3);

		mInfo.Level = TableInfo->Level * MonsterAbilityScale + LevelOffset;

		// Set Monster Ability based on Monster Level
		MonsterAbilityScale += 0.3 * mInfo.Level;

		mInfo.Name = TableInfo->Name;
		mInfo.AttackPoint = TableInfo->AttackPoint * MonsterAbilityScale;
		mInfo.ArmorPoint = TableInfo->ArmorPoint * MonsterAbilityScale;
		mInfo.HP = TableInfo->HP * MonsterAbilityScale;
		mInfo.HPMax = TableInfo->HP * MonsterAbilityScale;
		mInfo.MP = TableInfo->MP * MonsterAbilityScale;
		mInfo.MPMax = TableInfo->MP * MonsterAbilityScale;

		

		
		mInfo.Exp = TableInfo->Exp * MonsterAbilityScale;
		mInfo.Gold = TableInfo->Gold;
		mInfo.MoveSpeed = TableInfo->MoveSpeed;
		mInfo.AttackDistance = TableInfo->AttackDistance;
		mInfo.TraceDistance = TableInfo->TraceDistance;

		mInfo.SkillDataArray = TableInfo->SkillDataArray;
		mInfo.SkillEffectArray = TableInfo->SkillEffectArray;

		// 이동속도를 적용한다.
		// 앉아서 이동시 이동속도의 반으로 지정한다.
		GetCharacterMovement()->MaxWalkSpeed = mInfo.MoveSpeed;
		GetCharacterMovement()->MaxWalkSpeedCrouched = mInfo.MoveSpeed * 0.5f;

		GetMesh()->SetSkeletalMesh(TableInfo->Mesh);

		GetMesh()->SetAnimInstanceClass(TableInfo->MonsterAnimClass);
		mAnimInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
		
	}


	// 위젯 블루프린트 UClass 정보를 이용해서 객체를 만들어낸다.
	if (IsValid(mMonsterHPClass))
	{
		// 생성한 객체의 주소를 m_MainHUD 에 받아둔다.
		mMonsterHP = Cast<UMonsterHP>(CreateWidget(GetWorld(), mMonsterHPClass));
		if (IsValid(mMonsterHP))
		{
			mWidgetComopnent->SetWidgetSpace(EWidgetSpace::Screen);

			mWidgetComopnent->SetDrawSize(FVector2D(0.5f, 0.5f));
			mWidgetComopnent->SetRelativeLocation(FVector(0, 0, 200.f));

			mWidgetComopnent->SetWidget(mMonsterHP);
		}
	}

	// 위젯컴포넌트가 지정한 MonsterHPBase 위젯에 프로그레스바를 조정한다.
	if (IsValid(mMonsterHP))
	{
		mMonsterHP->SetHPPercent(1.f);

		mMonsterHP->SetLevel(mInfo.Level);
	}
	
	// sound
	mNormalAttackSoundPath = TEXT("SoundWave'/Game/UltimateMagicUE/wav/Buffs/Buff_24.Buff_24'");

	UKYTGameInstance* Inst = Cast<UKYTGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	float MasterVolumeScale = Inst->GetVolume().MasterVolumeScale;

	float MonsterVolumeScale = Inst->GetVolume().MonsterVolumeScale * MasterVolumeScale;

	mMonsterAttackVolume = MonsterVolumeScale;
}

void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mDead && mDestroyStart)
	{
		mDestroyCurrentTime += DeltaTime;
		if (mDestroyCurrentTime >= mDestroyTime) {

			this->Destroy();
		}
	}
}

void ABaseMonster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 부모 기능을 실행하기 전에 먼저 BehaviorTree와
	// Blackboard를 지정해준다.
	AMonsterAIController* AI =
		Cast<AMonsterAIController>(NewController);

	if (IsValid(AI))
	{
		AI->SetBehaviorTree(TEXT("BehaviorTree'/Game/KYT/Monster/AI/Monster/BT_Monster.BT_Monster'"));
		AI->SetBlackboard(TEXT("BlackboardData'/Game/KYT/Monster/AI/Monster/BB_Monster.BB_Monster'"));
	}
}

void ABaseMonster::UnPossessed()
{

	Super::UnPossessed();
}

void ABaseMonster::SetExpHoming()
{
	if (mExpProjectile != nullptr) {

		mExpProjectile->SetSpeed(1000.f);
		mExpProjectile->SetHoming(true);

	}

}

void ABaseMonster::DestroyStart(float DestroyTime)
{
	mDestroyStart = true;
	mDestroyTime = DestroyTime;
}

float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 Damage = (int32)Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Damage = Damage - mInfo.ArmorPoint;

	Damage = Damage < 1 ? 1 : Damage;

	mInfo.HP -= Damage;
	

	float Ratio = (float)mInfo.HP / mInfo.HPMax;
	mMonsterHP->SetHPPercent(Ratio);

	if (mInfo.HP <= 0)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// 죽었다.
		mAnimInst->ChangeAnim(EMonsterAnimType::Death);

		AAIController* AI = Cast<AAIController>(GetController());

		if (IsValid(AI))
			AI->BrainComponent->StopLogic(TEXT("Death"));


		mDead = true;
		

		FActorSpawnParameters	SpawnParam;

		if (mExpProjectile == nullptr)
		{
			mExpProjectile = GetWorld()->SpawnActor<AExpProjectile>(GetActorLocation() + GetActorUpVector() * 100.f, GetActorUpVector().Rotation(), SpawnParam);
		}
		mExpProjectile->SetTrailParticle(TEXT("NiagaraSystem'/Game/Ultimate_Magic_Bundle/MagicProjectiles/Niagara/Nature/NS_Nature_Trail.NS_Nature_Trail'"));
		mExpProjectile->SetImpactParticle(TEXT("NiagaraSystem'/Game/Ultimate_Magic_Bundle/MagicProjectiles/Niagara/Nature/NS_Nature_Impact.NS_Nature_Impact'"));
		

		mExpProjectile->SetActorScale3D(FVector(0.4f, 0.4f, 0.4f));

		mExpProjectile->SetSpeed(1.f);
		mExpProjectile->SetHoming(false);

		float ExpScale = 1.0f + (mStageNum * 0.5f);

		mExpProjectile->SetExp(mInfo.Exp * ExpScale);

		/*
		* // 구버전 경험치 획득 코드
		ABasePlayerCharacter* PlayerCharacter = Cast<ABasePlayerCharacter>(DamageCauser);
		if (IsValid(PlayerCharacter)) {

			PlayerCharacter->GetExp(mInfo.Exp);
		}
		else {

			AProjectile* Projectile = Cast<AProjectile>(DamageCauser);
			if (IsValid(Projectile)) {

				AMagicianPlayerCharacter* Magician = Cast<AMagicianPlayerCharacter>(Projectile->mOwner);

				if (IsValid(Magician)) {

					Magician->GetExp(mInfo.Exp);
				}
			}
		}
		*/

	}

	else
	{
		mAnimInst->Hit();
	}

	return Damage;
}

void ABaseMonster::Attack()
{
	FVector	StartLocation = GetActorLocation() +
		GetActorForwardVector() * mAttackLocationDist;
	FVector	EndLocation = StartLocation +
		GetActorForwardVector() * mInfo.AttackDistance;

	FCollisionQueryParams	param(NAME_None, false, this);

	FHitResult	CollisionResult;
	bool CollisionEnable = GetWorld()->SweepSingleByChannel(
		CollisionResult, StartLocation,
		EndLocation, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel10,				// MonsterAttack
		FCollisionShape::MakeSphere(150.f),
		param);

	FColor	DrawColor = CollisionEnable ? FColor::Red : FColor::Green;

	/*
	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
		mInfo.AttackDistance / 2.f,
		100.f,
		FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 0.5f);
	*/

	if (CollisionEnable)
	{
		FActorSpawnParameters	SpawnParam;
		//SpawnParam.Template = mHitActor;
		SpawnParam.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		AParticleNiagara* Particle =
			GetWorld()->SpawnActor<AParticleNiagara>(
				CollisionResult.ImpactPoint,
				CollisionResult.ImpactNormal.Rotation(),
				SpawnParam);

		Particle->SetParticle(TEXT("NiagaraSystem'/Game/Ultimate_Magic_Bundle/MagicProjectiles/Niagara/Shadow/NS_Shadow_Impact_Red.NS_Shadow_Impact_Red'"));
		Particle->SetSound(mNormalAttackSoundPath);
		Particle->SetSoundVolumeScale(0.3f);

		CollisionResult.GetActor()->TakeDamage(
			(float)mInfo.AttackPoint,
			FDamageEvent(), GetController(), this);
		//Particle->SetParticle(TEXT("ParticleSystem'/Game/ParagonYin/FX/Particles/Yin/Abilities/Primary/FX/P_Yin_Primary_Impact.P_Yin_Primary_Impact'"));
		
	}
}

void ABaseMonster::Skill1()
{
}

void ABaseMonster::Skill2()
{
}

void ABaseMonster::Skill3()
{
}

void ABaseMonster::ClearSkill()
{
	/*
	mUseSkillIndex = -1;
	mSkillEnable = false;

	int32	SkillCount = mSkillDataArray.Num();

	for (int32 i = 0; i < SkillCount; ++i)
	{
		mSkillDataArray[i].UseSkill = false;
		mSkillDataArray[i].Duration = 0.f;
	}

	AMonsterAIController* AIController =
		Cast<AMonsterAIController>(GetController());

	AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("SkillEnable"), false);
	*/
}

void ABaseMonster::ClearCurrentSkill()
{
	/*
	if (mUseSkillIndex == -1)
		return;

	mSkillDataArray[mUseSkillIndex].UseSkill = false;
	mSkillDataArray[mUseSkillIndex].Duration = 0.f;

	mUseSkillIndex = -1;
	mSkillEnable = false;

	AMonsterAIController* AIController =
		Cast<AMonsterAIController>(GetController());

	AIController->GetBlackboardComponent()->SetValueAsBool(TEXT("SkillEnable"), false);

	*/

}
