// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"


ATrap::ATrap()
{
	// Configure Size
	GetRenderComponent()->SetRelativeScale3D(FVector(1.25f,1.0f,1.25f));
}

void ATrap::BeginPlay()
{
	Super::BeginPlay();
}

