// Fill out your copyright notice in the Description page of Project Settings.
#include "SlidItem.h"
#include "MyCharacter.h"
#include "Engine.h"
#include "GameFramework/RotatingMovementComponent.h"


// Sets default values
ASlidItem::ASlidItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	StaticSlideMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticSlideMesh"));
	StaticSlideMesh->SetupAttachment(RootComponent);


	SlideRotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("SlidingRotating"));
	SlideRotatingComponent->RotationRate = FRotator(0, 180, 0);

	//StaticSlideMesh->SetCollisionProfileName(TEXT("CollisonPawnOverlapOnly"));


}

// Called when the game starts or when spawned
void ASlidItem::BeginPlay()
{
	Super::BeginPlay();
	

	StaticSlideMesh->OnComponentBeginOverlap.AddDynamic(this, &ASlidItem::OnBeginOverlapSlide);
}

void ASlidItem::OnBeginOverlapSlide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, "Add Slider is Called");
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor);
	
	if (MyCharacter) {

		if (!MyCharacter->bSlidePowerAvailable) {
			MyCharacter->AddSlidePower();
			
		}
	}

	//UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(OverlappedComponent);
	Destroy();



}

// Called every frame
void ASlidItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

