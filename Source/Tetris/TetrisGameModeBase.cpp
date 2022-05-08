// Copyright Epic Games, Inc. All Rights Reserved.


#include "TetrisGameModeBase.h"
#include "TetrisPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TetrisPlayerState.h"

void ATetrisGameModeBase::BeginPlay() 
{
	MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);
	if (MenuWidget)
		MenuWidget->AddToViewport(0);

	return;
}

void ATetrisGameModeBase::StartGame() 
{
	ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
	if (ScoreWidget)
		ScoreWidget->AddToViewport(0);
	
	// Spawn overlapper
	if (Overlapper == nullptr)
	{
		FVector Location(500, 500, 0);
		FRotator Rotation(0);
		FVector Scale(16, 16, 0.46875);
		FTransform Transform(Rotation, Location, Scale);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Overlapper = GetWorld()->SpawnActor<AOverlapper>(OverlapperClass, Transform, SpawnParams);
	}

	// Start spawning figures in player pawn
	ATetrisPawn* PlayerPawn = Cast<ATetrisPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerPawn)
		PlayerPawn->StartGame();

	return;
}

void ATetrisGameModeBase::EndGame()
{
	// Manage widgets
	PlayAgainWidget = CreateWidget<UPlayAgainWidget>(GetWorld(), PlayAgainWidgetClass);
	if (PlayAgainWidget)
		PlayAgainWidget->AddToViewport(0);

	ScoreWidget->RemoveFromParent();

	// Reset overlapper
	if (Overlapper)
		Overlapper->ClearField();


	// Call end game functions in player state and player pawn
	ATetrisPawn* PlayerPawn = Cast<ATetrisPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (PlayerPawn)
	{
		PlayerPawn->EndGame();

		ATetrisPlayerState* PlayerState = Cast<ATetrisPlayerState>(PlayerPawn->GetPlayerState());
		if (PlayerState)
			PlayerState->EndGame();
	}

	return;
}

UScoreWidget* ATetrisGameModeBase::GetScoreWidget() const
{
	return ScoreWidget;
}