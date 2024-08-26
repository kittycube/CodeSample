// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class UGameWidget;

/**
 * 
 */
UCLASS()
class BRG_GAMEPLAYPROJECT_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

	// game widget blueprint class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HUD, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameWidget> GameWidgetClass;

public:
	// getter
	UGameWidget* GetGameWidget() const
	{
		return GameWidget;
	}
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY()
	UGameWidget* GameWidget;
};
