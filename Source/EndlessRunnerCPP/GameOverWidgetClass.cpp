// Fill out your copyright notice in the Description page of Project Settings.
#include "GameOverWidgetClass.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GamePlayStatics.h"







void UGameOverWidgetClass::NativeConstruct()
{

	if (MainMenuBtn) {
		MainMenuBtn->OnClicked.AddDynamic(this, &UGameOverWidgetClass::MainMenuClick);
	
	}
	if (RestartBtn) {
		RestartBtn->OnClicked.AddDynamic(this, &UGameOverWidgetClass::RestartClick);
	}

}

void UGameOverWidgetClass::MainMenuClick()
{
	UWorld* world = GetWorld();
	if (world) {
		UGameplayStatics::OpenLevel(world, TEXT("MainMenuLevel"));
	}
}

void UGameOverWidgetClass::RestartClick()
{
	UWorld* world = GetWorld();
	if (world) {
		UKismetSystemLibrary::ExecuteConsoleCommand(world, TEXT("RestartLevel"));
	}
}
