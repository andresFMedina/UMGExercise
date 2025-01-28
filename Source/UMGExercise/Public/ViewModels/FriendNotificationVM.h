// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendNotificationVM.generated.h"

class UUserServiceSubsystem;
struct FUserDataRow;
/**
 * 
 */
UCLASS(BlueprintType)
class UMGEXERCISE_API UFriendNotificationVM : public UMVVMViewModelBase
{
	GENERATED_BODY()

	void OnUserConnected(FUserDataRow UserConnected);

protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter)
	FString FriendNickname;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter="GetShowNotification", Setter="SetShowNotification")
	bool bShowNotification;

public:
	UFUNCTION(BlueprintCallable)
	void Initiallize(UUserServiceSubsystem* UserService);	
	
	FString GetFriendNickname() const;
	bool GetShowNotification() const;

	void SetFriendNickname(const FString Nickname);
	void SetShowNotification(const bool ShowNotification);
};
