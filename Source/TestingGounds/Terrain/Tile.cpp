// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int minSpawn, int maxSpawn)
{
	FVector min(0, -2000, 0);
	FVector max(4000, 2000, 0);
	FBox bounds(min, max);
	int numToSpawn = FMath::RandRange(minSpawn, maxSpawn);

	for (int i = 0; i < numToSpawn; i++)
	{
		FVector spawnPoint = FMath::RandPointInBox(bounds);
		AActor * Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		//UE_LOG(LogTemp, Warning, TEXT("Spawn point = %s"), *spawnPoint.ToString());

		Spawned->SetActorRelativeLocation(spawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}


}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

