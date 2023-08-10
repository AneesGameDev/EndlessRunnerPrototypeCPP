// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidgetClass.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API UGameOverWidgetClass : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* MainMenuBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* RestartBtn;
	



public:

	UFUNCTION()
		virtual void NativeConstruct() override;


	UFUNCTION()
		void MainMenuClick();

	UFUNCTION()
		void RestartClick();

};
