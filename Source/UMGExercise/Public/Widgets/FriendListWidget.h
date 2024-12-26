// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendListWidget.generated.h"

class UTextBlock;
class UListView;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UFriendListWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* ListNameLabel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UListView* FriendsListView;

public:
	void SetFriendsListValues(const TArray<UObject*> Friends);

	void SetListName(const FString& ListName);

	void AddListItem(UObject* FriendToAdd);
	void RemoveListItem(UObject* FriendToRemove);
	
};
