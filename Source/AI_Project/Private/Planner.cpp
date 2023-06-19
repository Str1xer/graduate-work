#include "Planner.h"
#include "AIC_Agent.h"
#include "Agent.h"
#include "Harvest.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APlanner::APlanner()
{

	PrimaryActorTick.bCanEverTick = true;

}

AActor* FindClosestHarvest(TArray<AActor*> &Input, FVector MyLocation) {
	AActor* Output = NULL;
	float ClosestDistance = -1;
	for (AActor* Harvest : Input) 
	{
		if ((ClosestDistance == -1 || FVector::Dist((*Harvest).GetActorLocation(), MyLocation) < ClosestDistance) && !Cast<AHarvest>(Harvest)->IsExhausted && !Cast<AHarvest>(Harvest)->IsTaken)
		{
			ClosestDistance = FVector::Dist((*Harvest).GetActorLocation(), MyLocation);
			Output = Harvest;
		}
	}

	return Output;
}

void APlanner::BeginPlay()
{
	Super::BeginPlay();


	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHarvest::StaticClass(), foundHarvest);
	
}

void APlanner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlanner::Plan(AAIC_Agent *ref) 
{
	AActor* Harvest = FindClosestHarvest(foundHarvest, ref->Character->GetActorLocation());

	if (Harvest != NULL) 
	{
		SCR_Harvest::addActions(ref, Harvest);
	}
	else 
	{
		if (FVector::DistXY(ref->Character->GetActorLocation(), FVector(0, 0, 100.0)) < 300)
			ref->AddAction(MakeShareable(new Actions::Idle()));
		else
			ref->AddAction(MakeShareable(new Actions::MoveTo(FVector(0, 0, 100.0), 300.0)));
	}
		
	//ref->AddAction(new A_MoveTo(FVector(0, -2500, 0)));
}

void APlanner::EnemyFound(AActor *EmenyRef) 
{

	if (Enemies.Contains(EmenyRef))
		return;

	Enemies.Add(EmenyRef);
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, FString::Printf(TEXT("Enemy found")));
	for (AAIC_Agent* Agent : Agents)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Found Test")));
		Agent->RemovePlan();
		if (!Agent->Character->CanFight)
			Agent->AddAction(MakeShareable(new Actions::RunAway(EmenyRef)));
		else {
			SCR_Attack::addActions(Agent, EmenyRef);
		}
	}
}

bool APlanner::EnemyExists()
{
	return !Enemies.IsEmpty();
}

void APlanner::EnemyDead(AActor* EnemyRef)
{
	if (Enemies.Contains(EnemyRef))
		Enemies.Remove(EnemyRef);

	if (!Enemies.IsEmpty())
		return;

	for (AAIC_Agent* Agent : Agents)
	{
		if (!Agent->Character->CanFight)
			Agent->RemovePlan();
	}
}

//// Действие
//Action::Action()
//{
//	
//}
//
//bool Action::Execute(AAIC_Agent *ref)
//{
//	return true;
//}

//// Действие "Движение к цели"
//A_MoveTo::A_MoveTo(FVector Target)
//{
//	TargetLocation = Target;
//}
//
//A_MoveTo::A_MoveTo(AActor Target)
//{
//	TargetLocation = Target.GetActorLocation();
//}
//
//bool A_MoveTo::Execute(AAIC_Agent *ref)
//{
//	ref->MoveToLocation(TargetLocation, 100.0);
//	ref->Character->StateText->SetText(FText::FromString("Moving to Target"));
//	if (!ref->IsFollowingAPath())
//		return true;
//	return false;
//}
//
//// Действие "Сбор ресурсов"
//A_CollectHarvest::A_CollectHarvest(AHarvest* ref) {
//	HarvestRef = ref;
//	HarvestRef->IsTaken = true;
//}
//
//A_CollectHarvest::~A_CollectHarvest() {
//	HarvestRef->IsTaken = false;
//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("Deleted Task")));
//}
//
//bool A_CollectHarvest::Execute(AAIC_Agent* ref)
//{
//	ref->Character->StateText->SetText(FText::FromString("Collecting"));
//	if (HarvestRef->IsExhausted)
//		return true;
//	ref->Character->AddResource(HarvestRef->HarvestResources(ref->MyDeltaTime));
//
//	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, FString::Printf(TEXT("Collecting %f"), ref->Character->GetResourcesCount()));
//	return false;
//}
//
//// Действие "Атака противника"
//A_Attack::A_Attack(AActor* Target)
//{
//	Enemy = Target;
//}
//
//bool A_Attack::Execute(AAIC_Agent* ref)
//{
//	ref->Character->StateText->SetText(FText::FromString("Attack"));
//	ref->MoveToLocation(Enemy->GetActorLocation());
//	return false;
//}
//
//bool A_Idle::Execute(AAIC_Agent* ref)
//{
//	ref->Character->StateText->SetText(FText::FromString("Idle"));
//	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, FString::Printf(TEXT("%s: Idle %f"),*ref->Character->GetActorLabel(), ref->Character->GetResourcesCount()));
//	return false;
//}
//
//
//A_RunAway::A_RunAway(AActor* Target) {
//	Enemy = Target;
//}
//
//bool A_RunAway::Execute(AAIC_Agent* ref) 
//{	
//	ref->Character->StateText->SetText(FText::FromString("Run Away"));
//	ref->MoveToLocation(ref->Character->GetActorLocation() + 1000 * UKismetMathLibrary::Normal(ref->Character->GetActorLocation() - Enemy->GetActorLocation()));
//	return false;
//}
//
