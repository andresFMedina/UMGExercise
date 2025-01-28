// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendHUD.generated.h"

class UFriendListWidget;
class UFriendStatusNotificationWidget;
class UDataTable;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UFriendHUD : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite ,meta = (BindWidget, AllowPrivateAccess))
	UFriendListWidget* ConnectedFriendsWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess))
	UFriendListWidget* DisconnectedFriendsWidget;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UFriendStatusNotificationWidget* FriendStatusNotification;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSoftObjectPtr<UDataTable> DataSource;	

protected:
	virtual void NativeConstruct() override;
private:
	/*void InitializeLists();
	
	UFUNCTION()
	void OnChangeUserConnectionStatus(FString& UserNickname, bool bIsConnected);	

	void MoveListItem(UFriendListWidget* SourceList, UFriendListWidget* DestinyList, const FString& Nickname, const bool bIsConnected);	*/
};
