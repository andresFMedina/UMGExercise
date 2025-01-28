// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/FriendNotificationVM.h"
#include "Services/UserServiceSubsystem.h"
#include "Data/UserData.h"

void UFriendNotificationVM::OnUserConnected(FUserDataRow UserConnected)
{
	if (!UserConnected.bIsConnected) return;

	SetFriendNickname(UserConnected.Nickname);
	SetShowNotification(true);
}

void UFriendNotificationVM::Initiallize(UUserServiceSubsystem* UserService)
{
	UserService->OnUserChangeConnectionStatus.AddUObject(this, &ThisClass::OnUserConnected);
}

FString UFriendNotificationVM::GetFriendNickname() const
{
	return FriendNickname;
}

bool UFriendNotificationVM::GetShowNotification() const
{
	return bShowNotification;
}

void UFriendNotificationVM::SetFriendNickname(const FString Nickname)
{
	UE_MVVM_SET_PROPERTY_VALUE(FriendNickname, Nickname);
}

void UFriendNotificationVM::SetShowNotification(const bool ShowNotification)
{
	UE_MVVM_SET_PROPERTY_VALUE(bShowNotification, ShowNotification);
}
