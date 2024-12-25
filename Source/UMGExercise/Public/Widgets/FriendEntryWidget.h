// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FriendEntryWidget.generated.h"

class UTextBlock;
class UFriendModel;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UFriendEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* FriendModelItem) override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* NicknameLabel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* LevelLabel;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* ConnectionStatusLabel;

	UPROPERTY()
	UFriendModel* FriendItem;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UFriendModel* GetFriendItem() const { return FriendItem; }
	
};
