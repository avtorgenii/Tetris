// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Figure.h"
#include "Blueprint/UserWidget.h"
#include "Tetris/UI/PlayAgainWidget.h"
#include "Overlapper.generated.h"

UCLASS()
class TETRIS_API AOverlapper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOverlapper();

	// Grid management for overlapper
	UFUNCTION(BlueprintCallable,Category = GridManagement)				// Searches for horizontal rows that should be cleared
	void CheckHorizontal();			
	UFUNCTION(BlueprintCallable, Category = GridManagement)				// Searches for vertical rows that should be cleared
	void CheckVertical();				
	UFUNCTION(BlueprintCallable, Category = GridManagement)				// Clears row
	void DestroyRow(TArray<UStaticMeshComponent*> BlocksToDestroy); 
	UFUNCTION(BlueprintCallable, Category = GridManagement)				// Clears whole field
	void ClearField();													

	// Overlap event to detect figures
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	//Box collision
	UPROPERTY(EditDefaultsOnly,Category = Components)
	UBoxComponent* Collision;

	// Array that holds all blocks that enter overlapper
	UPROPERTY(BlueprintReadWrite,Category = Blocks)
	TArray<UStaticMeshComponent*> Blocks;
	// Array that is used to storage blocks that will be removed from "Blocks" array
	UPROPERTY(BlueprintReadWrite, Category = Blocks)
	TArray<UStaticMeshComponent*> BlocksToRemoveFromMainArr;

	// Overlapper properties
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = Blocks)
	int BlocksInRow = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Blocks)
	float ToleranceInEqualityOfCoords = 5;

};
