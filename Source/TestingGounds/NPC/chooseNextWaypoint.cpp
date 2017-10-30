// Fill out your copyright notice in the Description page of Project Settings.

#include "chooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"


EBTNodeResult::Type UchooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	//getpatrolpoints
	auto controlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto patrolRoute = controlledPawn->FindComponentByClass<UPatrolRoute>();
	
	if (!ensure(patrolRoute)) { return EBTNodeResult::Failed; }

	auto patrolPoints = patrolRoute->getPatrolPoints();
	if (patrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points"));
		return EBTNodeResult::Failed;
	}


	//setnextwaypoint
	auto blackBoardComp = OwnerComp.GetBlackboardComponent();
	auto waypointIndex = blackBoardComp->GetValueAsInt(indexKey.SelectedKeyName);
	blackBoardComp->SetValueAsObject(nextWaypointKey.SelectedKeyName, patrolPoints[waypointIndex]);

	//cycleIndex
	auto nextWaypointIndex = (waypointIndex + 1) % patrolPoints.Num();
	blackBoardComp->SetValueAsInt(indexKey.SelectedKeyName, nextWaypointIndex);



	return EBTNodeResult::Succeeded;
}

