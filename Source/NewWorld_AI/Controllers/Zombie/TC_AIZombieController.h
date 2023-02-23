#pragma once

#include "CoreMinimal.h"
#include "Controllers/TC_AIBaseController.h"
#include "AIModule/Classes/Perception/AIPerceptionTypes.h"
#include "TC_AIZombieController.generated.h"

class UTC_AggroComponent;

UCLASS()
class NEWWORLD_AI_API ATC_AIZombieController : public ATC_AIBaseController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "New World")
		float LostPerceptionTimer = 0.f;

	ATC_AIZombieController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

private:
	bool bCanScream = false;
	FTimerHandle LostPerception;

	UFUNCTION()
		void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	void OnLostPerception();

	
};
