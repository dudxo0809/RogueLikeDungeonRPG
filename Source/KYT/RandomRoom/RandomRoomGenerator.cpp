// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomRoomGenerator.h"

#include "RoomData.h"
#include "FloorData.h"

CRandomRoomGenerator* CRandomRoomGenerator::mInst = nullptr;

CRandomRoomGenerator::CRandomRoomGenerator()
{
	mFloorData = nullptr;

	mRoomNum = (int32)EFloorInfo::RoomNum;
	mRoomX = (int32)EFloorInfo::RoomX;
	mRoomY = (int32)EFloorInfo::RoomY;

}

CRandomRoomGenerator::~CRandomRoomGenerator()
{
	delete mFloorData;
}

CFloorData* CRandomRoomGenerator::MakeFloorData(int32 N, int32 M)
{
	mFloorData = new CFloorData;

	ClearArr();


	CRoomData* none = new CRoomData;
	none->SetRoomType(ERoomType::None);

	CRoomData* Init = new CRoomData;
	Init->SetRoomType(ERoomType::Init);

	for (int32 i = 0; i < N; i++) {
		for (int32 j = 0; j < M; j++) {
			mFloorData->SetRoomData(i, j, none);
		}
	}
	DFS(0, 0, 0);

	mFloorData->SetRoomData(0, 0, Init);
	//mFloorData->SetRoomData(0, 1, room2);

	bool CheckBossRoom = false;
	for (int32 i = N-1; i >=0; i--) {

		if (CheckBossRoom == true)
			break;

		for (int32 j = M-1; j >= 0; j--) {
			
			if (CheckBossRoom == true)
				break;

			if (arr[i][j] == 1) {

				if (mFloorData->GetRoomData(i, j)->GetRoomType() == ERoomType::Normal) {

					CRoomData* Boss = new CRoomData;
					Boss->SetRoomType(ERoomType::Boss);

					mFloorData->SetRoomData(i, j, Boss);
					CheckBossRoom = true;

					break;
				}

			}
		}
	}


	for (int32 i = 0; i < N; i++) {
		for (int32 j = 0; j < M; j++) {
			if (arr[i][j] == 1) {

				for (int32 dir = 0; dir < 4; dir++) {
					
					int32 ny = i + dy[dir];
					int32 nx = j + dx[dir];

					if (ny >= 0 && ny < mRoomY && nx >= 0 && nx < mRoomX) {
						if (arr[ny][nx] == 1) {

							mFloorData->GetRoomData(i, j)->SetIsWall(dir, false);

						}
					}
				}

			}
		}
	}


	return mFloorData;
}

int32 CRandomRoomGenerator::DFS(int32 y, int32 x, int32 cnt)
{
	if (cnt == mRoomNum) {
		return cnt;
	}

	arr[y][x] = 1;

	CRoomData* Normal = new CRoomData;
	Normal->SetRoomType(ERoomType::Normal);

	mFloorData->SetRoomData(y, x, Normal);

	bool dir_check[4] = { false,false,false,false };
	int32 dir_cnt = 0;
	//FMath::RandRange(0, 3);

	
	
	for (int32 i = 0; i < 4; i++) {
	

		int32 dir;

		while (dir_cnt < 4) {
			int32 rand = FMath::RandRange(0, 3);
			
			if (dir_check[rand] == false) {

				dir_check[rand] = true;
				dir_cnt++;
				dir = rand;
				break;
			}
			else
				continue;
		
		}

		int32 ny = y + dy[dir];
		int32 nx = x + dx[dir];

		if (ny >= 0 && ny < mRoomY && nx >= 0 && nx < mRoomX) {

			if (arr[ny][nx] != 1) {
				cnt = DFS(ny, nx, cnt + 1);
				if (cnt == mRoomNum)
					break;
			}
		}
	}

	return cnt;
}

void CRandomRoomGenerator::ClearArr()
{
	for (int32 i = 0; i < 20; i++)
		for (int32 j = 0; j < 20; j++)
			arr[i][j] = 0;
}
