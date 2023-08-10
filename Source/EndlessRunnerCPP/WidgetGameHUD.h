// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
//#include "MyGameModeBase.h"
#include "WidgetGameHUD.generated.h"

class AMyGameModeBase;

/**
 * 
 */
UCLASS()
class ENDLESSRUNNERCPP_API UWidgetGameHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeHUD(AMyGameModeBase* GameModeBase);

	UFUNCTION(BlueprintCallable)
	void SetCoinsCount(int32 Coins);

	UFUNCTION(BlueprintCallable)
	void SetLivesCount(int32 Lives);

	UFUNCTION(BlueprintCallable)
	void OnPauseClick();

	UFUNCTION()

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* LivesCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PauseBtn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> UPauseMenuWidgetClass;


	
};
