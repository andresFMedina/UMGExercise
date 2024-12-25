// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FriendModel.generated.h"

struct FUserDataRow;
/**
 * 
 */
UCLASS()
class UMGEXERCISE_API UFriendModel : public UObject
{
	GENERATED_BODY()
	
	UPROPERTY()	
	FString Nickname;
	UPROPERTY()
	int Level;
	UPROPERTY()
	FString ConnectionStatus;
	UPROPERTY()
	FString Description;

public:
	void MapUserToFriend(const FUserDataRow* User);
	UFUNCTION(BlueprintCallable)	
	FORCEINLINE FString GetNickname() const { return Nickname; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetLevel() const { return Level; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetConnectionStatus() const { return ConnectionStatus; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetDescription() const { return Description; }
};
