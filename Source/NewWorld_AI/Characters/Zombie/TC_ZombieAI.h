#pragma once

#include "CoreMinimal.h"
#include "Characters/TC_CharacterBaseAI.h"
#include "TC_ZombieAI.generated.h"

class UAnimMontage;
class USphereComponent;

UENUM()
enum class ETC_AttackTypes : int32
{
	Hard = 0,
	Combo = 1,
	None = 2
};

UENUM()
enum class ETC_AttackComboState : int32
{
	Combo1 = 0,
	Combo2 = 1,
	Combo3 = 2,
	NumMaxCombo = 3
};

USTRUCT(BlueprintType)
struct FTC_AttackInformation
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TArray<UAnimMontage*> Attacks;
};

UCLASS()
class NEWWORLD_AI_API ATC_ZombieAI : public ATC_CharacterBaseAI
{
	GENERATED_BODY()

public:
	ATC_ZombieAI();
	virtual void Attack() override;
	virtual void SpawnAttackZone() override;
	virtual int32 GetCurrentTypeAttack() const override;
	virtual bool IsComboEnded() const override;
	virtual void IncrementComboCounter() override;
	virtual void FinishCombo() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "New World")
		TMap<ETC_AttackTypes, FTC_AttackInformation> AttackInformation;

	UPROPERTY(EditAnywhere, Category = "New World", meta = (ClampMax = 100))
		int32 HardAttackProbability = 0;

	UPROPERTY(EditDefaultsOnly, Category = "New World")
		USphereComponent* HardAttackZone = nullptr;

private:
	
	FTimerHandle TimerAttackDone;
	int32 AttackComboNumber = 0U;
	int32 CurrentComboNumber = 0U;
	ETC_AttackTypes AttackType = ETC_AttackTypes::None;

	ETC_AttackTypes GetAttackTypeToDo() const;
	void OnTimerAttackDone();
	void GetTotalAttackComboNumber();
};
