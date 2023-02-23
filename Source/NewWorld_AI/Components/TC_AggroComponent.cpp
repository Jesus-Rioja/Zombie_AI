#include "Components/TC_AggroComponent.h"

UTC_AggroComponent::UTC_AggroComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTC_AggroComponent::AddActorWithAggro(AActor* Actor, const float Aggro)
{
	if (!AggroMap.Contains(Actor))
	{
		AggroMap.Add(Actor, Aggro);
	}
}

AActor* UTC_AggroComponent::GetMoreAggroActor() const
{
	float BiggestAggro = -999.f;
	AActor* BiggestActor = nullptr;
	for (auto& Aggroed : AggroMap)
	{
		if (BiggestAggro < Aggroed.Value)
		{
			BiggestActor = Aggroed.Key;
		}
	}

	return BiggestActor;
}

void UTC_AggroComponent::BeginPlay()
{
	Super::BeginPlay();
}