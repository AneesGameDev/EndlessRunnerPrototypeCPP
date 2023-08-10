// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinItem.generated.h"

UCLASS()
class ENDLESSRUNNERCPP_API ACoinItem : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* CoinStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UNiagaraSystem* NiagraParticle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Components")
		class URotatingMovementComponent* RotatingMovementComponent;
	
	UPROPERTY(EditAnywhere , BlueprintReadOnly , Category = "Components")
		class USoundBase* SoundOverlap;

	//UPROPERTY(EditAnywhere , BlueprinteReadOnly , Category = "Components")
		


	// Sets default values for this actor's properties
	ACoinItem();

protected:

	UFUNCTION()
		void BeginOverlapSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
