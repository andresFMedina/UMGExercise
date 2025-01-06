// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendHUD.generated.h"

class UFriendListWidget;
class UFriendsViewModel;
class UDataTable;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UFriendHUD : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UFriendListWidget* ConnectedFriendsWidget;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UFriendListWidget* DisconnectedFriendsWidget;
	UPROPERTY()
	UFriendsViewModel* FriendsViewModel;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UDataTable> DataSource;

protected:
	virtual void NativeConstruct() override;
private:
	void InitializeLists();
	
	void OnChangeUserConnectionStatus(UObject* Friend, bool bIsConnected);

	void SetConnectedFriend(UObject* Friend);

	void SetDisconnectedFriend(UObject* Friend);
};
