// Fill out your copyright notice in the Description page of Project Settings.

#include "FlootTileActor.h"
#include "Kismet/KismetMathLibrary.h"
//#include "CoinItem.h"
#include "Obstacle.h"

//#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
//#include "GameplayStatics.generated.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.h"
#include "MyGameModeBase.h"
#include "EndlessRunnerCPPGameModeBase.h"



// Sets default values
AFlootTileActor::AFlootTileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(SceneComponent);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachPoint"));
	AttachPoint->SetupAttachment(SceneComponent);

	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("CenterLane"));
	CenterLane->SetupAttachment(SceneComponent);

	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftLane"));
	LeftLane->SetupAttachment(SceneComponent);

	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("RightLane"));
	RightLane->SetupAttachment(SceneComponent);

	FloorTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FloorTriggerBox"));
	FloorTriggerBox->SetupAttachment(SceneComponent);
	FloorTriggerBox->SetBoxExtent(FVector(32.f ,500.f, 200.f ));
	FloorTriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));




}






// Called when the game starts or when spawned
void AFlootTileActor::BeginPlay()
{
	Super::BeginPlay();
	RunnerGameMode =Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunnerGameMode);

	FloorTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFlootTileActor::OnTriggerBoxOverlap);


	
}

// Called every frame
void AFlootTileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlootTileActor::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AMyCharacter* myCharacter = Cast<AMyCharacter>(OtherActor);
	if (myCharacter) {
		RunnerGameMode->AddFloorTiles(true);

		GetWorldTimerManager().SetTimer(DestroyHandle, this, &AFlootTileActor::DestroyFloorTile, 2.0f, false);
		//GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, AFlootTileActor::DestroyFloorTile(), 2.0, false);
	}


}
void AFlootTileActor::DestroyFloorTile() {


	if(DestroyHandle.IsValid()) {
		GetWorldTimerManager().ClearTimer(DestroyHandle);
	}



	for (auto ChildActor : ChildActors) {
		if (ChildActor) {
			ChildActor->Destroy();
		}
	}


	ChildActors.Empty();

	RunnerGameMode->RemoveFloorTiles(this);

	this->Destroy();

}

void AFlootTileActor::SpawnItem()
{
	if (IsValid(smallObstacle) && IsValid(biggObstacleClass)) {

		int32 NumBig = 0;

		SpawnLaneItem(LeftLane , NumBig);
		SpawnLaneItem(RightLane , NumBig);
		SpawnLaneItem(CenterLane , NumBig);
	}


}

void AFlootTileActor::SpawnLaneItem(UArrowComponent* Lane , int32& NumBig)
{

	float RandValue = FMath::RandRange(0.1f, 1.2f);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FTransform& SpawnLocation = Lane->GetComponentTransform();

	if (UKismetMathLibrary::InRange_FloatFloat(RandValue,SpawnPercent1, SpawnPercent2, true, true)) {
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(smallObstacle, SpawnLocation, SpawnParameters);
		
		ChildActors.Add(Obstacle);

	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent2, SpawnPercent3, true, true)) {

		if (NumBig < 2) {
			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(biggObstacleClass, SpawnLocation, SpawnParameters);

			if (Obstacle) {
				ChildActors.Add(Obstacle);
				NumBig += 1;
			}
		}
		else
		{

			AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(smallObstacle, SpawnLocation, SpawnParameters);
			ChildActors.Add(Obstacle);
		}

	}
	else if (UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent3, 0.6, true, true)) {
		ACoinItem* CoinItem = GetWorld()->SpawnActor<ACoinItem>(CoinsItemClass, SpawnLocation, SpawnParameters);
		ChildActors.Add(CoinItem);
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(RandValue, 0.6, 0.7, true, true))
	{
		float RandValues = FMath::RandRange(1.5f, 2.5f);
		if (RandValues <= 2.2f) {
			ASlidItem* SlideItem = GetWorld()->SpawnActor<ASlidItem>(SlideItemClass, SpawnLocation, SpawnParameters);
		}
		else
		{
			ACoinItem* CoinItem = GetWorld()->SpawnActor<ACoinItem>(CoinsItemClass, SpawnLocation, SpawnParameters);
			ChildActors.Add(CoinItem);
		}
		
	}

	/*if (UKismetMathLibrary::InRange_FloatFloat(RandValue, SpawnPercent3, 0.6, true, true)) {
		
	}*/

}
