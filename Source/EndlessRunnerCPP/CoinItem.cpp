// Fill out your copyright notice in the Description page of Project Settings.
#include "CoinItem.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "MyCharacter.h"
#include "GameFramework/RotatingMovementComponent.h"



// Sets default values
ACoinItem::ACoinItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(SceneComponent);
	SphereCollider->SetCollisionProfileName("CollisonPawnOverlapOnly");


	CoinStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMesh"));
	CoinStaticMesh->SetupAttachment(SphereCollider);
	CoinStaticMesh->SetCollisionProfileName(TEXT("CollisonPawnOverlapOnly"));

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingComponent"));
	RotatingMovementComponent->RotationRate = FRotator(0, 180, 0);





}


// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ACoinItem::BeginOverlapSphere);
	
}


void ACoinItem::BeginOverlapSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	AMyCharacter* myCharacter = Cast<AMyCharacter>(OtherActor);
	if (myCharacter) {

		if (SoundOverlap) {
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundOverlap , GetActorLocation());
		}
		if (NiagraParticle) {
			FVector Location = FVector(180, 0, 0);
			/*UWorld* world = GetWorld();
			Location +=world->OriginLocation;
			FVector LocationWorld = FVector(Location.X, Location.Y, Location.Z);*/
			
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, NiagraParticle, GetActorLocation() + Location, FRotator::ZeroRotator, FVector::OneVector, true);
		}
		myCharacter->AddCoin();
	}

	

	Destroy();

}



// Called every frame
void ACoinItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

