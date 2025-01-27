// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/UserServiceSubsystem.h"
#include "Engine/DataTable.h"
#include "Data/UserData.h"
#include "TimerManager.h"

void UUserServiceSubsystem::GenerateConnectionStatusChanges()
{
	/*Get all the users
	  Find a random index
	  Set IsConnected variable to its opposite
	  Send the user changed in the event
	  Start the timer
	  */
	TArray<FUserDataRow*> AllUsers;
	UsersDataTable->GetAllRows(TEXT("All Users"), AllUsers);
	if (!AllUsers.IsEmpty())
	{
		int RandomIndex = FMath::RandRange(0, AllUsers.Num() - 1);
		FUserDataRow* RandomUserToChange = AllUsers[RandomIndex];
		UE_LOG(LogTemp, Warning, TEXT("User changed: %s"), *RandomUserToChange->Nickname);
		RandomUserToChange->bIsConnected = !RandomUserToChange->bIsConnected;
		SetUserData(RandomUserToChange);

		OnUserChangeConnectionStatus.Broadcast(*RandomUserToChange);
		StartConnectionStatusChangesTimer();
	}
}

void UUserServiceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UUserServiceSubsystem::Deinitialize()
{
	if (UsersDataTable)
	{
		UsersDataTable->RemoveFromRoot();
		UsersDataTable = nullptr;
	}
}

void UUserServiceSubsystem::StartConnectionStatusChangesTimer()
{
	float EventTime = FMath::RandRange(10, 15);
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(ChangeConnectionTimer, this, &UUserServiceSubsystem::GenerateConnectionStatusChanges, EventTime, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("World is empty"));
	}
}

TArray<FUserDataRow*> UUserServiceSubsystem::GetFriends(const bool bIsConnected) const
{
	TArray<FUserDataRow*> UsersFound;
	UsersDataTable->GetAllRows(TEXT("All Users"), UsersFound);

	if (!UsersFound.IsEmpty())
	{
		UsersFound = UsersFound.FilterByPredicate([bIsConnected](FUserDataRow* User)
			{
				return User->bIsConnected == bIsConnected;
			});
	}

	return UsersFound;
}

void UUserServiceSubsystem::SetUserData(FUserDataRow* UserChanged)
{
	FUserDataRow* User = GetUserByNickname(UserChanged->Nickname);
	if (User)
	{
		User = UserChanged;

		UsersDataTable->Modify();
	}
}

FUserDataRow* UUserServiceSubsystem::GetUserByNickname(const FString& UserName) const
{
	return UsersDataTable->FindRow<FUserDataRow>(FName(UserName), TEXT("Get User"));
}

void UUserServiceSubsystem::SetDataSource(TSoftObjectPtr<UDataTable> DataSource)
{
	if (!DataSource.IsValid())
	{
		DataSource.LoadSynchronous();
	}
	UsersDataTable = DataSource.Get();
	check(UsersDataTable);
	UsersDataTable->AddToRoot();
	StartConnectionStatusChangesTimer();
}
