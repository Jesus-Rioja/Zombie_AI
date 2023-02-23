#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_BaseEnemySpawner.generated.h"

class ATC_CharacterBaseAI;
class USphereComponent;
class ATC_AttackerManager;

UCLASS()
class NEWWORLD_AI_API ATC_BaseEnemySpawner : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "New World")
		TSubclassOf<ATC_CharacterBaseAI> ActorToSpawn;
	UPROPERTY(EditAnywhere, Category = "New World")
		float TimeToSpawn = 0.f;
	UPROPERTY(EditAnywhere, Category = "New World")
		int32 MaxEnemiesToSpawn = 0;
	UPROPERTY(EditAnywhere, Category = "New World")
		USphereComponent* SphereComponent = nullptr;
	UPROPERTY(EditAnywhere, Category = "New World")
		TWeakObjectPtr<ATC_AttackerManager> AttackManager = nullptr;

	ATC_BaseEnemySpawner();
	virtual void Tick(float DeltaTime) override;
	FVector GetRandomPointInSphere() const;

	void RemoveAttackingEnemy(ATC_CharacterBaseAI* Enemy);
	void RemoveWaitingEnemy(ATC_CharacterBaseAI* Enemy);
	bool AddAttackingEnemy(ATC_CharacterBaseAI* Enemy) const;
	bool IsEnemyAttacking(ATC_CharacterBaseAI* Enemy) const;
	bool IsEnemyWaiting(ATC_CharacterBaseAI* Enemy) const;

protected:
	virtual void BeginPlay() override;

private:

	FTimerHandle SpawnTimer;
	int32 CurrentEnemisSpawned = 0;

	void OnSpawnTimer();
};
