// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendListWidget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Models/FriendModel.h"

void UFriendListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CollapseButton->OnClicked.AddDynamic(this, &UFriendListWidget::OnCollapseButtonClick);	
}

void UFriendListWidget::SetFriendsListValues(const TArray<UFriendModel*>& Friends)
{
	FriendsList = Friends;
	FriendsListView->SetListItems(Friends);
}

void UFriendListWidget::SetListName(const FString& ListName)
{
	ListNameLabel->SetText(FText::FromString(ListName));
}

UFriendModel* UFriendListWidget::GetFriendByNickname(const FString& NicknameToLook) const
{
	return *FriendsList.FindByPredicate([NicknameToLook](UFriendModel* Friend)
		{
			return NicknameToLook == Friend->GetNickname();
		});
}

void UFriendListWidget::AddListItem(UFriendModel* FriendToAdd)
{
	FriendsList.Add(FriendToAdd);
	FriendsListView->AddItem(FriendToAdd);
}

void UFriendListWidget::RemoveListItem(UFriendModel* FriendToRemove)
{
	FriendsList.Remove(FriendToRemove);
	FriendsListView->RemoveItem(FriendToRemove);
}

void UFriendListWidget::CollapseButtonAction()
{	
	ESlateVisibility CurrentVisibility = FriendsListView->GetVisibility();
	FWidgetTransform Transform;
	Transform.Angle = 180.f;
	
	switch (CurrentVisibility)
	{
	case ESlateVisibility::Visible:		
		PlayAnimation(CollapseListAnimation);
		break;
	case ESlateVisibility::Collapsed:
	default:
		PlayAnimation(ExpandListAnimation);
		Transform.Angle = 0.f;
		break;
	}

	CollapseButtonImage->SetRenderTransform(Transform);
	CollapseButtonImage->SetRenderTransformPivot(FVector2D(0.5f, 0.5f));
}

void UFriendListWidget::OnCollapseButtonClick()
{
	CollapseButtonAction();	
}
