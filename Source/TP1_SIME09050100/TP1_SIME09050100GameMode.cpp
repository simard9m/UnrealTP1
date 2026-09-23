// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP1_SIME09050100GameMode.h"

ATP1_SIME09050100GameMode::ATP1_SIME09050100GameMode()
{
	// stub
}

//mes methodes pour ui
void ATP1_SIME09050100GameMode::BonusSpawned()
{
	TotalBonuses++;
}

void ATP1_SIME09050100GameMode::BonusCaught()
{
	CaughtBonuses++;
}

void ATP1_SIME09050100GameMode::BonusMissed()
{
	MissedBonuses++;
}

float ATP1_SIME09050100GameMode::GetCatchPercentage() const
{
	int32 FinishedBonuses = CaughtBonuses + MissedBonuses;

	if (FinishedBonuses == 0)
	{
		return 0.0f;
	}

	return ((float)CaughtBonuses / (float)FinishedBonuses) * 100.0f;
}