// Fill out your copyright notice in the Description page of Project Settings.


#include "Cheese.h"

#include "PlayerCharacter.h"
#include "PaperSpriteComponent.h"

ACheese::ACheese()
{
}

void ACheese::BeginPlay()
{
	Super::BeginPlay();
	// delegate for OnComponentBeginOverlap
	GetRenderComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACheese::OnBeginOverlap);
	GetRenderComponent()->SetCollisionProfileName("OverlapAll");
}

// if player overlaps, signal to player then destroy
void ACheese::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter->EatCheese();
		Destroy();
	}
}