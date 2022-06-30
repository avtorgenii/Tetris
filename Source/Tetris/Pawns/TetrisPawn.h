// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tetris/Actors/Figure.h"
#include "Tetris/Actors/Overlapper.h"
#include "TetrisPawn.generated.h"

USTRUCT(BlueprintType)
struct FigureClass
{
GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFigure> FigureClass;
};

UCLASS()
class TETRIS_API ATetrisPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATetrisPawn();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Declaring movement functions for figure
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	void Rotate();
	void MoveToPlatform();

	// Managing spawning new figures
	UFUNCTION(BlueprintCallable, Category = Spawn)
	void SpawnFigure();
	void ResetSpawnTimer();

	// Start and End game functions
	UFUNCTION(BlueprintCallable, Category = Game)
	void StartGame();
	UFUNCTION(BlueprintCallable, Category = Game)
	void EndGame();

	// Detach figure from controller
	UFUNCTION(BlueprintCallable, Category = Figure)
	void ClearCurrentFigure();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Current figure 
	UPROPERTY()
	AFigure* CurrentFigure;

	// Figures that pawn can spawn
	UPROPERTY(EditAnywhere,Category = Spawn)
	TArray<FigureClass> FigureClasses;

	// Spawn properties
	FTimerHandle SpawnTimer;
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	float SpawnRate = 5.f;

	// Game state
	bool GameEnded = false;
};
