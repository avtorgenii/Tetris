// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "Figure.generated.h"

UCLASS()
class TETRIS_API AFigure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFigure();

	// Functions managing movement
	void MoveForward();
	void MoveBackward();
	void MoveRight();
	void MoveLeft();
	void MoveDown();
	void Rotate();
	void MoveToPlatform();

	// Timeline functions
	UFUNCTION()
	void SizeProgress(float Value);
	UFUNCTION()
	void SizeEnd();

	// Destroy function
	UFUNCTION()
	void DestroyBlock(UStaticMeshComponent* BlockToDestroy);

	// Blocks getter
	UFUNCTION()
	TArray<UStaticMeshComponent*> GetBlocks() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

private:
	// Components
	UPROPERTY(VisibleAnywhere,Category = Components)
	USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* Block1;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* Block2;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* Block3;
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* Block4;

	// Arrays
	UPROPERTY()
	TArray<UStaticMeshComponent*> Blocks;
	UPROPERTY()
	TArray<UStaticMeshComponent*> BlocksToDestroy;

	// Edge values of possible figure's coordinates
	UPROPERTY(EditDefaultsOnly,Category = Coordinates)
	float MaxXLoc = 960;
	UPROPERTY(EditDefaultsOnly,Category = Coordinates)
	float MinXLoc = 40;
	UPROPERTY(EditDefaultsOnly, Category = Coordinates)
	float MaxYLoc = 960;
	UPROPERTY(EditDefaultsOnly, Category = Coordinates)
	float MinYLoc = 40;

	float MoveOffset = 100;

	float EqualityTolerance = 10;

	// Move down properties
	FTimerHandle MoveDownTimer;
	float MoveDownRate = 0.5f;

	// Timeline properties
	FTimeline SizeTimeLine;
	UPROPERTY(EditAnywhere,Category = Timeline)
	UCurveFloat* SizeCurve;
	UPROPERTY(EditAnywhere,Category = Timeline)
	float TimeLineLenght = 0.5f;
};
