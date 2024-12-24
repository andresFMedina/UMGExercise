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
	
	FString Nickname;
	int Level;
	FString ConnectionStatus;
	FString Description;

public:
	void MapUserToFriend(const FUserDataRow* User);
	FORCEINLINE FString GetNickname() const { return Nickname; }
	FORCEINLINE int GetLevel() const { return Level; }
	FORCEINLINE FString GetConnectionStatus() const { return ConnectionStatus; }
	FORCEINLINE FString GetDescription() const { return Description; }
};
