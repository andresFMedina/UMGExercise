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
class UFriendsVM;
/**
 *
 */
UCLASS()
class UMGEXERCISE_API UFriendListWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Getter = "GetIsOnlineList", Setter = "SetIsOnlineList")
	bool bIsOnlineList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* FriendsListView;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ListNameLabel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* CollapseButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	UImage* CollapseButtonImage;	

	virtual void NativeConstruct() override;

public:	

	UFUNCTION(BlueprintCallable)
	void AddListItem(UObject* FriendToAdd);

	UFUNCTION(BlueprintCallable)
	void RemoveListItem(UObject* FriendToRemove);

	UFUNCTION()
	bool GetIsOnlineList() const;

	UFUNCTION()
	void SetIsOnlineList(const bool IsOnlineList);


	/*UFUNCTION(BlueprintCallable)
	void CollapseButtonAction();*/
};
