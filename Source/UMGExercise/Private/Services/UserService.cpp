// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/UserService.h"
#include "Engine/DataTable.h"
#include "TimerManager.h"

UUserService* UUserService::Instance = nullptr;

UUserService::UUserService()
{

}

void UUserService::StartConnectionStatusChangesTimer()
{
	float EventTime = FMath::RandRange(10, 15);
	if (WorldContext)
	{
		WorldContext->GetTimerManager().SetTimer(ChangeConnectionTimer, Instance, &UUserService::GenerateConnectionStatusChanges, EventTime, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("World is empty"));
	}
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
		UE_LOG(LogTemp, Warning, TEXT("User changed: %s"), *RandomUserToChange->Nickname);
		RandomUserToChange->bIsConnected = !RandomUserToChange->bIsConnected;
		SetUserData(RandomUserToChange);

		OnUserChangeConnectionStatus.Broadcast(*RandomUserToChange);
		StartConnectionStatusChangesTimer();
	}
}

void UUserService::BeginDestroy()
{
	Super::BeginDestroy();

	if (UsersDataTable)
	{
		UsersDataTable->RemoveFromRoot();
		UsersDataTable = nullptr;
	}

	if (Instance) 
	{
		Instance->RemoveFromRoot();
		Instance = nullptr;
	}
}

UUserService* UUserService::Get()
{
	if (!Instance)
	{
		Instance = NewObject<UUserService>();
		Instance->AddToRoot();
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
	UsersDataTable->AddToRoot();
}
