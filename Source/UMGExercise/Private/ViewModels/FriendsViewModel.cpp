// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/FriendsViewModel.h"
#include"Data/UserData.h"
#include "Models/FriendModel.h"
#include "Services/UserService.h"
#include "Engine/DataTable.h"

UFriendModel* UFriendsViewModel::MapUserDataToFriendModel(const FUserDataRow* User) const
{
	if (User)
	{
		UFriendModel* FriendFound = NewObject<UFriendModel>();
		FriendFound->MapUserToFriend(User);
		return FriendFound;
	}
	return nullptr;
}

UFriendsViewModel::UFriendsViewModel()
{
	UserService = UUserService::Get();
}

UFriendModel* UFriendsViewModel::GetFriendByNickname(const FString& Nickname) const
{
	FUserDataRow* UserFound = UserService->GetUserByNickname(Nickname);
	return MapUserDataToFriendModel(UserFound);
}

TArray<UFriendModel*> UFriendsViewModel::GetFriendsByConnectionStatus(const bool bIsConnected) const
{
	TArray<UFriendModel*> FriendsFound;
	TArray<FUserDataRow*> UsersFound = UserService->GetFriends(bIsConnected);

	if (UsersFound.Num() > 0)
	{
		for (FUserDataRow* User : UsersFound)
		{
			UFriendModel* Friend = NewObject<UFriendModel>();
			Friend->MapUserToFriend(User);			
			FriendsFound.Add(Friend);
		}
	}

	return FriendsFound;
}

UFUNCTION()
void UFriendsViewModel::OnFriendConnectionStatusChanged(FUserDataRow User)
{	
	OnFriendStatusChangedDelegate.Broadcast(User.Nickname, User.bIsConnected);
}

void UFriendsViewModel::SetDataSource(const TSoftObjectPtr<UDataTable>& DataSource)
{
	UserService->SetDataSource(DataSource);	
}

void UFriendsViewModel::SetWorldContext(UWorld* WorldContext)
{
	UserService->SetWorldContext(WorldContext);
	UserService->OnUserChangeConnectionStatus.AddUObject(this, &ThisClass::OnFriendConnectionStatusChanged);
	UserService->StartConnectionStatusChangesTimer();
}
