// Fill out your copyright notice in the Description page of Project Settings.


#include "Figure.h"
#include "Tetris/Pawns/TetrisPawn.h"
#include "Tetris/GameBase/TetrisGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFigure::AFigure()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Block1 = CreateDefaultSubobject<UStaticMeshComponent>("Block1");
	Block2 = CreateDefaultSubobject<UStaticMeshComponent>("Block2");
	Block3 = CreateDefaultSubobject<UStaticMeshComponent>("Block3");
	Block4 = CreateDefaultSubobject<UStaticMeshComponent>("Block4");

	Blocks.Append({ Block1,Block2,Block3,Block4 });

	for (auto Block : Blocks) 
	{
		Block->SetCollisionObjectType(ECC_WorldDynamic);
		Block->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
		Block->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
		Block->SetupAttachment(Root);
	}
	
}

// Called when the game starts or when spawned
void AFigure::BeginPlay()
{
	Super::BeginPlay();

	// Set timer for function that moves figure down
	GetWorldTimerManager().SetTimer(MoveDownTimer, this, &AFigure::MoveDown, MoveDownRate, true, 0);
	
	// Setting up timeline that will play when block is being destroyed
	if (SizeCurve) 
	{
		FOnTimelineFloat TimeLineProgress;
		FOnTimelineEvent TimeLineEnd;
		
		TimeLineProgress.BindUFunction(this, FName("SizeProgress"));
		TimeLineEnd.BindUFunction(this,FName("SizeEnd"));
		SizeTimeLine.SetTimelineFinishedFunc(TimeLineEnd);
		SizeTimeLine.AddInterpFloat(SizeCurve, TimeLineProgress);
		SizeTimeLine.SetTimelineLength(TimeLineLenght);
	}
}

void AFigure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SizeTimeLine.TickTimeline(DeltaTime);
}

void AFigure::DestroyBlock(UStaticMeshComponent* BlockToDestroy) 
{
	if (BlockToDestroy)
	{
		// Start timeline only once
		if (BlocksToDestroy.Num() == 0)
		{
			SizeTimeLine.PlayFromStart();
		}

		BlocksToDestroy.Add(BlockToDestroy);
		BlockToDestroy->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Blocks.Remove(BlockToDestroy);
	}
}

void AFigure::MoveForward() 
{
	for (auto Block : Blocks)
	{
		if (Block->GetComponentLocation().X + MoveOffset > MaxXLoc) 
		{
			return;
		}
	}

	AddActorWorldOffset(FVector(MoveOffset,0,0));
	return;
}

void AFigure::MoveBackward()
{
	for (auto Block : Blocks)
	{
		if (Block->GetComponentLocation().X - MoveOffset < MinXLoc)
		{
			return;
		}
	}

	AddActorWorldOffset(FVector(-MoveOffset, 0, 0));
	return;
}

void AFigure::MoveRight()
{
	for (auto Block : Blocks)
	{
		if (Block->GetComponentLocation().Y + MoveOffset > MaxYLoc)
		{
			return;
		}
	}

	AddActorWorldOffset(FVector(0, MoveOffset, 0));
	return;
}

void AFigure::MoveLeft()
{
	for (auto Block : Blocks)
	{
		if (Block->GetComponentLocation().Y - MoveOffset < MinYLoc)
		{
			return;
		}
	}

	AddActorWorldOffset(FVector(0, -MoveOffset, 0));
	return;
}

void AFigure::MoveDown()
{
	for (auto Block : Blocks)
	{
		if (Block->GetComponentLocation().Z - MoveOffset < 0)
		{
			GetWorldTimerManager().ClearTimer(MoveDownTimer);
			return;
		}
	}

	AddActorWorldOffset(FVector(0, 0, -MoveOffset));
	return;
}

void AFigure::Rotate() 
{
	AddActorLocalRotation(FRotator(0, 90, 0));

	FVector DeltaLoc(0);

	// If after rotation any block goes beyond platform - adjust whole figure

	for (auto Block : Blocks)
	{
		DeltaLoc = FVector(0);

		if (Block->GetComponentLocation().X > MaxXLoc)
		{
			DeltaLoc += FVector(-(Block->GetComponentLocation().X - MaxXLoc + EqualityTolerance),0,0);
		}
		else if (Block->GetComponentLocation().X < MinXLoc)
		{
			DeltaLoc += FVector(-(Block->GetComponentLocation().X - MinXLoc - EqualityTolerance), 0, 0);
		}
		AddActorWorldOffset(DeltaLoc);
	}
	
	for (auto Block : Blocks)
	{
		DeltaLoc = FVector(0);

		if (Block->GetComponentLocation().Y > MaxYLoc)
		{
			DeltaLoc += FVector(0, -(Block->GetComponentLocation().Y - MaxYLoc + EqualityTolerance), 0);
		}
		else if (Block->GetComponentLocation().Y < MinYLoc)
		{
			DeltaLoc += FVector(0, -(Block->GetComponentLocation().Y - MinYLoc - EqualityTolerance), 0);
		}
		AddActorWorldOffset(DeltaLoc);
	}
	return;
}

TArray<UStaticMeshComponent*> AFigure::GetBlocks() const 
{
	return Blocks;
}

void AFigure::MoveToPlatform() 
{
	AddActorWorldOffset(FVector(0, 0, -GetActorLocation().Z));

	GetWorldTimerManager().ClearTimer(MoveDownTimer);

	Cast<ATetrisPawn>(UGameplayStatics::GetPlayerPawn(this, 0))->ResetSpawnTimer();

	return;
}

void AFigure::SizeProgress(float Value)
{
	for (auto Block : BlocksToDestroy) 
	{
		if(Block)
		Block->SetWorldScale3D(FVector(Value));
	}
}

void AFigure::SizeEnd()
{
	for (auto Block : BlocksToDestroy) 
	{
		if (Block)
		{
			// Destroy block and remove it from main array when timeline ends
			Blocks.Remove(Block);
			Block->DestroyComponent();
		}
	}

	BlocksToDestroy.Empty();

	// Destroy whole figure actor when all blocks are destroyed
	if (Blocks.Num() == 0) 
	{
		Destroy();
	}
}

