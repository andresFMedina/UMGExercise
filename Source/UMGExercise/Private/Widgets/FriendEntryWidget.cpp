// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendEntryWidget.h"
#include "Components/TextBlock.h"
#include "Models/FriendModel.h"

void UFriendEntryWidget::NativeOnListItemObjectSet(UObject* FriendModelItem)
{
	FriendItem = Cast<UFriendModel>(FriendModelItem);
	check(FriendItem);

	NicknameLabel->SetText(FText::FromString(FriendItem->GetNickname()));
	LevelLabel->SetText(FText::FromString(FString::FromInt(FriendItem->GetLevel())));
	ConnectionStatusLabel->SetText(FText::FromString(FriendItem->GetConnectionStatus()));
}
