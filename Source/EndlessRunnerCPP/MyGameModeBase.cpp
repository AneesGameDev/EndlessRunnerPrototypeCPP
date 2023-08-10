// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"
#include "FlootTileActor.h"



void AMyGameModeBase::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	GameHud =Cast<UWidgetGameHUD>(CreateWidget(GetWorld(), GameHudClass));
	GameHud->AddToViewport();
	check(GameHud);

	GameHud->InitializeHUD(this);

	CreateInitialFloorTiles();

	NumberOfLives = MaxLives;

}



void AMyGameModeBase::CreateInitialFloorTiles()
{
	AFlootTileActor* Tile = AddFloorTiles(false);

	if (Tile) {
		LanSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LanSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LanSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
	}


	AddFloorTiles(false); 
		AddFloorTiles(false);

	for (int i = 0; i < NumInitialFloorTiles; i++) {
		AddFloorTiles(true);
	}

	//for (float Val : LanSwitchValues) {
	//	UE_LOG(LogTemp, Warning, TEXT("Location Of Lan is %f"), Val);
	//}
	

}

void AMyGameModeBase::AddCoin()
{
	TotalCoins += 1;

	OnCoinsChange.Broadcast(TotalCoins);
	UE_LOG(LogTemp, Warning, TEXT("TotalCoins is %d"), TotalCoins);

}

void AMyGameModeBase::PlayerDied()
{
	NumberOfLives -= 1;

	OnLivesChange.Broadcast(NumberOfLives);

	if (NumberOfLives > 0) {
		// Level Continue 

		for (auto Tiles : FloorTiles) {
			Tiles->DestroyFloorTile();
		}

		FloorTiles.Empty();

		NextSpawnPoint = FTransform();

		CreateInitialFloorTiles();

		OnLevelReset.Broadcast();


	}
	else
	{
		//UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
		//Restart Game Player isDied
		GameOver();
	}
}

void AMyGameModeBase::GameOver()
{
	UWorld* world = GetWorld();
	if (world) {
		world->GetTimerManager().SetTimer(TimerPause, this, &AMyGameModeBase::TempFunc, 1.5f);
	}
	
	//UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (IsValid(GameOverWidgetClass)) {
		UUserWidget* Widget = CreateWidget(GetWorld(), GameOverWidgetClass);
		if (Widget) {
			Widget->AddToViewport();
		}
	}
}
void AMyGameModeBase::TempFunc() {
	//UWorld* world = GetWorld();
	if (TimerPause.IsValid()) {
		GetWorldTimerManager().ClearTimer(TimerPause);
	}
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMyGameModeBase::RemoveFloorTiles(AFlootTileActor* TileRemoved)
{
	FloorTiles.Remove(TileRemoved);
}

AFlootTileActor* AMyGameModeBase::AddFloorTiles(const bool bSpawnItems)
{
	UWorld* World = GetWorld();

	if (World) {  
		AFlootTileActor* Tile = World->SpawnActor<AFlootTileActor>(FloorTileClass, NextSpawnPoint);
		if (Tile) {

			FloorTiles.Add(Tile);

			if (bSpawnItems) {
				Tile->SpawnItem();
			}


			NextSpawnPoint = Tile->GetAttachTransform();
		}
		return Tile;
	}

	return nullptr;
}

