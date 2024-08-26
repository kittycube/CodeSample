// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalPoint.h"

#include "PaperFlipbookComponent.h"
#include "PlayerCharacter.h"

AGoalPoint::AGoalPoint(): GoalFlipbook(nullptr)
{
}

void AGoalPoint::BeginPlay()
{
	Super::BeginPlay();
	GetRenderComponent()->OnComponentHit.AddDynamic(this, &AGoalPoint::OnHit);
}

// if player hits this, then end the game
void AGoalPoint::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter->WinGame();
		GetRenderComponent()->SetFlipbook(GoalFlipbook);
	}
}
