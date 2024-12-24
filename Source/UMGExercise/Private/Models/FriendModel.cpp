// Fill out your copyright notice in the Description page of Project Settings.


#include "Models/FriendModel.h"
#include "Data/UserData.h"

void UFriendModel::MapUserToFriend(const FUserDataRow* User)
{
	Nickname = User->Nickname;
	Level = User->Level;
	ConnectionStatus = User->bIsConnected ? FString("Online") : FString("Offline");
	Description = User->Description;
}
