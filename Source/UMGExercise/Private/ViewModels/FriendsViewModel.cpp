// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/FriendsViewModel.h"
#include"Data/UserData.h"
#include "Models/FriendModel.h"
#include "Services/UserService.h"

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
	//UserService->StartConnectionStatusChangesTimer();
	UserService->OnUserChangeConnectionStatus.AddUObject(this, &UFriendsViewModel::OnFriendConnectionStatusChanged);
}

UFriendModel* UFriendsViewModel::GetFriendByNickname(const FString& Nickname) const
{
	FUserDataRow* UserFound = UserService->GetUserByNickname(Nickname);	
	return MapUserDataToFriendModel(UserFound);
}

TArray<UObject*> UFriendsViewModel::GetFriendsByConnectionStatus(const bool bIsConnected) const
{
	TArray<UObject*> FriendsFound;
	TArray<FUserDataRow*> UsersFound = UserService->GetFriends(bIsConnected);

	if (UsersFound.Num() > 0)
	{
		for (FUserDataRow* User : UsersFound) 
		{
			UFriendModel* Friend = NewObject<UFriendModel>();
			Friend->MapUserToFriend(User);
			UObject* FriendMapped = Cast<UObject>(Friend);
			FriendsFound.Add(FriendMapped);
		}
	}

	return FriendsFound;
}

void UFriendsViewModel::OnFriendConnectionStatusChanged(FUserDataRow User)
{
	UFriendModel* FriendChanged = NewObject<UFriendModel>();
	FriendChanged->MapUserToFriend(&User);
	UObject* FriendToSend = Cast<UObject>(FriendChanged);
	OnFriendStatusChangedDelegate.Broadcast(FriendToSend, User.bIsConnected);
}
