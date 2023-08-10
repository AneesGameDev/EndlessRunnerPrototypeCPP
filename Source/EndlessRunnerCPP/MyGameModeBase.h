// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WidgetGameHUD.h"
#include "EndlessRunnerCPPGameModeBase.h"
#include "MyGameModeBase.generated.h"

//class UUserWidget;
class AFlootTileActor;

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChange, int32, CoinCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCountChange, int32, LivesCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelReset);

UCLASS()

class ENDLESSRUNNERCPP_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere, Category = "Config")
    
	TSubclassOf<AFlootTileActor> FloorTileClass;

	UPROPERTY(EditAnywhere, Category = "FloorTiles")
		TArray<AFlootTileActor*> FloorTiles;


	UPROPERTY(EditAnywhere, Category = "UMGCustom")

		TSubclassOf<UUserWidget> GameOverWidgetClass;;

	UPROPERTY(EditAnywhere, Category = "UMGCustom")

		TSubclassOf<UUserWidget> GameHudClass;


	UPROPERTY(VisibleInstanceOnly, Category = "GameHud")
	UWidgetGameHUD* GameHud;

	UPROPERTY(VisibleInstanceOnly, Category = "GameHud")
	FTimerHandle TimerPause;


	
	UPROPERTY(EditAnywhere, Category = "Config")
	int32 NumInitialFloorTiles = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "runtimeNextPoint")
	FTransform NextSpawnPoint;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	TArray<float> LanSwitchValues;

	UPROPERTY(VisibleAnywhere)
		int32 TotalCoins = 0;

	UPROPERTY(VisibleAnywhere)
		int32 NumberOfLives;

	UPROPERTY(EditAnywhere)
		int32 MaxLives = 3;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, Category = "LivesChangeEvent")
	  FOnLivesCountChange OnLivesChange;


	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, Category = "OnCoinsChangeEvent")
		FOnCoinsCountChange OnCoinsChange;

	
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, Category = "OnLevelReset")
		FOnLevelReset OnLevelReset;

	UFUNCTION(BlueprintCallable)
	void CreateInitialFloorTiles();

	UFUNCTION(BlueprintCallable)
		void AddCoin();

	UFUNCTION(BlueprintCallable)
		void PlayerDied();

	UFUNCTION(BlueprintCallable)
		void GameOver();

	UFUNCTION()
		void RemoveFloorTiles(AFlootTileActor* TileRemoved);

	UFUNCTION()
		void TempFunc();

	UFUNCTION(BlueprintCallable)

   AFlootTileActor* AddFloorTiles(const bool bSpawnItems);


	virtual void BeginPlay() override;

	
};
