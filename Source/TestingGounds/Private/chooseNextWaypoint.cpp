// Fill out your copyright notice in the Description page of Project Settings.

#include "chooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"


EBTNodeResult::Type UchooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	//getpatrolpoints
	auto aiController = OwnerComp.GetAIOwner();
	auto controlledPawn = aiController->GetPawn();
	auto patrollingGuard = Cast<APatrollingGuard>(controlledPawn);

	patrolPoints = patrollingGuard->patrolPointsCpp;


	//setnextwaypoint
	auto blackBoardComp = OwnerComp.GetBlackboardComponent();
	auto waypointIndex = blackBoardComp->GetValueAsInt(indexKey.SelectedKeyName);
	blackBoardComp->SetValueAsObject(nextWaypointKey.SelectedKeyName, patrolPoints[waypointIndex]);

	//cycleIndex
	auto nextWaypointIndex = (waypointIndex + 1) % patrolPoints.Num();
	blackBoardComp->SetValueAsInt(indexKey.SelectedKeyName, nextWaypointIndex);



	return EBTNodeResult::Succeeded;
}

