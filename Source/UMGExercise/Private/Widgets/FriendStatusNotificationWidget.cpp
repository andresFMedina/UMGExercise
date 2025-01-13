// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendStatusNotificationWidget.h"
#include "Components/TextBlock.h"

void UFriendStatusNotificationWidget::ShowNotification(const FString& Nickname)
{
	SetVisibility(ESlateVisibility::Visible);
	MessageText->SetText(FText::FromString(Nickname + " has connected!"));
	GetWorld()->GetTimerManager().SetTimer(HideNotificationTimer, this, &ThisClass::HideNotification, TimeToHideNotification, false);
}

void UFriendStatusNotificationWidget::HideNotification()
{
	SetVisibility(ESlateVisibility::Hidden);
}
