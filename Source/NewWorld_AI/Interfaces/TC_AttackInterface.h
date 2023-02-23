#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TC_AttackInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UTC_AttackInterface : public UInterface
{
	GENERATED_BODY()
};

class ITC_AttackInterface
{
	GENERATED_BODY()

public:
	virtual void Attack() = 0;
	virtual void SpawnAttackZone() = 0;
	virtual int32 GetCurrentTypeAttack() const { return 0; }
	virtual bool IsComboEnded() const { return true; };
	virtual void IncrementComboCounter() {};
	virtual void FinishCombo() {};
};




