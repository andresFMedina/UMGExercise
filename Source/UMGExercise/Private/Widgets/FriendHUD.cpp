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
	check(FriendsViewModel);

	FriendsViewModel->SetDataSource(DataSource);

	ConnectedFriendsWidget->SetListName(FString("Online"));
	ConnectedFriendsWidget->SetFriendsListValues(FriendsViewModel->GetFriendsByConnectionStatus(true));
	DisconnectedFriendsWidget->SetListName(FString("Offline"));
	DisconnectedFriendsWidget->SetFriendsListValues(FriendsViewModel->GetFriendsByConnectionStatus(false));

	GetWorld()->GetTimerManager().SetTimer(ConnectionSimulationTimer, this, &ThisClass::InitiallizeConnectionSimulation, 5.f, false);
	FriendsViewModel->OnFriendStatusChangedDelegate.AddDynamic(this, &ThisClass::OnChangeUserConnectionStatus);
}
/* Find the reference with the nickname
	Determine which list will be the source and which one will be the destination
	Remove the Item from the source
	Add the Item to the destiny
	Show the notification is bIsConnected is true
*/
void UFriendHUD::OnChangeUserConnectionStatus(FString& UserNickname, bool bIsConnected)
{
	if (bIsConnected) {
		MoveListItem(DisconnectedFriendsWidget, ConnectedFriendsWidget, UserNickname, bIsConnected);
		FriendStatusNotification->ShowNotification(UserNickname);
		return;
	}
	MoveListItem(ConnectedFriendsWidget, DisconnectedFriendsWidget, UserNickname, bIsConnected);
}

void UFriendHUD::MoveListItem(UFriendListWidget* SourceList, UFriendListWidget* DestinyList, const FString& Nickname, const bool bIsConnected)
{
	UFriendModel* Friend = SourceList->GetFriendByNickname(Nickname);
	Friend->SetConnectionStatus(bIsConnected);
	SourceList->RemoveListItem(Friend);
	DestinyList->AddListItem(Friend);
}

void UFriendHUD::InitiallizeConnectionSimulation()
{
	FriendsViewModel->SetWorldContext(GetWorld());
}
