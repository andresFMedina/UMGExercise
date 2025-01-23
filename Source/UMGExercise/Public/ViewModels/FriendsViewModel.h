// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FriendsViewModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFriendStatusChanged, FString&, FriendChanged, bool, bIsConnected);

//class UUserService;
class UUserServiceSubsystem;
class UFriendModel;
class UDataTable;
struct FUserDataRow;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UFriendsViewModel : public UObject
{
	GENERATED_BODY()

	UUserServiceSubsystem* UserService;

	UFriendModel* MapUserDataToFriendModel(const FUserDataRow* User) const;

public:
	UFriendsViewModel();

	FOnFriendStatusChanged OnFriendStatusChangedDelegate;

	UFUNCTION(BlueprintCallable)
	UFriendModel* GetFriendByNickname(const FString& Nickname) const;

	UFUNCTION(BlueprintCallable)
	TArray<UFriendModel*> GetFriendsByConnectionStatus(const bool bIsConnected) const;

	void OnFriendConnectionStatusChanged(FUserDataRow User);

	UFUNCTION(BlueprintCallable)
	void SetDataSource(const TSoftObjectPtr<UDataTable>& DataSource);

	void SetWorldContext(UWorld* WorldContext);

};
