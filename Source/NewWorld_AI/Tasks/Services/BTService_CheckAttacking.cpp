#include "Tasks/Services/BTService_CheckAttacking.h"
#include "Characters/TC_CharacterBaseAI.h"
#include "Controllers/TC_AIBaseController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_CheckAttacking::UBTService_CheckAttacking() : Super()
{
	NodeName = "Check Attacking";
	bCreateNodeInstance = true;
}


void UBTService_CheckAttacking::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	ATC_AIBaseController* ControllerBase = Cast<ATC_AIBaseController>(OwnerComp.GetAIOwner());
	ATC_CharacterBaseAI* CharacterBase = ControllerBase ? Cast<ATC_CharacterBaseAI>(ControllerBase->GetPawn()) : nullptr;
	if (!BlackboardComponent || !CharacterBase)
		return;

	const bool bIsAttacking = BlackboardComponent->GetValueAsBool("bCanAttack");

	if (CharacterBase->IsEnemyWaiting() && bIsAttacking)
	{
		BlackboardComponent->SetValueAsBool("bCanAttack", false);
	}

	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
	if (TargetActor)
	{
		const float Distance = UKismetMathLibrary::Vector_Distance(CharacterBase->GetActorLocation(), TargetActor->GetActorLocation());
		if (Distance >= 200.f && CharacterBase->IsEnemyAttacking())
		{
			CharacterBase->RemoveAttackingEnemy();
		}
	}
}
