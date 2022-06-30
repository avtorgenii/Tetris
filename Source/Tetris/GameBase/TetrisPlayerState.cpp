// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisPlayerState.h"
#include "Kismet/GameplayStatics.h"

void ATetrisPlayerState::BeginPlay()
{
	GameMode = Cast<ATetrisGameModeBase>(GetWorld()->GetAuthGameMode());
	PlayerPawn = Cast<ATetrisPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATetrisPlayerState::UpdateScore() 
{
	Score += CurrentScoreMultiplier * PointsForOneRow;

	if (GameMode->GetScoreWidget())
		GameMode->GetScoreWidget()->UpdateScore(Score,DecreaseScoreMultiplierTime);

	IncreaseScoreMultiplier();

	// Set timer for decrease multiplier function
	GetWorldTimerManager().SetTimer(ScoreMultiplierDecreaseTimer, this, &ATetrisPlayerState::DecreaseScoreMultiplier, DecreaseScoreMultiplierTime, true, DecreaseScoreMultiplierTime);
	return;
	
}

float ATetrisPlayerState::GetScore()
{
	return Score;
}

void ATetrisPlayerState::IncreaseScoreMultiplier() 
{
	CurrentScoreMultiplier = FMath::Min(CurrentScoreMultiplier + 1,MaxScoreMultiplier);
	if (GameMode->GetScoreWidget())
		GameMode->GetScoreWidget()->IncreaseScoreMultiplier(CurrentScoreMultiplier);
	return;
}

void ATetrisPlayerState::DecreaseScoreMultiplier()
{
	CurrentScoreMultiplier = FMath::Max(CurrentScoreMultiplier - 1, MinScoreMultiplier);
	if (GameMode->GetScoreWidget())
		GameMode->GetScoreWidget()->DecreaseScoreMultiplier(CurrentScoreMultiplier);
	return;
}

void ATetrisPlayerState::EndGame() 
{
	// Reset properties
	CurrentScoreMultiplier = MinScoreMultiplier;
	Score = 0;
	return;
}