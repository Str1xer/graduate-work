#include "Actions.h"
#include "AIC_Agent.h"
#include "Agent.h"
#include "Harvest.h"
#include "Enemy.h"
#include "AIC_Enemy.h"
#include "Planner.h"
#include "I_Storage.h"
#include "Kismet/KismetMathLibrary.h"


Action::Action()
{

}

bool Action::Execute(AAIC_Agent* ref)
{
	return true;
}

// Namespace Classes

// Move to target action
Actions::MoveTo::MoveTo(const FVector Target, const float inputRadius)
{
	TargetLocation = Target;
	Radius = inputRadius;
}

Actions::MoveTo::MoveTo(AActor* Target)
{
	TargetLocation = Target->GetActorLocation();
}

bool Actions::MoveTo::Execute(AAIC_Agent* ref)
{
	//Anim State
	ref->Character->CurrentState = EAgentState::AS_Walk;

	//Debug State Above Agent
	//ref->Character->StateText->SetText(FText::FromString("Moving to Target"));

	ref->MoveToLocation(TargetLocation, Radius);
	//if (FVector::DistXY(ref->Character->GetActorLocation(), TargetLocation) < Radius)
	if (!ref->IsFollowingAPath())
		return true;
	return false;
}

//Collecting harvest action
Actions::CollectHarvest::CollectHarvest(AHarvest* ref) {
	HarvestRef = ref;
	HarvestRef->IsTaken = true;
}

Actions::CollectHarvest::~CollectHarvest() {
	HarvestRef->IsTaken = false;
	HarvestRef->Resources = 3;
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Deleted Task")));
}

bool Actions::CollectHarvest::Execute(AAIC_Agent* ref)
{
	//Debug State Above Agent
	//ref->Character->StateText->SetText(FText::FromString("Collecting"));

	//Anim State
	ref->Character->CurrentState = EAgentState::AS_Collect;

	if (HarvestRef->IsExhausted) {
		//ref->Character->AddResource(HarvestRef->HarvestResources(ref->MyDeltaTime));
		ref->Character->ResourcesCount = 1;
		ref->Character->ResourcesTime = 1.5;
		return true;
	}

	HarvestRef->HarvestResources(ref->MyDeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, FString::Printf(TEXT("Collecting %f"), ref->Character->GetResourcesCount()));
	return false;
}

//Attack action
Actions::Attack::Attack(AActor* Target)
{
	Enemy = Cast<AEnemy>(Target);
}

bool Actions::Attack::Execute(AAIC_Agent* ref)
{
	//Debug State Above Agent
	//ref->Character->StateText->SetText(FText::FromString("Attack"));
	
	//Anim State
	ref->Character->CurrentState = EAgentState::AS_Attack;
	Cast<AAIC_Enemy>(Enemy->GetController())->StopMovement();
	Cast<AAIC_Enemy>(Enemy->GetController())->UnderAttack = true;

	ref->MoveToLocation(Enemy->GetActorLocation());
	if (CurrentAS == EAttackState::AS_CanAttack)
	{
		if (FVector::DistXY(ref->Character->GetActorLocation(), Enemy->GetActorLocation()) < 200)
		{
			ref->Character->Punch();
			Enemy->TakingDamage(10);
			CurrentAS = EAttackState::AS_Waiting;
			SleepTimer = 0;
		}		
	}
	else {
		AttackReloading(ref->MyDeltaTime);
	}
	
	if (Enemy->IsActorBeingDestroyed() || Enemy->IsDead())
		ref->Character->Planner->EnemyDead(Enemy);
		
	return Enemy->IsDead();
}

void Actions::Attack::AttackReloading(float time) {
	SleepTimer += time;
	if (SleepTimer > 1)
		CurrentAS = EAttackState::AS_CanAttack;
}

//Idle action
bool Actions::Idle::Execute(AAIC_Agent* ref)
{
	//Debug State Above Agent
	//ref->Character->StateText->SetText(FText::FromString("Idle"));

	//Anim State
	ref->Character->CurrentState = EAgentState::AS_Walk;

	//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, FString::Printf(TEXT("%s: Idle %f"), *ref->Character->GetActorLabel(), ref->Character->GetResourcesCount()));
	return true;
}

//Running away action
Actions::RunAway::RunAway(AActor* Target) {
	Enemy = Target;
}

bool Actions::RunAway::Execute(AAIC_Agent* ref)
{
	//Debug State Above Agent
	//ref->Character->StateText->SetText(FText::FromString("Run Away"));

	//Anim State
	ref->Character->CurrentState = EAgentState::AS_Walk;

	ref->MoveToLocation(FVector(0, 0, 0));
	//ref->MoveToLocation(ref->Character->GetActorLocation() + 1000 * UKismetMathLibrary::Normal(ref->Character->GetActorLocation() - Enemy->GetActorLocation()));
	return !ref->Character->Planner->EnemyExists();
	//return false;
}

Actions::Unloading::Unloading() {

}

bool Actions::Unloading::Execute(AAIC_Agent *ref) 
{
	//Debug State Above Agent
	//ref->Character->StateText->SetText(FText::FromString("Unloading"));

	//Anim State
	ref->Character->CurrentState = EAgentState::AS_Collect;

	ref->Character->UnloadingResourcesTime(ref->MyDeltaTime);
	if (ref->Character->ResourcesTime <= 0) {
		ref->Character->ResourcesCount = 0;

		II_Storage* TheInterface = Cast<II_Storage>(ref->Character->Storage);
		TheInterface->Execute_AddResource(ref->Character->Storage, 1);
		return true;
	}
		
	return false;
}

Actions::Arming::Arming(bool NewState) 
{
	Taking = NewState;
}

bool Actions::Arming::Execute(AAIC_Agent* ref)
{
	//Anim State
	ref->Character->CurrentState = EAgentState::AS_Walk;

	if (Taking)
		ref->Character->Sword->SetVisibility(true);
	else 
		ref->Character->Sword->SetVisibility(false);
	return true;
}

