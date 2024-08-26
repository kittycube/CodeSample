// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

#include "GameWidget.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	// create instance of game widget 
	GameWidget = CreateWidget<UGameWidget>(GetWorld(), GameWidgetClass);
	GameWidget->AddToViewport();
}
