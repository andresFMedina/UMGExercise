// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/FriendsVM.h"
#include "Models/FriendModel.h"
#include "Services/UserServiceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Data/UserData.h"

UFriendModel* UFriendsVM::MapUserDataToFriendModel(const FUserDataRow* User) const
{
	if (User)
	{
		UFriendModel* FriendFound = NewObject<UFriendModel>();
		FriendFound->MapUserToFriend(User);
		return FriendFound;
	}
	return nullptr;
}

void UFriendsVM::OnFriendConnectionStatusChanged(FUserDataRow User)
{
	if (User.bIsConnected == bIsOnlineList) 
	{
		auto FriendToAdd = AddFriend(User);
		OnAddFriendListDelegate.Broadcast(FriendToAdd);

		return;
	}

	auto FriendToRemove = RemoveFriend(User.Nickname);
	OnRemoveFriendListDelegate.Broadcast(FriendToRemove);
}

TArray<UFriendModel*> UFriendsVM::GetFriendList() const
{
	return FriendList;
}

FString UFriendsVM::GetListName() const
{
	return ListName;
}

bool UFriendsVM::GetIsOnlineList() const
{
	return bIsOnlineList;
}

void UFriendsVM::SetListName(const FString NewListName)
{	
	UE_MVVM_SET_PROPERTY_VALUE(ListName, NewListName);
}

void UFriendsVM::SetIsOnlineList(const bool IsOnlineList)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(bIsOnlineList, IsOnlineList))
	{
		FString NewListName = bIsOnlineList ? "Online" : "Offline";
		SetListName(NewListName);
	}
}

void UFriendsVM::InitiallizeList(UUserServiceSubsystem* UserService)
{
	TArray<UFriendModel*> FriendsFound;
	UserService->OnUserChangeConnectionStatus.AddUObject(this, &ThisClass::OnFriendConnectionStatusChanged);
	TArray<FUserDataRow*> UsersFound = UserService->GetFriends(bIsOnlineList);

	if (UsersFound.Num() > 0)
	{
		for (FUserDataRow* User : UsersFound)
		{
			UFriendModel* Friend = NewObject<UFriendModel>();
			Friend->MapUserToFriend(User);
			FriendList.Add(Friend);
		}
	}

	FString NewListName = bIsOnlineList ? "Online" : "Offline";
	SetListName(NewListName);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(FriendList);

}

UFriendModel* UFriendsVM::AddFriend(FUserDataRow FriendToAdd)
{
	UFriendModel* Friend = MapUserDataToFriendModel(&FriendToAdd);
	if (Friend)
	{
		FriendList.Add(Friend);		
	}
	return Friend;
}

UFriendModel* UFriendsVM::GetFriendByNickname(const FString& Nickname) const
{
	return *FriendList.FindByPredicate([Nickname](UFriendModel* Friend)
	{
		return Nickname == Friend->GetNickname();
	});
}

UFriendModel* UFriendsVM::RemoveFriend(const FString& Nickname)
{
	auto FriendToRemove = GetFriendByNickname(Nickname);
	if (FriendToRemove)
	{
		FriendList.Remove(FriendToRemove);
	}
	return FriendToRemove;
}
