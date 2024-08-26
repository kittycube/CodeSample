// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"


class UCanvasPanel;
class UTextBlock;

/**
 * 
 */
UCLASS()
class BRG_GAMEPLAYPROJECT_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void WinGame();
	void LoseGame();
	void ChangeCheeseCount(int Count);
	
protected:
	virtual void NativePreConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) 
	UCanvasPanel* EndGamePanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) 
	UTextBlock* WinText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) 
	UTextBlock* LoseText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) 
	UCanvasPanel* StatsPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) 
	UTextBlock* CheeseCounter;
};
