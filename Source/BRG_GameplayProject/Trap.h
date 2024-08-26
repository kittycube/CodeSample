// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Trap.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class BRG_GAMEPLAYPROJECT_API ATrap : public AEnemy
{
	GENERATED_BODY()

public:
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
