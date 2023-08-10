// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{

	if (pawn == nullptr) {

		pawn = TryGetPawnOwner();

	}

	if (IsValid(pawn)) {
		MovementComponent = pawn->GetMovementComponent();

		MyCharacter = Cast<AMyCharacter>(pawn);
	}



}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	if (pawn && MovementComponent) {

		if (MyCharacter && MyCharacter->bSlidePowerAvailable) {
			Speed = 0;
		}
		else {
			bIsInAir = MovementComponent->IsFalling();

			Speed = pawn->GetVelocity().Size();
		}

		
	}



}

//void UMyAnimInstance::Tick(float DeltaTime)
//{
//}
