#include "Tasks/BTTask_Attack.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Controllers/TC_AIBaseController.h"
#include "Characters/TC_CharacterBaseAI.h"
#include "Characters/Zombie/TC_ZombieAI.h"
#include "Characters/TC_TurretBase.h"

UBTTask_Attack::UBTTask_Attack() : Super()
{
	bCreateNodeInstance = true;
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	ATC_AIBaseController* BaseController = Cast<ATC_AIBaseController>(OwnerComp.GetAIOwner());
	ATC_CharacterBaseAI* BaseCharacter = BaseController ? Cast<ATC_CharacterBaseAI>(BaseController->GetPawn()) : nullptr;

	if (!BlackboardComp || !BaseCharacter)
		return EBTNodeResult::Failed;

	ControllerBase = BaseController;
	AActor* Target = Cast<AActor>(BlackboardComp->GetValue<UBlackboardKeyType_Object>("TargetActor"));
	if (!Target)
		return EBTNodeResult::Succeeded;

	if (BaseCharacter->IsEnemyAttacking() || BaseCharacter->AddAttackingEnemy())
	{
		BaseCharacter->Attack();
		BaseCharacter->OnAttackDone.BindUObject(this, &UBTTask_Attack::OnAttackDone);
		return EBTNodeResult::InProgress;
	}
	else
	{
		if (ATC_TurretBase* Turret = Cast<ATC_TurretBase>(BaseCharacter))
		{
			Turret->Attack();
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
}

void UBTTask_Attack::OnAttackDone()
{
	ATC_AIBaseController* BaseController = ControllerBase.Get();
	if (BaseController)
	{
		ATC_CharacterBaseAI* CharacterBase = Cast<ATC_CharacterBaseAI>(ControllerBase.Get()->GetPawn());
		if (CharacterBase)
		{
			ETC_AttackTypes TypeAttack = static_cast<ETC_AttackTypes>(CharacterBase->GetCurrentTypeAttack());
			switch (TypeAttack)
			{
				case ETC_AttackTypes::Hard:
				{
					CharacterBase->OnAttackDone.Unbind();
					FinishLatentTask(*ControllerBase.Get()->BehaviorTreeComponent, EBTNodeResult::Succeeded);
				}
				break;
				case ETC_AttackTypes::Combo:
				{
					if (CharacterBase->IsComboEnded())
					{
						CharacterBase->FinishCombo();
						CharacterBase->OnAttackDone.Unbind();
						FinishLatentTask(*ControllerBase.Get()->BehaviorTreeComponent, EBTNodeResult::Succeeded);
					}
					else
					{
						FinishLatentTask(*ControllerBase.Get()->BehaviorTreeComponent, EBTNodeResult::InProgress);
						CharacterBase->IncrementComboCounter();
						CharacterBase->Attack();
					}
				}
				break;
				default:
					FinishLatentTask(*ControllerBase.Get()->BehaviorTreeComponent, EBTNodeResult::Failed);
			}
		}
	}
}