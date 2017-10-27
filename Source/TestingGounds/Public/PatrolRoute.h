// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGOUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

//////////////////////////////////////Methods//////////////////////////////////////	
public:
	TArray<AActor*> getPatrolPoints() const;


protected:


private:

//////////////////////////////////////Members//////////////////////////////////////	
public:


protected:


private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<AActor*> PatrolPoints;

		
	
};
