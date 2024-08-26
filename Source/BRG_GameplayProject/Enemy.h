// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "Enemy.generated.h"

class UPaperFlipbook;
class UBoxComponent;

/**
 * 
 */
UCLASS(Abstract)
class BRG_GAMEPLAYPROJECT_API AEnemy : public APaperFlipbookActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sprite, meta = (AllowPrivateAccess))
	UPaperFlipbook* CaughtMouseFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sprite, meta = (AllowPrivateAccess))
	UPaperFlipbook* DisabledFlipbook;

public:
	AEnemy();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	bool bIsActive = true;
};