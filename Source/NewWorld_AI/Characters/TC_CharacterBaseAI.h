#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/TC_AttackInterface.h"
#include "TC_CharacterBaseAI.generated.h"

class UBehaviorTree;

DECLARE_DELEGATE(FAttackDone);

UCLASS()
class NEWWORLD_AI_API ATC_CharacterBaseAI : public ACharacter, public ITC_AttackInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree = nullptr;
	UPROPERTY()
		AActor* Spawner = nullptr;

	FAttackDone OnAttackDone;

	ATC_CharacterBaseAI();

	virtual void Attack() override;
	virtual void SpawnAttackZone() override;

	void RemoveAttackingEnemy();
	void RemoveWaitingEnemy();
	bool AddAttackingEnemy();
	bool IsEnemyAttacking();
	bool IsEnemyWaiting();
	
protected:
	virtual void BeginPlay() override;

};