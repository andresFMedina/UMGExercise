// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FriendEntryWidget.h"
#include "Components/TextBlock.h"
#include "Models/FriendModel.h"
#include "Widgets/FriendDetailsHoverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

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
    /*
    * Get Mouse position, get ViewPort Size and Viewport Scale to show the widget in the cursor position
    * Set pivot to (0,0) and offset (-500, 0) to show always to the left
      Display the widget
    */
    check(FriendHoverClass);
    FriendHoverInstance = CreateWidget<UFriendDetailsHoverWidget>(GetWorld(), FriendHoverClass);
    if (FriendHoverInstance)
    {        
        FVector2D ScreenSpacePosition = InMouseEvent.GetScreenSpacePosition();

        FVector2D ViewportSize;
        GEngine->GameViewport->GetViewportSize(ViewportSize);
        
        const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

        FVector2D ViewportPosition;        
        ViewportPosition = ScreenSpacePosition / Scale;

        ViewportPosition.X = FMath::Clamp(ViewportPosition.X, 0.f, ViewportSize.X - 1.f);
        ViewportPosition.Y = FMath::Clamp(ViewportPosition.Y, 0.f, ViewportSize.Y - 1.f);        
        ViewportPosition.X -= 500.f;
        
        FriendHoverInstance->SetRenderTransformPivot(FVector2D(0.f, 0.f));
        FriendHoverInstance->SetPositionInViewport(ViewportPosition, false);
        FriendHoverInstance->SetDesiredSizeInViewport(FVector2D(400.f, 200.f));
        
        FriendHoverInstance->DisplayWidget(FriendItem);

        FriendHoverInstance->AddToViewport();
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
