// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendStatusNotificationWidget.h"
#include "Components/TextBlock.h"

void UFriendStatusNotificationWidget::ShowNotification(const FString& Nickname)
{	
	MessageText->SetText(FText::FromString(Nickname + " has connected!"));
	PlayAnimation(ShowNotificationAnimation);
	GetWorld()->GetTimerManager().SetTimer(HideNotificationTimer, this, &ThisClass::HideNotification, TimeToHideNotification, false);
}

void UFriendStatusNotificationWidget::HideNotification()
{
	PlayAnimation(HideNotificationAnimation);
}
