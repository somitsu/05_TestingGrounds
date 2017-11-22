// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	FVector location;
	float rotation;
	float scale;
};

class UActorPool;

UCLASS()
class TESTINGGOUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, 
						int minSpawn = 1, 
						int maxSpawn = 1, 
						float radius = 500, 
						float minScale = 1.0f, 
						float maxScale = 1.0f);
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void PlaceAIPawns(TSubclassOf<class APawn> ToSpawn,
						int minSpawn = 1,
						int maxSpawn = 1,
						float radius = 500);





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
		void setPool(UActorPool * inPool);

private:
	TArray<FSpawnPosition> randomSpawnPositions(int minSpawn, int maxSpawn, float radius, float minScale, float maxScale);
	bool findEmptyLocation(FVector& outLocation, float radius);
	void placeActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition spawnPosition);
	void placeAIPawn(TSubclassOf<APawn> ToSpawn, FSpawnPosition spawnPosition);
	bool canSpawnAtLocation(FVector location, float radius);
	void positionNavMeshBoundsVolume();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector minExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector maxExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
		FVector navigationBoundsOffset;


private:
	UActorPool * poolReference;
	AActor * nmbvReference = nullptr;


};
