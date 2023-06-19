#include "Harvest.h"

AHarvest::AHarvest()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
 	PrimaryActorTick.bCanEverTick = true;
}

void AHarvest::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHarvest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AHarvest::HarvestResources(float Res)
{
	if (!Resources) {
		IsExhausted = true;
		//Destroy();
		MeshComponent->SetVisibility(false);
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AHarvest::RepeatingFunction, 2.0f, false, 5.0f);
		return 0;
	}
	float oldRes = Resources;
	Resources = Resources - Res <= 0 ? 0 : Resources - Res;
	return Resources == 0 ? oldRes : Res;
}

void AHarvest::RepeatingFunction()
{
	MeshComponent->SetVisibility(true);
	IsExhausted = false;
	Resources = 3;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("100"));
}