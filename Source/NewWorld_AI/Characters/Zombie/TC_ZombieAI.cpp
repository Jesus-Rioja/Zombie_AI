#include "Characters/Zombie/TC_ZombieAI.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ATC_ZombieAI::ATC_ZombieAI() : Super()
{
	HardAttackZone = CreateDefaultSubobject<USphereComponent>(TEXT("HardAttackZone"));
	HardAttackZone->SetupAttachment(RootComponent);
}

void ATC_ZombieAI::Attack()
{
	Super::Attack();

	// 1. Select if the zombie will do a combo or just a hard attack.
	if (AttackType == ETC_AttackTypes::None)
	{
		AttackType = GetAttackTypeToDo();
	}

	// 2. Attack
	switch (AttackType)
	{
		case ETC_AttackTypes::Hard:
		{
			const float AnimTime = PlayAnimMontage(AttackInformation[AttackType].Attacks[0]);
			GetWorldTimerManager().SetTimer(TimerAttackDone, this, &ATC_ZombieAI::OnTimerAttackDone, AnimTime, false);
		}
		break;
		case ETC_AttackTypes::Combo:
		{
			GetTotalAttackComboNumber();
 			int32 Index = CurrentComboNumber;
			const float AnimTime = PlayAnimMontage(AttackInformation[AttackType].Attacks[Index]);
			GetWorldTimerManager().SetTimer(TimerAttackDone, this, &ATC_ZombieAI::OnTimerAttackDone, AnimTime, false);
		}
		break;
		default:
			UE_LOG(LogTemp, Error, TEXT("ATC_ZombieAI::Attack -> No attack type detected"));
	}

}

void ATC_ZombieAI::SpawnAttackZone()
{
	FHitResult OutHit;
	if (HardAttackZone)
	{
		UKismetSystemLibrary::SphereTraceSingle(this, HardAttackZone->GetComponentLocation(), HardAttackZone->GetComponentLocation() + 150.f * HardAttackZone->GetComponentRotation().Vector(), 150.f, TraceTypeQuery_MAX, true, {this}, EDrawDebugTrace::ForDuration, OutHit, true);
		if (OutHit.GetActor())
		{
			// 
		}
	}
}

int32 ATC_ZombieAI::GetCurrentTypeAttack() const
{
	return static_cast<int32>(AttackType);
}

bool ATC_ZombieAI::IsComboEnded() const
{
	return CurrentComboNumber == AttackComboNumber;
}

ETC_AttackTypes ATC_ZombieAI::GetAttackTypeToDo() const
{
	int32 RandomValue = UKismetMathLibrary::RandomInteger(100);
	if (RandomValue > HardAttackProbability)
	{
		return ETC_AttackTypes::Combo;
	}

	return ETC_AttackTypes::Hard;
}

void ATC_ZombieAI::OnTimerAttackDone()
{
	OnAttackDone.ExecuteIfBound();
}

void ATC_ZombieAI::GetTotalAttackComboNumber()
{
	AttackComboNumber = (UKismetMathLibrary::RandomInteger(static_cast<int32>(ETC_AttackComboState::NumMaxCombo)));
}

void ATC_ZombieAI::IncrementComboCounter()
{
	if (CurrentComboNumber < AttackComboNumber)
	{
		CurrentComboNumber++;
	}
}

void ATC_ZombieAI::FinishCombo()
{
	CurrentComboNumber = 0;
}
