// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FriendsVM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddFriendList, UFriendModel*, FriendToAdd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoveFriendList, UFriendModel*, FriendToRemove);

class UUserServiceSubsystem;
class UFriendModel;
class UDataTable;
struct FUserDataRow;

/**
 * 
 */
UCLASS(BlueprintType)
class UMGEXERCISE_API UFriendsVM : public UMVVMViewModelBase
{
	GENERATED_BODY()	

	UFriendModel* MapUserDataToFriendModel(const FUserDataRow* User) const;	

	void OnFriendConnectionStatusChanged(FUserDataRow User);

protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter)
	TArray<UFriendModel*> FriendList;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Setter)
	FString ListName;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter = "GetIsOnlineList", Setter = "SetIsOnlineList")
	bool bIsOnlineList;

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnAddFriendList OnAddFriendListDelegate;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnRemoveFriendList OnRemoveFriendListDelegate;
	
	TArray<UFriendModel*> GetFriendList() const;	
	
	FString GetListName() const;
	
	bool GetIsOnlineList() const;
	
	void SetListName(const FString NewListName);
	
	void SetIsOnlineList(const bool IsOnlineList);

	UFUNCTION(BlueprintCallable)
	void InitiallizeList(UUserServiceSubsystem* UserService);	
	
	UFriendModel* AddFriend(const FUserDataRow FriendToAdd);
	
	UFriendModel* GetFriendByNickname(const FString& Nickname) const;	
	
	UFriendModel* RemoveFriend(const FString& Nickname);
};
