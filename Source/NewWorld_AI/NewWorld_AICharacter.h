#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NewWorld_AICharacter.generated.h"

class ATC_TurretBase;
class USceneComponent;

UCLASS(config = Game)
class ANewWorld_AICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "New World")
		TSubclassOf<ATC_TurretBase> TurretToSpawn;

	ANewWorld_AICharacter();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void SpawnTurret();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
	UPROPERTY(EditDefaultsOnly, Category = "New World")
		USceneComponent* TurretSpawnPosition = nullptr;
};

