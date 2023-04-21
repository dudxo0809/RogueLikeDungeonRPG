// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/Image.h>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"


#include "Minimap.generated.h"

/**
 * 
 */

class ARandomRoomGameMode;
class ABasePlayerCharacter;

class ABaseMonster;

UCLASS()
class KYT_API UMinimap : public UUserWidget
{
	GENERATED_BODY()
	

private:

	UImage* m_MiniMap;
	UImage* m_BossRoom;


	UImage* m_Pos_Start_Img;
	UImage* m_Pos_End_Img;


	UCanvasPanel* m_CanvasPanel;

	UImage* m_Monster_Img_Base;
	TArray<UImage*> m_Monster_Img;


private:

	FVector2D mPosStart;
	FVector2D mPosEnd;


	ARandomRoomGameMode* mGameMode;
	ABasePlayerCharacter* mPlayer;


private:

	TArray<ABaseMonster*> mMonsterArray;

public:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& _geo, float _DeltaTime) override;


public:

	void CalculateBossPosition();
	void CalculateMonsterPosition();

public:

	void SetMonsterArray(TArray<ABaseMonster*> Array)
	{
		mMonsterArray = Array;

		for (int32 i = 0; i < Array.Num(); i++) {

			UImage* Monster_Img = DuplicateObject<UImage>(m_Monster_Img_Base, this);

			// Color :: Red
			Monster_Img->SetColorAndOpacity(FLinearColor(FColor::Red));
			m_Monster_Img.Add(Monster_Img);


			m_CanvasPanel->AddChildToCanvas(Monster_Img);
		}
		
	}

	void DeleteMonsterArray()
	{
		mMonsterArray.Empty();
		m_Monster_Img.Empty();
	}
};
