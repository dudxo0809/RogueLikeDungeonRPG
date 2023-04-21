// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
 * 
 */


class CRoomData;

UENUM()
enum class EFloorInfo : uint8 {

	RoomNum = 22,
	
	RoomY = 10,
	RoomX = 10


};


class KYT_API CFloorData
{
public:
	CFloorData();
	~CFloorData();


private:

	int32 mRoomNum = 15;
	CRoomData* mRoomData[10][10];


public:

	CRoomData* GetRoomData(int y, int x) {

		return mRoomData[y][x];
	}
	void SetRoomData(int y, int x, CRoomData* Data) {

		mRoomData[y][x] = Data;
	}

};
