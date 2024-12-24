// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FriendsViewModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendStatusChanged, UObject*, FriendChanged);

class UUserService;
class UFriendModel;
struct FUserDataRow;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UFriendsViewModel : public UObject
{
	GENERATED_BODY()	

	UUserService* UserService;

	UFriendModel* MapUserDataToFriendModel(const FUserDataRow* User) const;

public:
	UFriendsViewModel();

	FOnFriendStatusChanged OnFriendStatusChangedDelegate;

	UFUNCTION(BlueprintCallable)
	UFriendModel* GetFriendByNickname(const FString& Nickname) const;

	UFUNCTION(BlueprintCallable)
	TArray<UObject*> GetFriendsByConnectionStatus(const bool bIsConnected) const;

	UFUNCTION(BlueprintCallable)
	void OnFriendConnectionStatusChanged(FUserDataRow User);
};
