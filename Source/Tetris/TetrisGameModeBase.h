// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/MenuWidget.h"
#include "UI/PlayAgainWidget.h"
#include "UI/ScoreWidget.h"
#include "Overlapper.h"
#include "TetrisGameModeBase.generated.h"


UCLASS()
class TETRIS_API ATetrisGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
private:
	// Widget variables
	UPROPERTY(EditDefaultsOnly,Category = Widgets)
	TSubclassOf<UMenuWidget> MenuWidgetClass;
	UPROPERTY()
	UMenuWidget* MenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UPlayAgainWidget> PlayAgainWidgetClass;
	UPROPERTY()
	UPlayAgainWidget* PlayAgainWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;
	UPROPERTY()
	UScoreWidget* ScoreWidget;

	// Overlapper variables
	UPROPERTY(EditDefaultsOnly,Category = Actors)
	TSubclassOf<AOverlapper> OverlapperClass;
	UPROPERTY()
	AOverlapper* Overlapper;
public:
	// Game management functions
	UFUNCTION(BlueprintCallable)
	void StartGame();
	UFUNCTION(BlueprintCallable)
	void EndGame();

	// Score widget getter
	UScoreWidget* GetScoreWidget() const;
	
};
