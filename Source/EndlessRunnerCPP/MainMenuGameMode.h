// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = "UMGCustom")

		TSubclassOf<UUserWidget> MainMenuWidgetClass;;

public:
	virtual void BeginPlay() override;

	
};
