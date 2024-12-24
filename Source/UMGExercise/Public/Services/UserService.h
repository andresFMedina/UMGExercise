// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserService.generated.h"

struct FUserDataRow;
class UDataTable;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUserChangeConnectionStatus, FUserDataRow* /*UserChanged*/);
/**
 * 
 */

UCLASS()
class UMGEXERCISE_API UUserService : public UObject
{
	GENERATED_BODY()
	UUserService();

	UDataTable* UsersDataTable;

	FTimerHandle ChangeConnectionTimer;

	FOnUserChangeConnectionStatus OnUserChangeConnectionStatus;

	UDataTable* GetUsersDataTable() const;

	void StartConnectionStatusChangesTimer();

	void GenerateConnectionStatusChanges();
	
public:
	TArray<FUserDataRow*> GetFriends(const bool bIsConnected) const;
	void SetUserData(FUserDataRow* UserChanged);
	FUserDataRow* GetUserByNickname(const FString& UserName) const;
};
