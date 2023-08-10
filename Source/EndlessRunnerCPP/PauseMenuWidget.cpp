// Fill out your copyright notice in the Description page of Project Settings.
#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"


void UPauseMenuWidget::NativeConstruct()
{
	if(ContinueBtn)
	ContinueBtn->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnContinueClick);

	if(RestartBtn)
	RestartBtn->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnPauseClick);

	if(MainMenu)
		MainMenu->OnClicked.AddDynamic(this, &UPauseMenuWidget::MainMenuClick);
}

void UPauseMenuWidget::OnContinueClick()
{

	UGameplayStatics::SetGamePaused(GetWorld(), false);
	RemoveFromParent();

}

void UPauseMenuWidget::OnPauseClick()
{
	UWorld* world = GetWorld();
	if(world)
	UKismetSystemLibrary::ExecuteConsoleCommand(world, TEXT("RestartLevel"));
}

void UPauseMenuWidget::MainMenuClick()
{
	UWorld* world = GetWorld();
	if (world) {
		UGameplayStatics::OpenLevel(world, TEXT("MainMenuLevel"));
	}
}
