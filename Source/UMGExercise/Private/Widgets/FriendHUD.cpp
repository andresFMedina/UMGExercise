// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendHUD.h"
#include "Widgets/FriendListWidget.h"
#include "Widgets/FriendStatusNotificationWidget.h"
#include "ViewModels/FriendsViewModel.h"
#include "Engine/DataTable.h"
#include "Models/FriendModel.h"

void UFriendHUD::NativeConstruct()
{
	Super::NativeConstruct();

	FriendsViewModel = NewObject<UFriendsViewModel>();
	InitializeLists();
}

void UFriendHUD::InitializeLists()
{
	check(FriendsViewModel && ConnectedFriendsWidget && DisconnectedFriendsWidget);

	FriendsViewModel->SetDataSource(DataSource);

	ConnectedFriendsWidget->SetListName(FString("Online"));
	ConnectedFriendsWidget->SetFriendsListValues(FriendsViewModel->GetFriendsByConnectionStatus(true));
	DisconnectedFriendsWidget->SetListName(FString("Offline"));
	DisconnectedFriendsWidget->SetFriendsListValues(FriendsViewModel->GetFriendsByConnectionStatus(false));

	GetWorld()->GetTimerManager().SetTimer(ConnectionSimulationTimer, this, &ThisClass::InitiallizeConnectionSimulation, 5.f, false);
	FriendsViewModel->OnFriendStatusChangedDelegate.AddDynamic(this, &ThisClass::OnChangeUserConnectionStatus);
}

void UFriendHUD::OnChangeUserConnectionStatus(FString& UserNickname, bool bIsConnected)
{
	if (bIsConnected) {
		SetConnectedFriend(UserNickname);
		FriendStatusNotification->ShowNotification(UserNickname);
		return;
	}
	SetDisconnectedFriend(UserNickname);
}

void UFriendHUD::SetConnectedFriend(const FString& UserNickname)
{
	UFriendModel* Friend = DisconnectedFriendsWidget->GetFriendByNickname(UserNickname);
	DisconnectedFriendsWidget->RemoveListItem(Friend);
	ConnectedFriendsWidget->AddListItem(Friend);
}

void UFriendHUD::SetDisconnectedFriend(const FString& UserNickname)
{
	UFriendModel* Friend = ConnectedFriendsWidget->GetFriendByNickname(UserNickname);
	ConnectedFriendsWidget->RemoveListItem(Friend);
	DisconnectedFriendsWidget->AddListItem(Friend);
}

void UFriendHUD::InitiallizeConnectionSimulation()
{
	FriendsViewModel->SetWorldContext(GetWorld());
}
