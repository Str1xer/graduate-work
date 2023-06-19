#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class AI_PROJECT_API AEnemy : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
private:
	float health = 100;
public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void TakingDamage(float damage);
	bool IsDead();
};
