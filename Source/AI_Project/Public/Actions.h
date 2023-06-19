#pragma once

#include "CoreMinimal.h"

class AAIC_Agent;
class AHarvest;
class AEnemy;

class Action
{
public:
	Action();
	//virtual ~Action() {};
	virtual bool Execute(AAIC_Agent* ref);
private:

};

namespace Actions
{
	//Moving to target action
	class MoveTo : public Action {
	private:
		float Radius = 100.0;
		FVector TargetLocation = FVector(0, 0, 0);
	public:
		MoveTo(const FVector Traget = FVector(0, 0, 0), const float radius = 100.0);
		MoveTo(AActor* Target);
		virtual bool Execute(AAIC_Agent* ref) override;
	};

	//Collection harvest action
	class CollectHarvest : public Action {
	private:
		AHarvest* HarvestRef;
	public:
		~CollectHarvest();
		CollectHarvest(AHarvest* ref);
		virtual bool Execute(AAIC_Agent* ref) override;
	};

	//Attack action
	class Attack : public Action {
	private:
		enum class EAttackState : uint8 {
			AS_CanAttack,
			AS_Waiting,
		};
		EAttackState CurrentAS = EAttackState::AS_CanAttack;
		AEnemy* Enemy;
		float SleepTimer;
	public:
		Attack(AActor* Target);
		virtual bool Execute(AAIC_Agent* ref) override;
		void AttackReloading(float time);
	};

	//Idle action
	class Idle : public Action {
	public:
		virtual bool Execute(AAIC_Agent* ref) override;
	};

	//Run away action
	class RunAway : public Action {
	private:
		AActor* Enemy;
	public:
		RunAway(AActor* Target);
		virtual bool Execute(AAIC_Agent* ref) override;
	};

	//Unloading resources action
	class Unloading : public Action {
	private:
		//AActor* Enemy;
	public:
		Unloading();
		virtual bool Execute(AAIC_Agent* ref) override;
	};

	//Arming action
	class Arming : public Action {
	private:
		bool Taking = true;
	public:
		Arming(bool NewState = true);
		virtual bool Execute(AAIC_Agent* ref) override;
	};

};
