// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	navMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));

}


void AInfiniteTerrainGameMode::populateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> nmbvIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (nmbvIterator)
	{
		addToPool(*nmbvIterator);
		++nmbvIterator;
	}
}

void AInfiniteTerrainGameMode::addToPool(ANavMeshBoundsVolume * volumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("NMBV: %s"), *volumeToAdd->GetName());
}
