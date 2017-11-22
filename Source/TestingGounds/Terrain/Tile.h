// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

UCLASS()
class TESTINGGOUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	UFUNCTION(BlueprintCallable, Category = "Tile")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, 
						int minSpawn = 1, 
						int maxSpawn = 1, 
						float radius = 500, 
						float minScale = 1.0f, 
						float maxScale = 1.0f);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
		void setPool(UActorPool * inPool);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector minExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector maxExtent;


private:
	bool findEmptyLocation(FVector& outLocation, float radius);
	void placeActor(TSubclassOf<AActor> ToSpawn, FVector spawnPoint, float rotation, float scale);

	bool canSpawnAtLocation(FVector location, float radius);
	void positionNavMeshBoundsVolume();
	
	UActorPool * poolReference;
	AActor * nmbvReference = nullptr;


};
