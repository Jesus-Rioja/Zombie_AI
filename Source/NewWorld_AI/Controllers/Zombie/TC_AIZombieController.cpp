#include "Controllers/Zombie/TC_AIZombieController.h"
#include "AIModule/Classes/Perception/AIPerceptionSystem.h"
#include "AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "AIModule/Classes/Perception/AISense_Sight.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "NewWorld_AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Zombie/TC_ZombieAI.h"
#include "Components/TC_AggroComponent.h"

ATC_AIZombieController::ATC_AIZombieController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AggroComponent = CreateDefaultSubobject<UTC_AggroComponent>(TEXT("AggroComponent"));
}

void ATC_AIZombieController::BeginPlay()
{
	Super::BeginPlay();

	if (PerceptionComponent)
	{
		PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ATC_AIZombieController::OnTargetPerceptionUpdated);
	}

	BlackboardComponent->SetValueAsBool("bCanScream", false);
	BlackboardComponent->SetValueAsBool("bCanAttack", true);
}

void ATC_AIZombieController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->IsA<ANewWorld_AICharacter>())
	{
		if (UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus) == UAISense_Sight::StaticClass())
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				if (LostPerception.IsValid())
				{
					GetWorldTimerManager().ClearTimer(LostPerception);
				}

				AActor* BBActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));

				if (BBActor != Actor)
				{
					BlackboardComponent->SetValueAsObject("TargetActor", Actor);
				}

				if (!bCanScream)
				{
					bCanScream = true;
					BlackboardComponent->SetValueAsBool("bCanScream", true);
				}

				AggroComponent->AddActorWithAggro(Actor, 1.f);
			}
			else
			{

				if (ATC_CharacterBaseAI* CharacterBase = Cast<ATC_CharacterBaseAI>(GetPawn()))
				{
					CharacterBase->RemoveAttackingEnemy();
					CharacterBase->RemoveWaitingEnemy();
					BlackboardComponent->SetValueAsBool("bCanAttack", true);
				}

				GetWorldTimerManager().SetTimer(LostPerception, this, &ATC_AIZombieController::OnLostPerception, LostPerceptionTimer, false);
			}
		}
	}
}

void ATC_AIZombieController::OnLostPerception()
{
	ATC_ZombieAI* ZombieCharacter = Cast<ATC_ZombieAI>(GetPawn());
	if (ZombieCharacter)
	{
		ZombieCharacter->GetCharacterMovement()->MaxWalkSpeed = 25.f;
	}

	BlackboardComponent->SetValueAsObject("TargetActor", nullptr);
	BlackboardComponent->SetValueAsBool("bCanScream", false);

	bCanScream = false;

	if (LostPerception.IsValid())
	{
		GetWorldTimerManager().ClearTimer(LostPerception);
	}
}
