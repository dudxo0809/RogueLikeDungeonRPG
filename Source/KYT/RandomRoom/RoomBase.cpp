// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomBase.h"

#include "../KYTGameModeBase.h"

// Sets default values
ARoomBase::ARoomBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	//mRoot->bVisualizeComponent = true;

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mRoot);

	//mMonsterSpawnTrigger = CreateDefaultSubobject<AMonsterSpawnTrigger>(TEXT("Spawner"));
	//mMonsterSpawnTrigger->SetActorLocation(FVector(0, 0, 300));
	//mMonsterSpawnTrigger->SetActorScale3D(FVector(55, 55, 10));
	
	


	mWall_E = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_E"));
	mWall_E->SetupAttachment(mMesh);
	mWall_E->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel6, ECollisionResponse::ECR_Block);

	mWall_W = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_W"));
	mWall_W->SetupAttachment(mMesh);
	mWall_W->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel6, ECollisionResponse::ECR_Block);

	mWall_N = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_N"));
	mWall_N->SetupAttachment(mMesh);
	mWall_N->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel6, ECollisionResponse::ECR_Block);

	mWall_S = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall_S"));
	mWall_S->SetupAttachment(mMesh);
	mWall_S->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel6, ECollisionResponse::ECR_Block);



	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/EditorMeshes/AssetViewer/Floor_Mesh.Floor_Mesh'"));
	mMesh->SetStaticMesh(Mesh);
	mMesh->SetRelativeScale3D(FVector(3.9, 3.9, 0.975));
	//mMesh->SetRelativeScale3D(FVector(4, 4, 1));

	mWall_E->SetStaticMesh(Mesh);
	mWall_W->SetStaticMesh(Mesh);
	mWall_S->SetStaticMesh(Mesh);
	mWall_N->SetStaticMesh(Mesh);

	mWall_E->SetRelativeRotation(FRotator(0, 90, 90));
	mWall_W->SetRelativeRotation(FRotator(0, -90, 90));
	mWall_S->SetRelativeRotation(FRotator(0, -180, 90));
	mWall_N->SetRelativeRotation(FRotator(0, 0, 90));

	mWall_E->SetRelativeLocation(FVector(500, 0, 500));
	mWall_W->SetRelativeLocation(FVector(-500, 0, 500));
	mWall_S->SetRelativeLocation(FVector(0, 500, 500));
	mWall_N->SetRelativeLocation(FVector(0, -500, 500));

	mWall_E->SetRelativeScale3D(FVector(1, 0.25, 1));
	mWall_W->SetRelativeScale3D(FVector(1, 0.25, 1));
	mWall_S->SetRelativeScale3D(FVector(1, 0.25, 1));
	mWall_N->SetRelativeScale3D(FVector(1, 0.25, 1));
	
	

	mGate = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/KYT/BluePrint/Room/SM_RoomWall.SM_RoomWall'"));



	IsMonsterSpawned = false;
	bDestoyMonster = false;
}

// Called when the game starts or when spawned
void ARoomBase::BeginPlay()
{
	Super::BeginPlay();
	

	

}

// Called every frame
void ARoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsMonsterSpawned && bDestoyMonster == false)
	{
		if (IsRoomCleared()) 
		{
			for (auto Monster : mMonsterArray)
			{
				Monster->SetExpHoming();
				Monster->DestroyStart(20.f);
			}
			bDestoyMonster = true;

			mMonsterArray.Empty();

			AKYTGameModeBase* MyGameMode = Cast<AKYTGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			MyGameMode->GetMainHUD()->GetMiniMap()->DeleteMonsterArray();
		}
	}

}

void ARoomBase::SetWallStaticMeshOff(int32 Dir)
{
	switch (Dir) {
		
	// East
	case 0:

		mWall_E->SetStaticMesh(mGate);

		mWall_E->SetRelativeScale3D(FVector(0.25, 0.25, 1));
		mWall_E->SetRelativeLocation(FVector(400, -510, 0));
		mWall_E->SetRelativeRotation(FRotator(0, 90, 0));

		break;

		// West
	case 1:

		mWall_W->SetStaticMesh(mGate);

		mWall_W->SetRelativeScale3D(FVector(0.25, 0.25, 1));
		mWall_W->SetRelativeLocation(FVector(-400, 510, 0));
		mWall_W->SetRelativeRotation(FRotator(0, -90, 0));

		break;

		// North
	case 2:

		mWall_N->SetStaticMesh(mGate);

		mWall_N->SetRelativeScale3D(FVector(0.25, 0.25, 1));
		mWall_N->SetRelativeLocation(FVector(-510, -400, 0));
		mWall_N->SetRelativeRotation(FRotator(0, 0, 0));

		break;

		// South
	case 3:

		mWall_S->SetStaticMesh(mGate);

		mWall_S->SetRelativeScale3D(FVector(0.25, 0.25, 1));
		mWall_S->SetRelativeLocation(FVector(510, 400, 0));
		mWall_S->SetRelativeRotation(FRotator(0, -180, 0));


		break;
	}
}

bool ARoomBase::IsRoomCleared()
{
	bool IsClear = true;

	for (auto Monster : mMonsterArray) 
	{
		if (!Monster->IsDead())
			IsClear = false;
	}

	return IsClear;
}

