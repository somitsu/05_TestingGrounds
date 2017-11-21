// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor * UActorPool::checkOutActor()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s]Checkout"), *GetName())
	return nullptr;
}

void UActorPool::returnActor(AActor * actorToReturn)
{
	if (!actorToReturn)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]Returned null"), *GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[%s]Returned: {%s}"), *GetName(), * actorToReturn->GetName());
}

void UActorPool::addActor(AActor * actorToAdd)
{
	if (!actorToAdd)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]Added null"), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s]Added: {%s}"), *GetName(), *actorToAdd->GetName());
}
