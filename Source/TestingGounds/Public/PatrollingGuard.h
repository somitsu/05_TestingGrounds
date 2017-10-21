// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGOUNDS_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
		//////////////////////////////////////Methods//////////////////////////////////////	
public:


protected:


private:



	//////////////////////////////////////Properties//////////////////////////////////////	
public:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<AActor * > patrolPointsCpp;
protected:




private:

	
	
};
