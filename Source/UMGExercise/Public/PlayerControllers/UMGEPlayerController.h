// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UMGEPlayerController.generated.h"

class UFriendHUD;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API AUMGEPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDOverlayClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD", meta = (AllowPrivateAccess = "true"))
	UUserWidget* HUDOverlay;
	
};
