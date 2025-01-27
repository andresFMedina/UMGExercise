// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UserServiceSubsystem.generated.h"

class UDataTable;
struct FUserDataRow;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUserChangeConnectionStatusDelegate, FUserDataRow /*UserChanged*/);
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UUserServiceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UDataTable* UsersDataTable;

	FTimerHandle ChangeConnectionTimer;

	void GenerateConnectionStatusChanges();
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void StartConnectionStatusChangesTimer();

	TArray<FUserDataRow*> GetFriends(const bool bIsConnected) const;
	void SetUserData(FUserDataRow* UserChanged);
	FUserDataRow* GetUserByNickname(const FString& UserName) const;

	UFUNCTION(BlueprintCallable)
	void SetDataSource(TSoftObjectPtr<UDataTable> DataSource);

	FOnUserChangeConnectionStatusDelegate OnUserChangeConnectionStatus;

};
