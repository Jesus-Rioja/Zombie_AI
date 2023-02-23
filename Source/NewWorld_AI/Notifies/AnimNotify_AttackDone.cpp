#include "Notifies/AnimNotify_AttackDone.h"
#include "Characters/TC_CharacterBaseAI.h"

void UAnimNotify_AttackDone::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ATC_CharacterBaseAI* BaseCharacter = MeshComp ? Cast<ATC_CharacterBaseAI>(MeshComp->GetOwner()) : nullptr;

	if (!BaseCharacter)
		return;

	BaseCharacter->SpawnAttackZone();
}

