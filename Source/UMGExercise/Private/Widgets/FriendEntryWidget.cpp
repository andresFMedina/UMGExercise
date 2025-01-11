// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendEntryWidget.h"
#include "Components/TextBlock.h"
#include "Models/FriendModel.h"
#include "Widgets/FriendDetailsHoverWidget.h"

void UFriendEntryWidget::NativeOnListItemObjectSet(UObject* FriendModelItem)
{
	FriendItem = Cast<UFriendModel>(FriendModelItem);
	check(FriendItem);

	NicknameLabel->SetText(FText::FromString(FriendItem->GetNickname()));
	LevelLabel->SetText(FText::FromString(FString::FromInt(FriendItem->GetLevel())));
	ConnectionStatusLabel->SetText(FText::FromString(FriendItem->GetConnectionStatus()));
}

void UFriendEntryWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	check(FriendHoverClass);

	FriendHoverInstance = CreateWidget<UFriendDetailsHoverWidget>(GetWorld(), FriendHoverClass);
	if (FriendHoverInstance)
	{
		FriendHoverInstance->AddToViewport();
		FVector2D CursorPosition = InMouseEvent.GetScreenSpacePosition();
		FriendHoverInstance->SetPositionInViewport(CursorPosition, false);
		FriendHoverInstance->DisplayWidget(FriendItem);
	}
}

void UFriendEntryWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (FriendHoverInstance)
	{
		FriendHoverInstance->RemoveFromParent();
		FriendHoverInstance = nullptr;
	}
}
