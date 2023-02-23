#pragma once

#include "CoreMinimal.h"
#include "TC_CharacterBaseAI.h"
#include "TC_TurretBase.generated.h"

class UStaticMeshComponent;
class ATC_ProjectileBase;
class USceneComponent;

UCLASS()
class NEWWORLD_AI_API ATC_TurretBase : public ATC_CharacterBaseAI
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "New World")
		UStaticMeshComponent* TurretBarrel = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "New World")
		UStaticMeshComponent* TurretBase = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "New World")
		UStaticMeshComponent* TurretTop = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "New World")
		USceneComponent* SpawnPosition = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "New World")
		TSubclassOf<ATC_ProjectileBase> ProjectileToSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "New World")
		float TimeToDestroy = 0.f;

	ATC_TurretBase();

	virtual void Attack() override;

protected:

	virtual void BeginPlay() override;

private:

	FTimerHandle DestroyTimer;
	void OnDestroyTimer();

};
