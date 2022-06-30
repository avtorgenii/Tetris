// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class TETRIS_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category = Score)
	void UpdateScore(int Score,float DecreaseScoreMultiplierTime);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Score)
	void IncreaseScoreMultiplier(int CurrentScoreMultiplier);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Score)
	void DecreaseScoreMultiplier(int CurrentScoreMultiplier);

protected:
	virtual void NativeConstruct() override;
	
};
