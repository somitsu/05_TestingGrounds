// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "chooseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGOUNDS_API UchooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
//////////////////////////////////////Methods//////////////////////////////////////	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


protected:


private:



//////////////////////////////////////Properties//////////////////////////////////////	
public:

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector indexKey;

	//UPROPERTY(EditAnywhere, Category = "Blackboard")
	


private:


	
	
};
