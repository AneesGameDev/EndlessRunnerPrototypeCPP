// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "MyCharacter.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneComponent);

	StaticMesh->OnComponentHit.AddDynamic(this, &AObstacle::OnObstacleHit);

}

void AObstacle::OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	AMyCharacter* myCharacter = Cast<AMyCharacter>(OtherActor);
	if (myCharacter) {
		if (!myCharacter->bSlidePowerAvailable) {
			myCharacter->Death();
		}
		else{
			auto Mesh =Cast<UStaticMeshComponent>(HitComponent);
			Mesh->SetCollisionProfileName(CollisionProfile.Name, true);
			//Mesh->CollisionPresets
			//Mesh->SetGenerateOverlapEvents(false);
			//StaticMesh->
			//Death Not Called
		}
		
	}

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

