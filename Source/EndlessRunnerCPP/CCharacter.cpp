// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACCharacter::ACCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBooom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBooom->SetupAttachment(GetRootComponent());
	CameraBooom->TargetArmLength = 600.f;
	CameraBooom->bUsePawnControlRotation = true;

	CameraFollow = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraFollow->SetupAttachment(CameraBooom, USpringArmComponent::SocketName);
	CameraFollow->bUsePawnControlRotation = false;

	BaseLookUpRate = 65.f;
	BaseTurnRate = 65.f;


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()-> RotationRate = (FRotator(0.f, 540.f, 0.f));
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;





}

// Called when the game starts or when spawned
void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACCharacter::LookUpInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &ACCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACCharacter::LookUpAtRate);


}

void ACCharacter::MoveForward(float Value)
{

	if (Controller != nullptr && Value != 0.f) {
		FRotator Rotator = Controller->GetControlRotation();
		//FRotator YawRotation(0.f, Rotator.Yaw, 0.f);
		Rotator.Pitch = 0.f;
		Rotator.Roll = 0.f;
		//FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Rotator.Vector(), Value);
	}

}

void ACCharacter::MoveRight(float Value)
{

	if (Controller != nullptr && Value != 0.f) {
		FRotator Rotator = Controller->GetControlRotation();
		//FRotator YawRotation(0.f, Rotator.Yaw, 0.f);
		//FVector VectorNew = FVector(0.f, Rotator.Yaw, 0.f);
		Rotator.Pitch = 0.f;
		Rotator.Roll = 0.f;
		FVector Direction = FRotationMatrix(Rotator).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}

}

void ACCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void ACCharacter::LookUpInput(float Val)
{
	
	PlayerController = Cast<APlayerController>(APawn::Controller);
	PlayerController->PlayerCameraManager->ViewPitchMax = 10.f;
	PlayerController->PlayerCameraManager->ViewPitchMin = -50.f;
	AddControllerPitchInput(Val);

}

