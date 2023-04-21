// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
 * 
 */


class CFloorData;


class KYT_API CRandomRoomGenerator
{
private:
	CRandomRoomGenerator();
	~CRandomRoomGenerator();

private:
	static CRandomRoomGenerator* mInst;

	CFloorData* mFloorData;


	int32 mRoomNum;
	int32 mRoomX;
	int32 mRoomY;


public:

	static CRandomRoomGenerator* GetInst() {
		if (!mInst)
			mInst = new CRandomRoomGenerator;

		return mInst;
	}

	CFloorData* MakeFloorData(int32 N, int32 M);


private:

	int32 arr[20][20];
	int32 dx[4] = { 1,-1,0,0 };
	int32 dy[4] = { 0,0,-1,1 };

	int32 DFS(int32 y, int32 x, int32 cnt);
	void ClearArr();

};
