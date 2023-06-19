#include "Enemy.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	SetGenericTeamId(3);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::TakingDamage(float damage) {
	health -= damage;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Enemy HP: %f"), health));
}

bool AEnemy::IsDead() {
	if (health <= 0) {
		GetMesh()->SetVisibility(false);
		SetActorEnableCollision(false);
	}
	

	return health <= 0;
}
