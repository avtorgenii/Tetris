// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisPawn.h"

// Sets default values
ATetrisPawn::ATetrisPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATetrisPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ATetrisPawn::ResetSpawnTimer()
{
	// Set timer for spawn function if game is not ended
	if(!GameEnded)
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ATetrisPawn::SpawnFigure, SpawnRate, true, 0.5f);
	return;
}

void ATetrisPawn::StartGame() 
{
	// Resetting game state variable and initializing spawn timer
	GameEnded = false;
	ResetSpawnTimer();
	return;
}

void ATetrisPawn::EndGame() 
{ 
	// Resetting game state variable
	GameEnded = true;

	// Destroying current figure that is still in movement
	if (CurrentFigure)
	{
		CurrentFigure->Destroy();
	}

	// Clearing spawn timer
	GetWorldTimerManager().ClearTimer(SpawnTimer);
	return;
}

// Called to bind functionality to input
void ATetrisPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Setting up movement functions for figure
	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &ATetrisPawn::MoveForward);
	PlayerInputComponent->BindAction("MoveBackward", IE_Pressed, this, &ATetrisPawn::MoveBackward);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ATetrisPawn::MoveRight);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ATetrisPawn::MoveLeft);
	PlayerInputComponent->BindAction("Rotate", IE_Pressed, this, &ATetrisPawn::Rotate);
	PlayerInputComponent->BindAction("MoveToPlatform", IE_Pressed, this, &ATetrisPawn::MoveToPlatform);

}

void ATetrisPawn::MoveForward()
{
	if (CurrentFigure)
		CurrentFigure->MoveForward();
	return;
}

void ATetrisPawn::MoveBackward()
{
	if (CurrentFigure)
		CurrentFigure->MoveBackward();
	return;
}

void ATetrisPawn::MoveRight()
{
	if (CurrentFigure)
		CurrentFigure->MoveRight();
	return;
}

void ATetrisPawn::MoveLeft()
{
	if (CurrentFigure)
		CurrentFigure->MoveLeft();
	return;
}

void ATetrisPawn::Rotate() 
{
	if (CurrentFigure)
		CurrentFigure->Rotate();
	return;
}

void ATetrisPawn::MoveToPlatform() 
{
	if (CurrentFigure)
		CurrentFigure->MoveToPlatform();
	return;
}

void ATetrisPawn::SpawnFigure()
{
	// Setting up transform parameters for figure
	FVector Location = GetActorLocation();
	Location.Z -= 200;
	FRotator Rotation(0);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Picking next figure class from array 
	TSubclassOf<AFigure> FigureToSpawn = FigureClasses[rand() % FigureClasses.Num()].FigureClass;

	// Spawning figure
	if (FigureToSpawn)
		CurrentFigure = GetWorld()->SpawnActor<AFigure>(FigureToSpawn, Location, Rotation, SpawnParams);
	return;
}

void ATetrisPawn::ClearCurrentFigure() 
{
	CurrentFigure = NULL;
	return;
}