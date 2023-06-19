// Fill out your copyright notice in the Description page of Project Settings.

#include "AIC_Agent.h"
#include "Agent.h"
#include "Planner.h"
#include "Enemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIC_Agent::AAIC_Agent() {
	PrimaryActorTick.bCanEverTick = true;

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(*SightConfig->GetSenseImplementation());
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AAIC_Agent::OnPawnDetected);
	
	SetGenericTeamId(FGenericTeamId(1));

}

void AAIC_Agent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AAgent>(AAIC_Agent::GetPawn());
	Cast<AAgent>(AAIC_Agent::GetPawn())->Planner->Agents.Add(this);
	bool isGettedPlan = Plan();

	//if (*Character->GetActorLabel() == FString("BP_Agent3")) {
	//	for (int i = 0; i < 2; i++) {
	//	Actions.Pop();
	//	AddAction(MakeShareable(new A_MoveTo(FVector(0, 0, 0))));
	//	}
	//}
	//MoveTo();
}

void AAIC_Agent::Tick(float DeltaTime)
{
	MyDeltaTime = DeltaTime;
	if (HasActionPlan()){
		TSharedPtr<Action>* a = Actions.Peek();
		bool result = (*a)->Execute(this);
			
		if (result) {
			Actions.Pop();
		}
	}
	else
	{
		Plan();
	}
}

bool AAIC_Agent::HasActionPlan() 
{
	return !Actions.IsEmpty();
}

bool AAIC_Agent::Plan()
{
	Character->Planner->Plan(this);

	return true;
}

void AAIC_Agent::AddAction(TSharedPtr<Action> act)
{
	Actions.Enqueue(act);
}

void AAIC_Agent::RemovePlan() {
	if (HasActionPlan())
		Actions.Empty();
}

void AAIC_Agent::OnPawnDetected(const TArray<AActor*>& Actors)
{
	if (Actors.Num() > 0)
		if (!Cast<AEnemy>(Actors[0])->IsDead())
			Character->Planner->EnemyFound(Actors[0]);
}


FRotator AAIC_Agent::GetControlRotation() const {
	if (GetPawn() == nullptr)
		return FRotator(0.0f, 0.0f, 0.0f);

	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}