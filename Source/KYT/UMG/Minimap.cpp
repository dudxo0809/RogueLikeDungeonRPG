// Fill out your copyright notice in the Description page of Project Settings.


#include "Minimap.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "../Character/BasePlayerCharacter.h"
#include "../RandomRoom/RandomRoomGameMode.h"



void UMinimap::NativeConstruct()
{
	Super::NativeConstruct();


	// Load Widget
	m_MiniMap = Cast<UImage>(GetWidgetFromName(FName(TEXT("UI_Minimap"))));
	m_BossRoom = Cast<UImage>(GetWidgetFromName(FName(TEXT("Boss"))));
	
	
	m_Pos_Start_Img = Cast<UImage>(GetWidgetFromName(FName(TEXT("Pos_Start"))));
	m_Pos_End_Img = Cast<UImage>(GetWidgetFromName(FName(TEXT("Pos_End"))));


	m_CanvasPanel = Cast<UCanvasPanel>(GetWidgetFromName(FName(TEXT("Canvas"))));

	m_Monster_Img_Base = Cast<UImage>(GetWidgetFromName(FName(TEXT("Monster"))));

	m_Monster_Img_Base->SetColorAndOpacity(FLinearColor(0, 0, 0, 0));


	


	mGameMode = Cast<ARandomRoomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(mGameMode))
	{
	}
	

	mPlayer = Cast<ABasePlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(mPlayer)) {

		m_MiniMap->Brush.SetResourceObject(mPlayer->GetMinimapMaterial());
	}
	
	if (UCanvasPanelSlot* MySlot = Cast<UCanvasPanelSlot>(m_Pos_Start_Img->Slot))
	{
		mPosStart = MySlot->GetPosition();
	}

	if (UCanvasPanelSlot* MySlot = Cast<UCanvasPanelSlot>(m_Pos_End_Img->Slot))
	{
		mPosEnd = MySlot->GetPosition();
	}

}

void UMinimap::NativeTick(const FGeometry& _geo, float _DeltaTime)
{
	Super::NativeTick(_geo, _DeltaTime);

	// Set BossMonster Position On MiniMap
	CalculateBossPosition();

	// Set Monster Position On MiniMap
	CalculateMonsterPosition();
	
}

void UMinimap::CalculateBossPosition()
{
	if (!IsValid(mPlayer) || mPlayer == nullptr)
		return;

	FVector2D NewBossPosition;

	FVector2D BossPosition = mGameMode->GetBossRoomPosition();
	FVector2D PlayerPosition = FVector2D(mPlayer->GetActorLocation().X, mPlayer->GetActorLocation().Y);

	// Norm Vec
	FVector2D PlayerDir = FVector2D(mPlayer->GetActorForwardVector().X, mPlayer->GetActorForwardVector().Y);
	PlayerDir = PlayerDir / PlayerDir.Size();

	// Norm Vec
	FVector2D BossDir = BossPosition - PlayerPosition;
	BossDir = BossDir / BossDir.Size();

	float UILengthX = (mPosEnd - mPosStart).X;
	float UIHalfLength = ((float)UILengthX / 2);

	// Dot Product
	float DotProduct = FVector2D::DotProduct(PlayerDir, BossDir);

	// Cross Product
	float CrossProduct = FVector2D::CrossProduct(PlayerDir, BossDir);

	//
	float Radian = FMath::Acos(DotProduct);
	Radian *= (CrossProduct < 0 ? -1 : 1);

	float Degree = FMath::RadiansToDegrees(Radian) - 90.f;
	Radian = FMath::DegreesToRadians(Degree);


	float NewX = FMath::Cos(Radian) * UIHalfLength * 1.2f;
	float NewY = FMath::Sin(Radian) * UIHalfLength * 1.2f;

	FVector2D CenterPos = (mPosStart + mPosEnd) / 2;

	NewBossPosition.X = CenterPos.X + NewX;
	NewBossPosition.Y = CenterPos.Y + NewY;


	// Set Boss Icon Position
	if (UCanvasPanelSlot* MySlot = Cast<UCanvasPanelSlot>(m_BossRoom->Slot))
	{
		MySlot->SetPosition(NewBossPosition);
	}
}

void UMinimap::CalculateMonsterPosition()
{
	if (!IsValid(mPlayer) || mPlayer == nullptr)
		return;


	for (int32 i = 0; i < mMonsterArray.Num(); i++)
	{
		if (mMonsterArray[i]->IsDead()) {

			m_Monster_Img[i]->SetColorAndOpacity(FLinearColor(0, 0, 0, 0));

			continue;
		}

		FVector2D NewMonsterPosition;
		
		FVector2D MonsterPosition = FVector2D(mMonsterArray[i]->GetActorLocation().X, mMonsterArray[i]->GetActorLocation().Y);
		FVector2D PlayerPosition = FVector2D(mPlayer->GetActorLocation().X, mPlayer->GetActorLocation().Y);

		
		// Norm Vec
		FVector2D PlayerDir = FVector2D(mPlayer->GetActorForwardVector().X, mPlayer->GetActorForwardVector().Y);
		PlayerDir = PlayerDir / PlayerDir.Size();

		// Norm Vec
		FVector2D MonsterDir = MonsterPosition - PlayerPosition;
		MonsterDir = MonsterDir / MonsterDir.Size();

		float UILengthX = (mPosEnd - mPosStart).X;
		float UIHalfLength = ((float)UILengthX / 2);

		// Dot Product
		float DotProduct = FVector2D::DotProduct(PlayerDir, MonsterDir);

		// Cross Product
		float CrossProduct = FVector2D::CrossProduct(PlayerDir, MonsterDir);

		//
		float Radian = FMath::Acos(DotProduct);
		Radian *= (CrossProduct < 0 ? -1 : 1);

		float Degree = FMath::RadiansToDegrees(Radian) - 90.f;
		Radian = FMath::DegreesToRadians(Degree);


		// Distance
		float Dist = FVector2D::Distance(MonsterPosition, PlayerPosition);

		// Real : Minimap = 700 : UIHalfLength
		float Ratio = Dist / 5000.f;


		float NewX = FMath::Cos(Radian) * UIHalfLength * 1.4f * Ratio;
		float NewY = FMath::Sin(Radian) * UIHalfLength * 1.4f * Ratio;

		FVector2D CenterPos = (mPosStart + mPosEnd) / 2;



		NewMonsterPosition.X = CenterPos.X + NewX;
		NewMonsterPosition.Y = CenterPos.Y + NewY;


		// Set Monster Icon Position
		if (UCanvasPanelSlot* MySlot = Cast<UCanvasPanelSlot>(m_Monster_Img[i]->Slot))
		{
			MySlot->SetPosition(NewMonsterPosition);
			MySlot->SetSize(FVector2D(20.f, 20.f));
		}


	}
}
