// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "GoalPoint.generated.h"

class UPaperFlipbook;
/**
 * 
 */
UCLASS()
class BRG_GAMEPLAYPROJECT_API AGoalPoint : public APaperFlipbookActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sprite, meta = (AllowPrivateAccess))
	UPaperFlipbook* GoalFlipbook;
	
public:
	AGoalPoint();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
