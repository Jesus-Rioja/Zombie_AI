#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetRandomPointInSphere.generated.h"

UCLASS()
class NEWWORLD_AI_API UBTTask_GetRandomPointInSphere : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_GetRandomPointInSphere();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
