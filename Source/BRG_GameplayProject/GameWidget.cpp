// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

void UGameWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	EndGamePanel->SetVisibility(ESlateVisibility::Hidden);
	CheeseCounter->SetText(FText::FromString("0"));
}

void UGameWidget::WinGame()
{
	EndGamePanel->SetVisibility(ESlateVisibility::Visible);
	WinText->SetVisibility(ESlateVisibility::Visible);
	LoseText->SetVisibility(ESlateVisibility::Hidden);
}

void UGameWidget::LoseGame()
{
	EndGamePanel->SetVisibility(ESlateVisibility::Visible);
	WinText->SetVisibility(ESlateVisibility::Hidden);
	LoseText->SetVisibility(ESlateVisibility::Visible);
}

void UGameWidget::ChangeCheeseCount(int Count)
{
	CheeseCounter->SetText(FText::FromString(FString::FromInt(Count)));
	
}




