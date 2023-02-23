#include "Characters/TC_CharacterBaseAI.h"
#include "Actors/TC_BaseEnemySpawner.h"

ATC_CharacterBaseAI::ATC_CharacterBaseAI()
{
}

void ATC_CharacterBaseAI::Attack()
{
}

void ATC_CharacterBaseAI::SpawnAttackZone()
{

}

void ATC_CharacterBaseAI::RemoveAttackingEnemy()
{
	ATC_BaseEnemySpawner* EnemySpawner = Cast<ATC_BaseEnemySpawner>(Spawner);
	if (!EnemySpawner)
		return;

	EnemySpawner->RemoveAttackingEnemy(this);
}

void ATC_CharacterBaseAI::RemoveWaitingEnemy()
{
	ATC_BaseEnemySpawner* EnemySpawner = Cast<ATC_BaseEnemySpawner>(Spawner);
	if (!EnemySpawner)
		return;

	EnemySpawner->RemoveWaitingEnemy(this);
}

bool ATC_CharacterBaseAI::AddAttackingEnemy()
{
	ATC_BaseEnemySpawner* EnemySpawner = Cast<ATC_BaseEnemySpawner>(Spawner);
	if (!EnemySpawner)
		return false;

	return EnemySpawner->AddAttackingEnemy(this);
}

bool ATC_CharacterBaseAI::IsEnemyAttacking()
{
	ATC_BaseEnemySpawner* EnemySpawner = Cast<ATC_BaseEnemySpawner>(Spawner);
	if (!EnemySpawner)
		return false;

	return EnemySpawner->IsEnemyAttacking(this);
}

bool ATC_CharacterBaseAI::IsEnemyWaiting()
{
	ATC_BaseEnemySpawner* EnemySpawner = Cast<ATC_BaseEnemySpawner>(Spawner);
	if (!EnemySpawner)
		return false;

	return EnemySpawner->IsEnemyWaiting(this);
}

void ATC_CharacterBaseAI::BeginPlay()
{
	Super::BeginPlay();
}