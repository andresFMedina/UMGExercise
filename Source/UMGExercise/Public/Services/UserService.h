// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserService.generated.h"

struct FUserDataRow;
class UDataTable;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUserChangeConnectionStatusDelegate, FUserDataRow /*UserChanged*/);
/**
 * 
 */

UCLASS()
class UMGEXERCISE_API UUserService : public UObject
{
	GENERATED_BODY()
	UUserService();

	static UUserService* Instance;

	UDataTable* UsersDataTable;

	FTimerHandle ChangeConnectionTimer;	

	UDataTable* GetUsersDataTable() const;	

	void GenerateConnectionStatusChanges();
	

public:
	static UUserService* Get();

	void StartConnectionStatusChangesTimer();

	TArray<FUserDataRow*> GetFriends(const bool bIsConnected) const;
	void SetUserData(FUserDataRow* UserChanged);
	FUserDataRow* GetUserByNickname(const FString& UserName) const;

	FOnUserChangeConnectionStatusDelegate OnUserChangeConnectionStatus;
};
