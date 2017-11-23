// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"
#include "GameFramework/Pawn.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	minExtent = FVector(0, -2000, 0);
	maxExtent = FVector(4000, 2000, 0);
	navigationBoundsOffset = FVector(2000, 0, 0);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int minSpawn, int maxSpawn, float radius, float minScale, float maxScale)
{
	randomlyPlaceActors(ToSpawn, minSpawn, maxSpawn, radius, minScale, maxScale);
}
void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int minSpawn, int maxSpawn, float radius)
{
	randomlyPlaceActors(ToSpawn, minSpawn, maxSpawn, radius, 1.0f, 1.0f);
}
void ATile::placeActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition spawnPosition)
{
	AActor * spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (!spawned) { return; }
	spawned->SetActorRelativeLocation(spawnPosition.location);
	spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	spawned->SetActorRotation(FRotator(0, spawnPosition.rotation, 0));
	spawned->SetActorScale3D(FVector(spawnPosition.scale));
}
void ATile::placeActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition spawnPosition)
{
	FRotator rotation = FRotator(0, spawnPosition.rotation, 0);
	APawn * spawned = GetWorld()->SpawnActor<APawn>(ToSpawn, spawnPosition.location, rotation);
	if (!spawned) { return; }
	spawned->SetActorRelativeLocation(spawnPosition.location);
	spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	spawned->SetActorRotation(FRotator(0, spawnPosition.rotation, 0));
	spawned->SpawnDefaultController();
	spawned->Tags.Add(FName("Enemy"));
}

template<class T>
void ATile::randomlyPlaceActors(TSubclassOf<T> ToSpawn, int minSpawn, int maxSpawn, float radius, float minScale, float maxScale)
{

	int numToSpawn = FMath::RandRange(minSpawn, maxSpawn);
	for (int i = 0; i < numToSpawn; i++) 
	{
		FSpawnPosition spawnPosition;
		spawnPosition.scale = FMath::RandRange(minScale, maxScale);
		bool found = findEmptyLocation(spawnPosition.location, radius*spawnPosition.scale);
		if (found)
		{
			spawnPosition.rotation = FMath::RandRange(-180.0f, 180.0f);
			placeActor(ToSpawn, spawnPosition);
		}
	}
	return;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!poolReference) { return; }
	if (!nmbvReference) { return; }
	poolReference->returnActor(nmbvReference);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::setPool(UActorPool * inPool)
{
	poolReference = inPool;
	positionNavMeshBoundsVolume();
}



void ATile::positionNavMeshBoundsVolume()
{
	nmbvReference = poolReference->checkoutActor();
	if (!(nmbvReference)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Not enough actors in pool"), *GetName());
		return; 
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out: {%s}"), *GetName(), *nmbvReference->GetName());
	nmbvReference->SetActorLocation(GetActorLocation()+navigationBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
}

bool ATile::findEmptyLocation(FVector& outLocation, float radius)
{

	FBox bounds(minExtent, maxExtent);
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

