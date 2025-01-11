// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendListWidget.generated.h"

class UTextBlock;
class UListView;
class UButton;
class UImage;
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

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* CollapseButton;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* CollapseButtonImage;

protected:
	virtual void NativeConstruct() override;

public:
	void SetFriendsListValues(const TArray<UObject*> Friends);

	void SetListName(const FString& ListName);

	void AddListItem(UObject* FriendToAdd);

	void RemoveListItem(UObject* FriendToRemove);

	void CollapseButtonAction();

	UFUNCTION(BlueprintCallable)
	void OnCollapseButtonClick();
};
