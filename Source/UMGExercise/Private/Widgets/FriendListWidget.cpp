// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendListWidget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"

void UFriendListWidget::SetFriendsListValues(const TArray<UObject*> Friends)
{
	FriendsListView->SetListItems(Friends);
}

void UFriendListWidget::SetListName(const FString& ListName)
{
	ListNameLabel->SetText(FText::FromString(ListName));
}

void UFriendListWidget::AddListItem(UObject* FriendToAdd)
{
	FriendsListView->AddItem(FriendToAdd);
}

void UFriendListWidget::RemoveListItem(UObject* FriendToRemove)
{
	FriendsListView->RemoveItem(FriendToRemove);
}
