#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Attack.generated.h"

class ATC_AIBaseController;

UCLASS()
class NEWWORLD_AI_API UBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_Attack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
private:
	TWeakObjectPtr<ATC_AIBaseController> ControllerBase = nullptr;
	void OnAttackDone();
};
