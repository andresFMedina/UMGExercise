// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/UserService.h"
#include "Engine/DataTable.h"
#include "Data/UserData.h"
#include "TimerManager.h"

UUserService::UUserService()
{
	UsersDataTable = GetUsersDataTable();
}

UDataTable* UUserService::GetUsersDataTable() const
{
	//Get the users table, the Reference will be setted up in the ViewModel
	TSoftObjectPtr<UDataTable> UsersDataTableRef = TSoftObjectPtr<UDataTable>(FSoftObjectPath(TEXT("/Script/Engine.DataTable'/Game/DataTables/UsersDataTable.UsersDataTable'")));
	if (!UsersDataTableRef.IsValid())
	{
		UsersDataTableRef.LoadSynchronous();
	}
	return UsersDataTableRef.Get();	
}

void UUserService::StartConnectionStatusChangesTimer()
{
	float EventTime = FMath::RandRange(30, 90);
	GetWorld()->GetTimerManager().SetTimer(ChangeConnectionTimer, this, &UUserService::GenerateConnectionStatusChanges,EventTime, false);
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

		OnUserChangeConnectionStatus.Broadcast(RandomUserToChange);
		StartConnectionStatusChangesTimer();
	}
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
	return GetUsersDataTable()->FindRow<FUserDataRow>(FName(UserName), TEXT("Get User"));
}
