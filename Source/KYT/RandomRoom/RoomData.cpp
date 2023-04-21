// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomData.h"

CRoomData::CRoomData()
{
	mRoomType = ERoomType::None;

	for (int32 i = 0; i < 4; i++)
		mWall[i] = true;

}

CRoomData::~CRoomData()
{
}
