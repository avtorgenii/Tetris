// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Kismet/GameplayStatics.h"

void UScoreWidget::UpdateScore_Implementation(int Score, float DecreaseScoreMultiplierTime)
{
}

void UScoreWidget::IncreaseScoreMultiplier_Implementation(int CurrentScoreMultiplier)
{
}

void UScoreWidget::DecreaseScoreMultiplier_Implementation(int CurrentScoreMultiplier)
{
}

void UScoreWidget::NativeConstruct() 
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
}