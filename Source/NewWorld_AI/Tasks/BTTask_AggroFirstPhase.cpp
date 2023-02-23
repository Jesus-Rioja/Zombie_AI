#include "Tasks/BTTask_AggroFirstPhase.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Controllers/TC_AIBaseController.h"
#include "Characters/TC_CharacterBaseAI.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_AggroFirstPhase::UBTTask_AggroFirstPhase() : Super()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_AggroFirstPhase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (PossibleMontages.Num() == 0)
		return EBTNodeResult::Succeeded;

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	BaseController = Cast<ATC_AIBaseController>(OwnerComp.GetAIOwner());
	ATC_CharacterBaseAI* BaseCharacter = BaseController.Get() ? Cast<ATC_CharacterBaseAI>(BaseController.Get()->GetPawn()) : nullptr;

	if (!BlackboardComponent || !BaseCharacter)
		return EBTNodeResult::Failed;

	const float AnimationTime = BaseCharacter->PlayAnimMontage(GetRandomMontage());
	BaseCharacter->GetWorldTimerManager().SetTimer(AnimationPlaying, this, &UBTTask_AggroFirstPhase::OnAnimationPlaying, AnimationTime, false);

	return EBTNodeResult::InProgress;
}

void UBTTask_AggroFirstPhase::OnAnimationPlaying()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = BaseController.Get()->BehaviorTreeComponent;
	UBlackboardComponent* BlackboardComponent = BaseController.Get()->BlackboardComponent;

	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsBool("bCanScream", false);
	}

	ATC_CharacterBaseAI* BaseCharacter = BaseController.Get() ? Cast<ATC_CharacterBaseAI>(BaseController.Get()->GetPawn()) : nullptr;
	if (BaseCharacter)
	{
		BaseCharacter->GetCharacterMovement()->MaxWalkSpeed = 250.f;
	}

	FinishLatentTask(*BehaviorTreeComponent, EBTNodeResult::Succeeded);
}

UAnimMontage* UBTTask_AggroFirstPhase::GetRandomMontage() const
{
	int32 Index = UKismetMathLibrary::RandomIntegerInRange(0, PossibleMontages.Num() - 1);
	return PossibleMontages[Index];
}