// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
 * 
 */

UENUM()
enum class ERoomType {

	None,
	Init,
	Normal,
	Boss,
	Shop
};


class KYT_API CRoomData
{
public:
	CRoomData();
	~CRoomData();


private:

	ERoomType mRoomType;

	// 0  1  2  3
	// E, W, N, S
	bool mWall[4];


public:

	void SetRoomType(ERoomType Type) {
		mRoomType = Type;
	}
	ERoomType GetRoomType() {
		return mRoomType;
	}

	// 0 : East, 1 : West, 2 : North, 3 : South
	bool GetIsWall(int32 Dir) {
		return mWall[Dir];
	}

	// 0 : East, 1 : West, 2 : North, 3 : South
	void SetIsWall(int32 Dir, bool IsWall) {
		mWall[Dir] = IsWall;
	}


};
