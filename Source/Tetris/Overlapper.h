// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Figure.h"
#include "Blueprint/UserWidget.h"
#include "UI/PlayAgainWidget.h"
#include "Overlapper.generated.h"

UCLASS()
class TETRIS_API AOverlapper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOverlapper();

	// Grid management for overlapper
	void CheckHorizontal();											// Searches for horizontal rows that should be cleared
	void CheckVertical();											// Searches for vertical rows that should be cleared
	void DestroyRow(TArray<UStaticMeshComponent*> BlocksToDestroy); // Clears row
	void ClearField();												// Clears whole field

	// Overlap event to detect figures
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Box collision
	UPROPERTY(EditDefaultsOnly,Category = Components)
	UBoxComponent* Collision;

	// Array that holds all blocks that enter overlapper
	UPROPERTY()
	TArray<UStaticMeshComponent*> Blocks;
	// Array that is used to storage blocks that will be removed from "Blocks" array
	UPROPERTY()
	TArray<UStaticMeshComponent*> BlocksToRemoveFromMainArr;

	// Overlapper properties
	int BlocksInRow = 10;
	float ToleranceInEqualityOfCoords = 10;

};
