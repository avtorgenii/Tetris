// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayAgainWidget.h"
#include "Kismet/GameplayStatics.h"

void UPlayAgainWidget::NativeConstruct()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
}