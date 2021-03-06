// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGoundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGOUNDS_API AInfiniteTerrainGameMode : public ATestingGoundsGameMode
{
	GENERATED_BODY()
	AInfiniteTerrainGameMode();

public:
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
		void populateBoundsVolumePool();

private:
	void addToPool(class ANavMeshBoundsVolume * volumeToAdd);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
		class UActorPool * navMeshBoundsVolumePool;
};
