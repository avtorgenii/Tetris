// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tetris/UI/MenuWidget.h"
#include "Tetris/UI/PlayAgainWidget.h"
#include "Tetris/UI/ScoreWidget.h"
#include "Tetris/Actors/Overlapper.h"
#include "TetrisGameModeBase.generated.h"


UCLASS()
class TETRIS_API ATetrisGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
protected:
	// Widget variables
	UPROPERTY(EditDefaultsOnly,Category = Widgets)
	TSubclassOf<UMenuWidget> MenuWidgetClass;
	UPROPERTY(BlueprintReadWrite,Category = Widgets)
	UMenuWidget* MenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UPlayAgainWidget> PlayAgainWidgetClass;
	UPROPERTY(BlueprintReadWrite, Category = Widgets)
	UPlayAgainWidget* PlayAgainWidget;

	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;
	UPROPERTY(BlueprintReadWrite, Category = Widgets)
	UScoreWidget* ScoreWidget;

	// Overlapper variables
	UPROPERTY(EditDefaultsOnly,Category = Actors)
	TSubclassOf<AOverlapper> OverlapperClass;
	UPROPERTY(BlueprintReadOnly,Category = Actors)
	AOverlapper* Overlapper;
public:
	// Game management functions
	UFUNCTION(BlueprintCallable,Category = Game)
	void StartGame();
	UFUNCTION(BlueprintCallable,Category = Game)
	void EndGame();

	// Score widget getter
	UFUNCTION(BlueprintCallable, Category = Widgets)
	UScoreWidget* GetScoreWidget() const;
	
};
