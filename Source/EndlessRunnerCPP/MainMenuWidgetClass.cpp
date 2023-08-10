// Fill out your copyright notice in the Description page of Project Settings.
#include "MainMenuWidgetClass.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/Button.h"


void UMainMenuWidgetClass::NativeConstruct()
{
	if (StartBtn) {
		StartBtn->OnClicked.AddDynamic(this, &UMainMenuWidgetClass::OnStartClick);

	}
	if (QuitBtn) {
		QuitBtn->OnClicked.AddDynamic(this, &UMainMenuWidgetClass::OnQuitClick);
	}



}

void UMainMenuWidgetClass::OnStartClick()
{

	UWorld* world = GetWorld();
	if (world) {
		UGameplayStatics::OpenLevel(world, TEXT("EndlessRunnerMap1"));
	}

}

void UMainMenuWidgetClass::OnQuitClick()
{
	UWorld* world = GetWorld();
	if (world) {
		UKismetSystemLibrary::ExecuteConsoleCommand(world, TEXT("quit"));
	}
}