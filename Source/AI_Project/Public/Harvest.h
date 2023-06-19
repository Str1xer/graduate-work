#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Harvest.generated.h"

UCLASS()
class AI_PROJECT_API AHarvest : public AActor
{
	GENERATED_BODY()
	
private:
	FTimerHandle MemberTimerHandle;

public:	
	AHarvest();
	float Resources = 3;
	bool IsExhausted = false;
	bool IsTaken = false;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	float HarvestResources(float Res);
	void RepeatingFunction();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
};
