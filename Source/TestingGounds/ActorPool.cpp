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

AActor * UActorPool::checkoutActor()
{
	if (pool.Num() <= 0) { return nullptr; }
	AActor * actorToCheckout = pool.Pop();
	return actorToCheckout;
}

void UActorPool::returnActor(AActor * actorToReturn)
{
	addActor(actorToReturn);
}

void UActorPool::addActor(AActor * actorToAdd)
{
	pool.Push(actorToAdd);
}
