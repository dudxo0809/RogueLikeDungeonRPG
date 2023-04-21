// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicTrigger.h"

#include "../Character/BasePlayerCharacter.h"

// Sets default values
ACinematicTrigger::ACinematicTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSequencePlayer = nullptr;
	mSequenceActor = nullptr;
}

void ACinematicTrigger::TriggerBegin(const FHitResult& SweepResult, AActor* OtherActor)
{
	if (!IsValid(Cast<ABasePlayerCharacter>(OtherActor)))
		return;

	if (IsValid(mLevelSequence))
	{
		if (!mSequencePlayer)
		{
			mSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
				GetWorld(), mLevelSequence, mSetting, mSequenceActor);
		}

		mSequencePlayer->Play();

		mSequencePlayer->OnFinished.AddDynamic(this, &ACinematicTrigger::SequenceFinish);
	}
}

void ACinematicTrigger::TriggerEnd()
{
}

void ACinematicTrigger::SequenceFinish()
{
	this->Destroy();
}

void ACinematicTrigger::PlaySequence()
{
	mSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		GetWorld(), mLevelSequence, mSetting, mSequenceActor);

	mSequencePlayer->Play();
}

