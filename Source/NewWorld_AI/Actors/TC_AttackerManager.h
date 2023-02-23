#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_AttackerManager.generated.h"

class ATC_CharacterBaseAI;

UCLASS()
class NEWWORLD_AI_API ATC_AttackerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATC_AttackerManager();

	bool AddCurrentAttackingEnemies(ATC_CharacterBaseAI* Enemy);
	bool IsEnemyAttacking(ATC_CharacterBaseAI* Enemy) const;
	bool IsEnemyWaiting(ATC_CharacterBaseAI* Enemy) const;

	void RemoveAttackingEnemy(ATC_CharacterBaseAI* Enemy);
	void RemoveWaitingEnemy(ATC_CharacterBaseAI* Enemy);
protected:

	UPROPERTY(EditAnywhere, Category = "New World")
		int32 MaxAttackingEnemies = 0;

	virtual void BeginPlay() override;

private:

	UPROPERTY()
		TArray<TWeakObjectPtr<ATC_CharacterBaseAI>> CurrentAttackingEnemies;
	UPROPERTY()
		TArray<TWeakObjectPtr<ATC_CharacterBaseAI>> CurrentWaitingEnemies;

};
