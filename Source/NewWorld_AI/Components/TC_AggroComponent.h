#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TC_AggroComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWWORLD_AI_API UTC_AggroComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTC_AggroComponent();

	void AddActorWithAggro(AActor* Actor, const float Aggro);
	AActor* GetMoreAggroActor() const;
protected:
	UPROPERTY()
		TMap<AActor*, float> AggroMap;

	virtual void BeginPlay() override;
};
