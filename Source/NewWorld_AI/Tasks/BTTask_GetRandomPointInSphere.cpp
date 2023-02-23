#include "Tasks/BTTask_GetRandomPointInSphere.h"
#include "Actors/TC_BaseEnemySpawner.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Controllers/TC_AIBaseController.h"
#include "Characters/TC_CharacterBaseAI.h"

UBTTask_GetRandomPointInSphere::UBTTask_GetRandomPointInSphere() : Super()
{
	bCreateNodeInstance = true;
	NodeName = "Get Random Point in Sphere";
}

EBTNodeResult::Type UBTTask_GetRandomPointInSphere::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	ATC_AIBaseController* ControllerBase = Cast<ATC_AIBaseController>(OwnerComp.GetAIOwner());
	ATC_CharacterBaseAI* CharacterBase = ControllerBase ? Cast<ATC_CharacterBaseAI>(ControllerBase->GetPawn()) : nullptr;
	ATC_BaseEnemySpawner* Spawner = CharacterBase ? Cast<ATC_BaseEnemySpawner>(CharacterBase->Spawner) : nullptr;

	if (!BlackboardComp || !Spawner)
		return EBTNodeResult::Failed;

	FVector RandomPoint = Spawner->GetRandomPointInSphere();
	RandomPoint.Z = 228.001297;

	BlackboardComp->SetValueAsVector("MoveToLocation", RandomPoint);
	
	return EBTNodeResult::Succeeded;
}
