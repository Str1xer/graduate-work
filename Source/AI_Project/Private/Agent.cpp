#include "Agent.h"
#include "AIC_Agent.h"
#include "Planner.h"

AAgent::AAgent()
{
 	PrimaryActorTick.bCanEverTick = true;

	//StateText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("State Name"));
	//StateText->SetHorizontalAlignment(EHTA_Center);
	//StateText->SetText(FText::FromString("Collecting"));
	//StateText->RegisterComponent();
	//StateText->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	//StateText->SetRelativeLocation(FVector(0, 0, 100));
	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
	//Sword->RegisterComponent();
	Sword->SetupAttachment(GetMesh(), FName("hand_rSocket"));
}

void AAgent::BeginPlay()
{
	Super::BeginPlay();
	//Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("hand_rSocket"));
	Sword->SetVisibility(false);
	//StateText->SetVisibility(false);
	Controller = Cast<AAIC_Agent>(AAgent::GetController());
}

void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


//void AAgent::AddResource(float count) {
//	Resources += count;
//}
//
float AAgent::UnloadingResourcesTime(float count) {
	float back = count <= ResourcesTime ? count : ResourcesTime;
	ResourcesTime -= back;
	return back;
}

void AAgent::Punch() 
{
	GetMesh()->GetAnimInstance()->Montage_Play(PunchMontage, 1.0);
}
//
//float AAgent::GetResourcesCount() {
//	return Resources;
//}