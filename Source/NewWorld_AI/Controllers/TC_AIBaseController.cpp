#include "Controllers/TC_AIBaseController.h"
#include "AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "AIModule/Classes/Perception/AISenseConfig_Damage.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Characters/TC_CharacterBaseAI.h"
#include "AIModule/Classes/Navigation/CrowdFollowingComponent.h"
#include "Components/TC_AggroComponent.h"

ATC_AIBaseController::ATC_AIBaseController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	SightConfig->SightRadius = 500.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 20.f;
	SightConfig->PeripheralVisionAngleDegrees = 360.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void ATC_AIBaseController::AddActorWithAggro(AActor* Actor, const float Aggro)
{
	if (AggroComponent)
	{
		AggroComponent->AddActorWithAggro(Actor, Aggro);
	}
}

AActor* ATC_AIBaseController::GetBiggestAggroActor() const
{
	if (AggroComponent)
	{
		return AggroComponent->GetMoreAggroActor();
	}

	return nullptr;
}

void ATC_AIBaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ATC_CharacterBaseAI* CharacterBase = Cast<ATC_CharacterBaseAI>(InPawn);
	UBehaviorTree* CharacterBehaviorTree = CharacterBase ? CharacterBase->BehaviorTree : nullptr;

	if (CharacterBehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*CharacterBehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*CharacterBehaviorTree);
	}

	BlackboardComponent->SetValueAsBool("bCanMove", true);
}