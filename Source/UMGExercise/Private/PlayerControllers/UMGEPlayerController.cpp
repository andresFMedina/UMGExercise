// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/UMGEPlayerController.h"
#include "Blueprint/UserWidget.h"

void AUMGEPlayerController::BeginPlay()
{
	check(HUDOverlayClass);

	HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayClass);
	check(HUDOverlay);

	HUDOverlay->AddToViewport();
	//HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	SetShowMouseCursor(true);
}
