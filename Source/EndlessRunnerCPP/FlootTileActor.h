// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoinItem.h"
#include "SlidItem.h"
#include "Obstacle.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
//#include "MyGameModeBase.generated.h"
#include "FlootTileActor.generated.h"



//class AObstacle;


UCLASS()
class ENDLESSRUNNERCPP_API AFlootTileActor : public AActor
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componenets");
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	class UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	class UArrowComponent* AttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	class UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	class UArrowComponent* RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	class UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components");
	class UBoxComponent* FloorTriggerBox;

	UPROPERTY();
	FTimerHandle DestroyHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
		TSubclassOf<AObstacle> smallObstacle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
		TSubclassOf<AObstacle> biggObstacleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
		TSubclassOf<ACoinItem> CoinsItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Silder")
		TSubclassOf<ASlidItem> SlideItemClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent1 = 0.1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent2 = 0.2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		float SpawnPercent3 = 0.3;

	UPROPERTY(EditAnywhere, Category = "FloorTiles")
		TArray<AActor*> ChildActors;




protected:
	class AMyGameModeBase* RunnerGameMode;

	
public:	
	// Sets default values for this actor's properties
	AFlootTileActor();


	UFUNCTION()
	void SpawnItem();

	UFUNCTION()
	void SpawnLaneItem(UArrowComponent* Lane , int32& NumBig);

	FORCEINLINE const FTransform& GetAttachTransform() const
	{
		return AttachPoint->GetComponentTransform();
	}

	UFUNCTION()
		void DestroyFloorTile();


protected:
	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
