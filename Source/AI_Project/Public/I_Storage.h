// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Storage.generated.h"


UINTERFACE(MinimalAPI)
class UI_Storage : public UInterface
{
	GENERATED_BODY()
};


class AI_PROJECT_API II_Storage
{
	GENERATED_BODY()
private:
	int Resources;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//void AddResource(int count);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
	void AddResource(int count);

};
