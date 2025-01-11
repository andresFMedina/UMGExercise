// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendDetailsHoverWidget.generated.h"

class UTextBlock;
class UFriendModel;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UFriendDetailsHoverWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* NicknameLabel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* DescriptionLabel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* LevelLabel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* ConnectionStatusLabel;
	
public:
	void DisplayWidget(UFriendModel* Friend);
};
