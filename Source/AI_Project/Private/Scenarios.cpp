#include "Scenarios.h"
#include "AIC_Agent.h"
#include "Harvest.h"
#include "Actions.h"
#include "Agent.h"

void SCR_Harvest::addActions(AAIC_Agent* ref, AActor* Harvest) 
{
	ref->AddAction(MakeShareable(new Actions::MoveTo(Harvest->GetActorLocation())));
	ref->AddAction(MakeShareable(new Actions::CollectHarvest(Cast<AHarvest>(Harvest))));
	ref->AddAction(MakeShareable(new Actions::MoveTo(FVector(0,0,100.0), 300.0)));
	ref->AddAction(MakeShareable(new Actions::Unloading()));
}

bool SCR_Harvest::validate() 
{
	return true;
}

void SCR_Attack::addActions(AAIC_Agent* ref, AActor* Enemy)
{
	ref->AddAction(MakeShareable(new Actions::MoveTo(FVector(-100.0, -880, 100.0), 150.0)));
	ref->AddAction(MakeShareable(new Actions::Arming(true)));
	ref->AddAction(MakeShareable(new Actions::MoveTo(Enemy->GetActorLocation())));
	ref->AddAction(MakeShareable(new Actions::Attack(Enemy)));
	ref->AddAction(MakeShareable(new Actions::MoveTo(FVector(-100.0, -880, 100.0), 150.0)));
	ref->AddAction(MakeShareable(new Actions::Arming(false)));
	if (ref->Character->ResourcesCount != 0)
	{
		ref->AddAction(MakeShareable(new Actions::MoveTo(FVector(0, 0, 100.0), 300.0)));
		ref->AddAction(MakeShareable(new Actions::Unloading()));
	}
		
	//ref->AddAction(MakeShareable(new Actions::MoveTo(FVector(0, 0, 0), 300.0)));
}

bool SCR_Attack::validate()
{
	return true;
}