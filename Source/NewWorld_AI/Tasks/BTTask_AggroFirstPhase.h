#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_AggroFirstPhase.generated.h"

class UAnimMontage;
class ATC_AIBaseController;

UCLASS()
class NEWWORLD_AI_API UBTTask_AggroFirstPhase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<UAnimMontage*> PossibleMontages;

	UBTTask_AggroFirstPhase();

protected:
	TWeakObjectPtr<ATC_AIBaseController> BaseController = nullptr;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	FTimerHandle AnimationPlaying;
	
	void OnAnimationPlaying();
	UAnimMontage* GetRandomMontage() const;
};
