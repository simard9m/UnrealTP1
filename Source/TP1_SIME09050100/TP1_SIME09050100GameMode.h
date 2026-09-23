// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TP1_SIME09050100GameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ATP1_SIME09050100GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ATP1_SIME09050100GameMode();
	
	//Variable pour UI
	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int32 TotalBonuses = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int32 CaughtBonuses = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Score")
	int32 MissedBonuses = 0;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void BonusSpawned();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void BonusCaught();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void BonusMissed();

	UFUNCTION(BlueprintPure, Category = "Score")
	float GetCatchPercentage() const;
};



