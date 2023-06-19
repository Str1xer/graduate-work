#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"
#include "Agent.generated.h"

class AAIC_Agent;
class APlanner;

UENUM(BlueprintType)
enum class EAgentState : uint8 {
	AS_Walk UMETA(DisplayName = "Walk"),
	AS_Collect UMETA(DisplayName = "Collect"),
	AS_Attack UMETA(DisplayName = "Attack"),
};

UCLASS()
class AI_PROJECT_API AAgent : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	AAgent();
	AAIC_Agent* Controller = NULL;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	APlanner* Planner;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* Storage;
	//UTextRenderComponent* StateText;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanFight = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	float ResourcesTime = 0;
	int ResourcesCount = 0;
	float UnloadingResourcesTime(float count);
	//void AddResource(float count);
	//float UnloadResource(float count);
	//float GetResourcesCount();
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Sword;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAgentState CurrentState = EAgentState::AS_Walk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* PunchMontage;
	void Punch();
};
