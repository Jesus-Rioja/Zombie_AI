#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckAttacking.generated.h"

UCLASS()
class NEWWORLD_AI_API UBTService_CheckAttacking : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_CheckAttacking();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
