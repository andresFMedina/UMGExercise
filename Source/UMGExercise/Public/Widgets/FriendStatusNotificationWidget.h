// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendStatusNotificationWidget.generated.h"


class UTextBlock;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UFriendStatusNotificationWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* MessageText;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float TimeToHideNotification = 5.f;

	FTimerHandle HideNotificationTimer;

public:
	void ShowNotification(const FString& Nickname);
	
	void HideNotification();
};
