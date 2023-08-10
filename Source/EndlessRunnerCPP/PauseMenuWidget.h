// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()


public: 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ContinueBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* RestartBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* MainMenu;

protected:

	UFUNCTION()
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnContinueClick();

	UFUNCTION()
		void OnPauseClick();

	UFUNCTION()
		void MainMenuClick();

	
};
