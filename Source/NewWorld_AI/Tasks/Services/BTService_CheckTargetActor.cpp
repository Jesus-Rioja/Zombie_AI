#include "Tasks/Services/BTService_CheckTargetActor.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Controllers/TC_AIBaseController.h"

UBTService_CheckTargetActor::UBTService_CheckTargetActor() : Super()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	ATC_AIBaseController* ControllerBase = Cast<ATC_AIBaseController>(OwnerComp.GetAIOwner());

	if (!BlackboardComponent || ControllerBase)
		return;

	AActor* AggroedActor = ControllerBase->GetBiggestAggroActor();
	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
	if (AggroedActor != TargetActor)
	{
		BlackboardComponent->SetValueAsObject("TargetActor", ControllerBase->GetBiggestAggroActor());
	}
}

