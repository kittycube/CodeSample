// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Cheese.generated.h"

/**
 * 
 */
UCLASS()
class BRG_GAMEPLAYPROJECT_API ACheese : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	ACheese();
	
protected:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
