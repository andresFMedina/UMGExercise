// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendHUD.h"
#include "Widgets/FriendListWidget.h"
#include "ViewModels/FriendsViewModel.h"

void UFriendHUD::NativeConstruct()
{
	Super::NativeConstruct();

	FriendsViewModel = NewObject<UFriendsViewModel>();
	InitializeLists();
	FriendsViewModel->OnFriendStatusChangedDelegate.AddDynamic(this, &ThisClass::OnChangeUserConnectionStatus);
}

void UFriendHUD::InitializeLists()
{
	check(FriendsViewModel && ConnectedFriendsWidget && DisconnectedFriendsWidget);

	ConnectedFriendsWidget->SetListName(FString("Online"));
	ConnectedFriendsWidget->SetFriendsListValues(FriendsViewModel->GetFriendsByConnectionStatus(true));
	DisconnectedFriendsWidget->SetListName(FString("Offline"));
	DisconnectedFriendsWidget->SetFriendsListValues(FriendsViewModel->GetFriendsByConnectionStatus(false));
	
}

void UFriendHUD::OnChangeUserConnectionStatus(UObject* Friend, bool bIsConnected)
{
	if (bIsConnected) {
		SetConnectedFriend(Friend);
		return;
	}
	SetDisconnectedFriend(Friend);
}

void UFriendHUD::SetConnectedFriend(UObject* Friend)
{
	DisconnectedFriendsWidget->RemoveListItem(Friend);
	ConnectedFriendsWidget->AddListItem(Friend);
}

void UFriendHUD::SetDisconnectedFriend(UObject* Friend)
{
	ConnectedFriendsWidget->RemoveListItem(Friend);
	DisconnectedFriendsWidget->AddListItem(Friend);
}
