// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseTrigger.h"
#include "CinematicTrigger.generated.h"

/**
 * 
 */
UCLASS()
class KYT_API ACinematicTrigger : public ABaseTrigger
{
	GENERATED_BODY()

public:
	ACinematicTrigger();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	ULevelSequence* mLevelSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FMovieSceneSequencePlaybackSettings	mSetting;

	ULevelSequencePlayer* mSequencePlayer;
	ALevelSequenceActor* mSequenceActor;

public:
	virtual void TriggerBegin(const FHitResult& SweepResult, AActor* OtherActor);
	virtual void TriggerEnd();


public:
	void SetLevelSequence(ULevelSequence* LevelSequence) { mLevelSequence = LevelSequence; }
	void PlaySequence();

public:
	UFUNCTION()
		void SequenceFinish();
};
