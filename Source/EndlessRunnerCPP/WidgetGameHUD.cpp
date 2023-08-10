// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WidgetGameHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GamePlayStatics.h"
#include "MyGameModeBase.h"



//class AMyGameModeBase;


void UWidgetGameHUD::NativeConstruct()
{
	if (PauseBtn) {

		PauseBtn->OnClicked.AddDynamic(this, &UWidgetGameHUD::OnPauseClick);
	}
	
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);

}



void UWidgetGameHUD::InitializeHUD(AMyGameModeBase* GameModeBase)
{

	if (GameModeBase) {
		CoinCount->SetText(FText::AsNumber(0));
		LivesCount->SetText(FText::AsNumber(GameModeBase->MaxLives));
		GameModeBase->OnCoinsChange.AddDynamic(this, &UWidgetGameHUD::SetCoinsCount);
		GameModeBase->OnLivesChange.AddDynamic(this, &UWidgetGameHUD::SetLivesCount);

	}

}

void UWidgetGameHUD::SetCoinsCount(const int32 Coins)
{

	CoinCount->SetText(FText::AsNumber(Coins));

}

void UWidgetGameHUD::SetLivesCount(int32 Lives)
{
	LivesCount->SetText(FText::AsNumber(Lives));
}

void UWidgetGameHUD::OnPauseClick()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	UUserWidget* PauseMenu = CreateWidget(GetWorld(), UPauseMenuWidgetClass);

	if (PauseMenu) {
		PauseMenu->AddToViewport();
	}
}

