// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "GameFramework/Actor.h"
#include "../Trigger/MonsterSpawnTrigger.h"
#include "../Monster/BaseMonster.h"

#include "RoomBase.generated.h"

UCLASS()
class KYT_API ARoomBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomBase();


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		USceneComponent* mRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* mMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* mWall_E;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* mWall_W;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* mWall_N;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* mWall_S;


	
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	//	AMonsterSpawnTrigger* mMonsterSpawnTrigger;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UStaticMesh* mGate;



private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		TArray<ABaseMonster*> mMonsterArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool IsMonsterSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool IsRoomClear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		bool bDestoyMonster;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	void SetWallStaticMeshOff(int32 Dir);

	void AddMonster(ABaseMonster* Monster)
	{
		mMonsterArray.Add(Monster);
	}

	void SetMonsterIsSpawned()
	{
		IsMonsterSpawned = true;
	}

	bool IsRoomCleared();


};
