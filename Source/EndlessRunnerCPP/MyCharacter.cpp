// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"
//#include "Components/ActorComponent.h"
#include "MyGameModeBase.h"



//class UCharacterMovementComponent;

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("cameraArm"));
	CameraArm->TargetArmLength = 350.f;
	CameraArm->SocketOffset = FVector(0, 0, 100.f);
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->SetupAttachment(GetMesh());


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	SliderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SliderMesh"));
	SliderMesh->SetupAttachment(GetMesh());

	//SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	//RootComponent = SceneComponent;
	//GetCapsuleComponent()->SetupAttachment(SceneComponent);

	//SlideMesh->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlidingMesh"));

	//SlideMesh->SetupAttachment(GetRootComponent());


}


// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	myGameModeBase = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	 

	check(myGameModeBase);

	myGameModeBase->OnLevelReset.AddDynamic(this, &AMyCharacter::PlayerReset);
	
	PlayerStart = Cast<APlayerStart>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass()));
}





// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator ControlRot = GetControlRotation();
	ControlRot.Roll = 0.f;
	ControlRot.Pitch = 0.f;

	AddMovementInput(ControlRot.Vector());



}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::DelayDownFunction);


	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &AMyCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAction("Down", IE_Pressed, this, &AMyCharacter::MoveDown);
	PlayerInputComponent->BindAction("SpeedUp", IE_Pressed, this, &AMyCharacter::SpeedUpCharacter);
	PlayerInputComponent->BindAction("SpeedUp", IE_Released, this, &AMyCharacter::SpeedDownCharacter);

}




void AMyCharacter::ChangeLaneUpdate(const float Val)
{
	 
	FVector Location = GetCapsuleComponent()->GetComponentLocation();

	Location.Y = FMath::Lerp(myGameModeBase->LanSwitchValues[CurrentLane], myGameModeBase->LanSwitchValues[NextLane], Val);
	UE_LOG(LogTemp, Warning, TEXT("Location Of Character Function is called %f") , Location.Y ,Val);
	SetActorLocation(Location);
	
}

void AMyCharacter::ChangeLaneFinished()
{
	CurrentLane = NextLane;
}

void AMyCharacter::Death()
{
	if(!bIsDead){
	FVector Location = GetActorLocation();

	UWorld* world = GetWorld();
	if (world) {
		bIsDead = true;
		DisableInput(nullptr);
		if (DeathParticleSystem) {
			UGameplayStatics::SpawnEmitterAtLocation(world, DeathParticleSystem, Location);
		}

		if (DeathSoundSystem) {
			UGameplayStatics::PlaySoundAtLocation(world, DeathSoundSystem, Location);
		}

		GetMesh()->SetVisibility(false);

		
	}
	world->GetTimerManager().SetTimer(RestartTimeHandle, this, &AMyCharacter::OnDeath, 0.5f);

	}
}

void AMyCharacter::AddCoin()
{
	myGameModeBase->AddCoin();
}




void AMyCharacter::OnDeath()
{
	//bIsDead = false;
	if (RestartTimeHandle.IsValid()) {
		GetWorldTimerManager().ClearTimer(RestartTimeHandle);
	}

	//UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));

	myGameModeBase->PlayerDied();

}

void AMyCharacter::PlayerReset()
{
	bIsDead = false;
	EnableInput(nullptr);
	GetMesh()->SetVisibility(true);
	//GetMesh()->AddLocalOffset(PlayerStart->GetActorLocation());
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	//GetMesh()->GetChildComponent(0)->SetVisibility(false);
	SliderMesh->SetVisibility(false);
	if (PlayerStart) {
		SetActorLocation(PlayerStart->GetActorLocation());
		SetActorRotation(PlayerStart->GetActorRotation());
	}
}



void AMyCharacter::MoveLeft()
{

	NextLane = FMath::Clamp(CurrentLane +1, 0, 2);
	ChangeLane();

	//UE_LOG(LogTemp, Warning, TEXT("Move Left Function is called"));
}

void AMyCharacter::MoveRight()
{
	NextLane = FMath::Clamp(CurrentLane -1, 0, 2);
	ChangeLane();
	//NextLane = FMath::Clamp(CurrentLane 1, 0, 2);
	//UE_LOG(LogTemp, Warning, TEXT("Move Right Function is called"));
}


void AMyCharacter::DelayDownFunction() {
	
	UWorld* World = GetWorld();
	if (World) {

		World->GetTimerManager().SetTimer(TimerDealyHandel, this, &AMyCharacter::MoveDown, 0.4f);

	}
	

}

void AMyCharacter::MoveDown()
{
	
 // GEngine->AddOnScreenDebugMessage(-1.f , 50.f, FColor::Green,FString::Printf(TEXT(""));

	if (TimerDealyHandel.IsValid()) {
		GetWorldTimerManager().ClearTimer(TimerDealyHandel);
	}
	static FVector Impuls = FVector(0, 0, fMoveDownImplus);
	GetCharacterMovement()->AddImpulse(Impuls, true);

	//UE_LOG(LogTemp, Warning, TEXT("Move Down Function is called"));
}


void AMyCharacter::AddSlidePower()
{
	if (!bSlidePowerAvailable) {

	//GetCapsuleComponent()->SetGenerateOverlapEvents(false);
		UE_LOG(LogTemp, Warning, TEXT("Add Slider is Called"));
	SliderMesh->SetVisibility(true);
	
	bSlidePowerAvailable = true;
	//GetCapsuleComponent()->SetCollisionProfileName("NoCollision");

	//GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Slide IS Given To Character"));
	GetWorld()->GetTimerManager().SetTimer(SlideTimer, this, &AMyCharacter::RemoveSlidePower, 5.f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, 140.f));
	GetCharacterMovement()->MaxWalkSpeed = 15000.f;

	}
}

void AMyCharacter::RemoveSlidePower()
{
	if (bSlidePowerAvailable) {


	SliderMesh->SetVisibility(false);
	//GetMesh()->
	bSlidePowerAvailable = false;
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetCharacterMovement()->MaxWalkSpeed = 1500.f;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Slide Is Removed Now"));
	//GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	}
}

void AMyCharacter::SpeedUpCharacter()
{
	if (!bSlidePowerAvailable) {
		GetCharacterMovement()->MaxWalkSpeed = 4300.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 15000.f;
	}
	
}

void AMyCharacter::SpeedDownCharacter()
{
	if (!bSlidePowerAvailable) {
		GetCharacterMovement()->MaxWalkSpeed = 1500.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 15000.f;
	}
	
}