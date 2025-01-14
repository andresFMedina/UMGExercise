// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendListWidget.generated.h"

class UTextBlock;
class UListView;
class UButton;
class UImage;
class UFriendModel;
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

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* CollapseListAnimation;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ExpandListAnimation;
	
	UPROPERTY()	
	TArray<UFriendModel*> FriendsList;


protected:
	virtual void NativeConstruct() override;

public:
	void SetFriendsListValues(const TArray<UFriendModel*>& Friends);

	void SetListName(const FString& ListName);

	UFriendModel* GetFriendByNickname(const FString& NicknameToLook) const;

	void AddListItem(UFriendModel* FriendToAdd);

	void RemoveListItem(UFriendModel* FriendToRemove);

	void CollapseButtonAction();

	UFUNCTION(BlueprintCallable)
	void OnCollapseButtonClick();
};
