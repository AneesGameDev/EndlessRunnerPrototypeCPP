// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/PlayerStart.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


class AMyGameModeBase;

UCLASS()
class ENDLESSRUNNERCPP_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()


private :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SliderMesh;
	


public:


	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SlideMesh")
		class UStaticMeshComponent* SlideMesh;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		int32 CurrentLane =1;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		int32 NextLane =0;
	UPROPERTY(VisibleInstanceOnly)
		AMyGameModeBase* myGameModeBase;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		UParticleSystem* CoinsParticleSystem;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		UParticleSystem* DeathParticleSystem;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		USoundBase* DeathSoundSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
		bool bSlidePowerAvailable=false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SlidingPower")
		int32 SlidingPower = 2000;


	UPROPERTY()
		FTimerHandle RestartTimeHandle;

	UPROPERTY()
		bool bIsDead = false;

	UPROPERTY()
		float fMoveDownImplus = -800.f;

	UPROPERTY()
		FTimerHandle TimerDealyHandel;

	UPROPERTY()
		APlayerStart* PlayerStart;

	UPROPERTY()
		FTimerHandle SlideTimer;

	// Sets default values for this character's properties
	AMyCharacter();

	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
		void ChangeLane();
	UFUNCTION(BlueprintCallable, Category = "Lane")
		void ChangeLaneUpdate(float Val);
	UFUNCTION(BlueprintCallable, Category = "Lane")
		void ChangeLaneFinished();

	UFUNCTION(BlueprintCallable)
		void Death();
	UFUNCTION(BlueprintCallable)
		void AddCoin();

	UFUNCTION()
		void PlayerReset();

	UFUNCTION(BlueprintCallable , Category ="AddSlide")
		void AddSlidePower();

	UFUNCTION(BlueprintCallable, Category = "AddSlide")
		void RemoveSlidePower();
	


protected:
	UFUNCTION(BlueprintCallable)
		void OnDeath();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void SpeedUpCharacter();
	UFUNCTION()
		void SpeedDownCharacter();




protected:
	UFUNCTION()
		void MoveLeft();

	UFUNCTION()
		void MoveRight();

	UFUNCTION()
		void MoveDown();
	UFUNCTION()
		void DelayDownFunction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
