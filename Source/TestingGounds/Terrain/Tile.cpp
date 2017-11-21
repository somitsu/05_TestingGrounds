// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int minSpawn, int maxSpawn, float radius, float minScale, float maxScale)
{

	int numToSpawn = FMath::RandRange(minSpawn, maxSpawn);
	
	for (int i = 0; i < numToSpawn; i++)
	{
		FVector spawnPoint;
		float randomScale = 1.0f;
		randomScale = FMath::RandRange(minScale, maxScale);

		bool found = findEmptyLocation(spawnPoint, radius*randomScale);
		if (found)
		{
			float randomRotation = FMath::RandRange(-180.0f, 180.0f);
			placeActor(ToSpawn, spawnPoint, randomRotation, randomScale);
		}
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

void ATile::setPool(UActorPool * pool)
{
	UE_LOG(LogTemp, Warning, TEXT("getting set"));
	poolReference = pool;
}

bool ATile::findEmptyLocation(FVector& outLocation, float radius)
{
	FVector min(0, -2000, 0);
	FVector max(4000, 2000, 0);
	FBox bounds(min, max);
	const int MAX_ATTEMPTS = 20;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector candidatePoint = FMath::RandPointInBox(bounds);
		if (canSpawnAtLocation(candidatePoint, radius))
		{
			outLocation = candidatePoint;
			return true;
		}
	}
	return false;
}

void ATile::placeActor(TSubclassOf<AActor> ToSpawn, FVector spawnPoint, float rotation, float scale)
{
	AActor * Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(spawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, rotation, 0));
	Spawned->SetActorScale3D(FVector(scale));
}

bool ATile::canSpawnAtLocation(FVector location, float radius)
{
	FHitResult hitResult;
	FVector globalLocation = ActorToWorld().TransformPosition(location);

	bool hasHit = GetWorld()->SweepSingleByChannel(
		hitResult,
		globalLocation,
		globalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(radius)
		);
	FColor resultColor = hasHit ? FColor::Red : FColor::Green;
	//DrawDebugCapsule(GetWorld(), globalLocation, 0, radius, FQuat::Identity, resultColor, true, 100);
	return !hasHit;
}

