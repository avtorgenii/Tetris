// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TetrisPawn.h"
#include "TetrisGameModeBase.h"
#include "TetrisPlayerState.h"
#include "UI/ScoreWidget.h"
#include "TetrisPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API ATetrisPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay () override;
public:
	// Score management functions
	void UpdateScore();
	UFUNCTION(BlueprintCallable,BlueprintPure)
	float GetScore();

	// End game function
	UFUNCTION()
	void EndGame();


private:
	// Multipliers functions
	void IncreaseScoreMultiplier();
	void DecreaseScoreMultiplier();

	// Game base properties
	UPROPERTY()
	ATetrisGameModeBase* GameMode;
	UPROPERTY()
	ATetrisPawn* PlayerPawn;

	// Score properties
	int Score = 0;
	UPROPERTY(EditDefaultsOnly,Category = Score)
	int PointsForOneRow = 1.f;
	UPROPERTY()
	int CurrentScoreMultiplier = 1;
	UPROPERTY(EditDefaultsOnly, Category = Score)
	int MinScoreMultiplier = 1;
	UPROPERTY(EditDefaultsOnly, Category = Score)
	int MaxScoreMultiplier = 10;

	// Timer properties
	UPROPERTY(EditDefaultsOnly, Category = Score)
	float DecreaseScoreMultiplierTime = 10.f;
	FTimerHandle ScoreMultiplierDecreaseTimer;
	
};
