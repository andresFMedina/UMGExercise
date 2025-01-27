// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendListWidget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Models/FriendModel.h"
#include "ViewModels/FriendsVM.h"
#include "Services/UserServiceSubsystem.h"

void UFriendListWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFriendListWidget::AddListItem(UObject* FriendToAdd)
{	
	FriendsListView->AddItem(FriendToAdd);
}

void UFriendListWidget::RemoveListItem(UObject* FriendToRemove)
{	
	FriendsListView->RemoveItem(FriendToRemove);
}

bool UFriendListWidget::GetIsOnlineList() const
{
	return bIsOnlineList;
}

void UFriendListWidget::SetIsOnlineList(const bool IsOnlineList)
{
	bIsOnlineList = IsOnlineList;	
}
