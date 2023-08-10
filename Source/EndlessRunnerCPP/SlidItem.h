// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlidItem.generated.h"

UCLASS()
class ENDLESSRUNNERCPP_API ASlidItem : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SlideComponents")
		class USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SlideComponents")
		class UStaticMeshComponent* StaticSlideMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SlideComponents")
		class URotatingMovementComponent* SlideRotatingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SlideComponents")
		class USoundBase* SlideSoundBase;

	



	// Sets default values for this actor's properties
	ASlidItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBeginOverlapSlide(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
