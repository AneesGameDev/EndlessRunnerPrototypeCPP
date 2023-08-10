// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacter.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
		float Speed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Movement")
		bool bIsInAir;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
		class APawn* pawn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
		class UPawnMovementComponent* MovementComponent;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
		AMyCharacter* MyCharacter;


	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/*UFUNCTION()
	virtual void Tick(float DeltaTime) override;*/

	
};
