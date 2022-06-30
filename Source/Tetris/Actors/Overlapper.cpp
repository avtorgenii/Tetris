// Fill out your copyright notice in the Description page of Project Settings.


#include "Overlapper.h"
#include "Figure.h"
#include "Tetris/Pawns/TetrisPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Tetris/GameBase/TetrisPlayerState.h"
#include "Tetris/GameBase/TetrisGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AOverlapper::AOverlapper()
{
	// Setting up collision component
	Collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	SetRootComponent(Collision);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionObjectType(ECC_WorldStatic);
	Collision->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
}

void AOverlapper::CheckHorizontal()
{
	TArray<UStaticMeshComponent*> BlocksToDestroy; // Array that will hold blocks that will be destroyed

	float CurrentY = 50; // Start y coordinate
	float YStep = 100; // Distance between rows

	for (int i = 0; i < BlocksInRow; i++) 
	{
		for (auto Block : Blocks) 
		{
			if (Block)
			{
				float BlockY = Block->GetComponentLocation().Y;

				// If blocks Y coordinate is equal to current rows Y coordinate,add block to destroy array
				if (FMath::IsNearlyEqual(BlockY, CurrentY, ToleranceInEqualityOfCoords))
				{
					BlocksToDestroy.Add(Block);
				}
			}
		}

		// If array gathered enough blocks - destroy row
		if (BlocksToDestroy.Num() == BlocksInRow)
		{
			DestroyRow(BlocksToDestroy);
		}

		// Updating properties
		BlocksToDestroy.Empty();
		CurrentY += YStep;

		// Remove destroyed blocks from main array
		for (auto BlockToRemove : BlocksToRemoveFromMainArr)
		{
			Blocks.Remove(BlockToRemove);
		}
		BlocksToRemoveFromMainArr.Empty();
	}

	return;

}

void AOverlapper::CheckVertical()
{
	TArray<UStaticMeshComponent*> BlocksToDestroy; // Array that will hold blocks that will be destroyed
	 
	float CurrentX = 50; // Start x coordinate
	float XStep = 100; // Distance between rows

	for (int i = 0; i < BlocksInRow; i++)
	{
		for (auto Block : Blocks)
		{
			if (Block)
			{
				float BlockX = Block->GetComponentLocation().X;

				// If blocks Y coordinate is equal to current rows Y coordinate,add block to destroy array
				if (FMath::IsNearlyEqual(BlockX, CurrentX, ToleranceInEqualityOfCoords))
				{
					BlocksToDestroy.Add(Block);
				}
			}
		}

		// If array gathered enough blocks - destroy row
		if (BlocksToDestroy.Num() == BlocksInRow)
		{
			DestroyRow(BlocksToDestroy);
		}

		// Updating properties
		BlocksToDestroy.Empty();
		CurrentX += XStep;

		// Remove destroyed blocks from main array
		for (auto BlockToRemove : BlocksToRemoveFromMainArr) 
		{
			Blocks.Remove(BlockToRemove);
		}
		BlocksToRemoveFromMainArr.Empty();
	}

	return;
	
}

void AOverlapper::DestroyRow(TArray<UStaticMeshComponent*> BlocksToDestroy)
{
	for (auto Block : BlocksToDestroy) 
	{
		if (Block)
		{
			BlocksToRemoveFromMainArr.Add(Block);
			
			// Get block's parent figure and destroy block from it
			Cast<AFigure>(Block->GetAttachmentRootActor())->DestroyBlock(Block);
		}
	}

	for (auto BlockToRemove : BlocksToRemoveFromMainArr)
	{
		Blocks.Remove(BlockToRemove);
	}

	// Update score
	ATetrisPlayerState* PlayerState = Cast<ATetrisPlayerState>(UGameplayStatics::GetPlayerPawn(this, 0)->GetPlayerState());
	if (PlayerState)
		PlayerState->UpdateScore();

	return;
}

void AOverlapper::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AFigure* Figure = Cast<AFigure>(OtherActor);

	if (Figure)
	{
		for (auto NewBlock : Figure->GetBlocks()) // Check if new figure goes in other figure borders
		{
			FVector OtherLoc = NewBlock->GetComponentLocation();

			for (auto Block : Blocks) 
			{
				FVector Loc = Block->GetComponentLocation();

				if (FMath::IsNearlyEqual(OtherLoc.X, Loc.X, ToleranceInEqualityOfCoords) && FMath::IsNearlyEqual(OtherLoc.Y, Loc.Y, ToleranceInEqualityOfCoords) && NewBlock != Block)
				{
					AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

					if (GameMode)
					{
						Cast<ATetrisGameModeBase>(GameMode)->EndGame();
			
						return;
					}
				}
			}
		}

		for (auto Block : Figure->GetBlocks()) // Add each block from figure to Blocks array
		{
			Blocks.AddUnique(Block);
		}
	
		// Inspect grid for fulfilled rows
		CheckVertical();
		CheckHorizontal();

		// Detach figure from pawn control
		(Cast<ATetrisPawn>(UGameplayStatics::GetPlayerPawn(this, 0)))->ClearCurrentFigure();
	}

}

// Called when the game starts or when spawned
void AOverlapper::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOverlapper::ClearField() 
{
	// Get all figures
	TArray<AActor*> Figures;
	UGameplayStatics::GetAllActorsOfClass(this, AFigure::StaticClass(), Figures);

	// Destroy each block in every figure
	for (auto Figure : Figures)
	{
		if (Figure)
		{
			auto BlocksToDestroy = Cast<AFigure>(Figure)->GetBlocks();
			for (auto Block : BlocksToDestroy)
			{
				if (Block)
					Cast<AFigure>(Figure)->DestroyBlock(Block);
			}
		}
	}

	// Reset array info
	BlocksToRemoveFromMainArr.Empty();
	Blocks.Empty();

	return;
}