// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Cat.generated.h"

class UInterpToMovementComponent;
class UArrowComponent;
/**
 * 
 */
UCLASS()
class BRG_GAMEPLAYPROJECT_API ACat : public AEnemy
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	// visual indication in editor of how far the enemy should travel
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* MovementIndicator;

	// movement component to interpolate enemy between points
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UInterpToMovementComponent* MovementComponent;
	
public:
	ACat();

protected:
	virtual void BeginPlay() override;
};
