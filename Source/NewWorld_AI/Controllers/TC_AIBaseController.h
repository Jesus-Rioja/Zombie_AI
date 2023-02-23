#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TC_AIBaseController.generated.h"

class UAISenseConfig_Sight;
class UAISenseConfig_Damage;
class UBlackboardComponent;
class UBehaviorTreeComponent;
class UTC_AggroComponent;

UCLASS()
class NEWWORLD_AI_API ATC_AIBaseController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = IA)
		UAISenseConfig_Sight* SightConfig = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = IA)
		UAISenseConfig_Damage* DamageConfig = nullptr;
	UPROPERTY()
		UBlackboardComponent* BlackboardComponent = nullptr;
	UPROPERTY()
		UBehaviorTreeComponent* BehaviorTreeComponent = nullptr;


	ATC_AIBaseController(const FObjectInitializer& ObjectInitializer);
	void AddActorWithAggro(AActor* Actor, const float Aggro);
	AActor* GetBiggestAggroActor() const;
protected:
	UPROPERTY()
		UTC_AggroComponent* AggroComponent = nullptr;
	virtual void OnPossess(APawn* InPawn) override;
};
