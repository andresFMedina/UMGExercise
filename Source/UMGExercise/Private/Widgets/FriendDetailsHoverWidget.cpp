// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendDetailsHoverWidget.h"
#include "Components/TextBlock.h"
#include "Models/FriendModel.h"

void UFriendDetailsHoverWidget::DisplayWidget(UFriendModel* Friend)
{
	NicknameLabel->SetText(FText::FromString(Friend->GetNickname()));
	DescriptionLabel->SetText(FText::FromString(Friend->GetDescription()));
	FString LevelText = FString::FromInt(Friend->GetLevel());
	LevelLabel->SetText(FText::FromString(LevelText));
	ConnectionStatusLabel->SetText(FText::FromString(Friend->GetConnectionStatus()));
}
