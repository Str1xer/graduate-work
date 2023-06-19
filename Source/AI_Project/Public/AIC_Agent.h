#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "AIC_Agent.generated.h"

class AAgent;
class APlanner;
class Action;

UCLASS()
class AI_PROJECT_API AAIC_Agent : public AAIController
{
	GENERATED_BODY()

protected:
	AAIC_Agent();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual FRotator GetControlRotation() const override;

private:
	//APlanner* Planner;
	TQueue<TSharedPtr<Action>> Actions = TQueue<TSharedPtr<Action>>();

public:
	AAgent* Character;
	void AddAction(TSharedPtr<Action> act);
	void RemovePlan();

	//bool MoveTo(FVector TargetLocation);
	bool Plan();
	bool HasActionPlan();

	float MyDeltaTime = 0;

	UFUNCTION(Category = "Perception")
		void OnPawnDetected(const TArray<AActor*>& Actors);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 90.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;

};
