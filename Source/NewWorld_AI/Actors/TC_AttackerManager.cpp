#include "Actors/TC_AttackerManager.h"
#include "Characters/TC_CharacterBaseAI.h"

ATC_AttackerManager::ATC_AttackerManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool ATC_AttackerManager::AddCurrentAttackingEnemies(ATC_CharacterBaseAI* Enemy)
{
	if (CurrentAttackingEnemies.Num() < MaxAttackingEnemies)
	{
		CurrentAttackingEnemies.AddUnique(Enemy);
		return true;
	}
	
	CurrentWaitingEnemies.AddUnique(Enemy);
	return false;
}

bool ATC_AttackerManager::IsEnemyAttacking(ATC_CharacterBaseAI* Enemy) const
{
	return CurrentAttackingEnemies.Find(Enemy) != INDEX_NONE;
}

bool ATC_AttackerManager::IsEnemyWaiting(ATC_CharacterBaseAI* Enemy) const
{
	return CurrentWaitingEnemies.Find(Enemy) != INDEX_NONE;
}

void ATC_AttackerManager::RemoveAttackingEnemy(ATC_CharacterBaseAI* Enemy)
{
	CurrentAttackingEnemies.Remove(Enemy);
}

void ATC_AttackerManager::RemoveWaitingEnemy(ATC_CharacterBaseAI* Enemy)
{
	CurrentWaitingEnemies.Remove(Enemy);
}

void ATC_AttackerManager::BeginPlay()
{
	Super::BeginPlay();
}