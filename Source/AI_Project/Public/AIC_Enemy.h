// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class AI_PROJECT_API AAIC_Enemy : public AAIController
{
	GENERATED_BODY()
	
protected:
	AAIC_Enemy();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool UnderAttack = false;
};
