#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scenarios.h"
#include "Actions.h"
#include "Planner.generated.h"

class AAIC_Agent;
class AAgent;
class AHarvest;
class AEnemy;

UCLASS()
class AI_PROJECT_API APlanner : public AActor
{
	GENERATED_BODY()
	
public:	
	APlanner();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AAIC_Agent*> Agents = TArray<AAIC_Agent*>();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* TestPlant;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void Plan(AAIC_Agent* ref);
	bool EnemyExists();
	void EnemyFound(AActor* EmenyRef);
	void EnemyDead(AActor* EnemyRef);
private:
	TArray<AActor*> foundHarvest;
	TArray<AActor*> Enemies;
};

//class Action
//{
//public:
//	Action();
//	//virtual ~Action() {};
//	virtual bool Execute(AAIC_Agent *ref);
//private:
//
//};
//
//class A_MoveTo: public Action {
//private:
//	FVector TargetLocation = FVector(0, 0, 0);
//public:
//	A_MoveTo(FVector Traget = FVector(0, 0, 0));
//	A_MoveTo(AActor Target);
//	virtual bool Execute(AAIC_Agent *ref) override;
//};
//
//class A_CollectHarvest: public Action {
//private:
//	AHarvest* HarvestRef;
//public:
//	 ~A_CollectHarvest();
//	A_CollectHarvest(AHarvest* ref);
//	virtual bool Execute(AAIC_Agent* ref) override;
//};
//
//class A_Attack : public Action {
//private:
//	AActor* Enemy;
//public:
//	A_Attack(AActor* Target);
//	virtual bool Execute(AAIC_Agent* ref) override;
//};
//
//class A_Idle : public Action {
//public:
//	virtual bool Execute(AAIC_Agent* ref) override;
//};
//
//class A_RunAway : public Action {
//private:
//	AActor* Enemy;
//public:
//	A_RunAway(AActor* Target);
//	virtual bool Execute(AAIC_Agent* ref) override;
//};