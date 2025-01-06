// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/UserService.h"
#include "Engine/DataTable.h"
#include "Data/UserData.h"
#include "TimerManager.h"

UUserService* UUserService::Instance = nullptr;

UUserService::UUserService()
{
	
}

void UUserService::StartConnectionStatusChangesTimer()
{
	float EventTime = FMath::RandRange(30, 90);
	/*if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(ChangeConnectionTimer, this, &UUserService::GenerateConnectionStatusChanges, EventTime, false);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("World is empty"));
	}*/
}

void UUserService::GenerateConnectionStatusChanges()
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
		RandomUserToChange->bIsConnected = !RandomUserToChange->bIsConnected;
		SetUserData(RandomUserToChange);

		OnUserChangeConnectionStatus.Broadcast(*RandomUserToChange);
		StartConnectionStatusChangesTimer();
	}
}

UUserService* UUserService::Get()
{
	if (!Instance)
	{
		Instance = NewObject<UUserService>();
	}
	return Instance;
}

TArray<FUserDataRow*> UUserService::GetFriends(const bool bIsConnected) const
{
	TArray<FUserDataRow*> UsersFound;
	UsersDataTable->GetAllRows(TEXT("All Users"), UsersFound);

	if (!UsersFound.IsEmpty()) {
		UsersFound = UsersFound.FilterByPredicate([bIsConnected](FUserDataRow* User)
			{
				return User->bIsConnected == bIsConnected;
			});
	}

	return UsersFound;
}

void UUserService::SetUserData(FUserDataRow* UserChanged)
{
	FUserDataRow* User = GetUserByNickname(UserChanged->Nickname);
	if (User)
	{
		User = UserChanged;

		UsersDataTable->Modify();
	}
}

FUserDataRow* UUserService::GetUserByNickname(const FString& UserName) const
{
	return UsersDataTable->FindRow<FUserDataRow>(FName(UserName), TEXT("Get User"));
}

void UUserService::SetDataSource(TSoftObjectPtr<UDataTable> DataSource)
{
	if (!DataSource.IsValid())
	{
		DataSource.LoadSynchronous();
	}	
	UsersDataTable = DataSource.Get();
	check(UsersDataTable);
}
