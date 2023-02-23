// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TC_ProjectileBase.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class NEWWORLD_AI_API ATC_ProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "New World")
		UStaticMeshComponent* StaticMeshComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "New World")
		UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
		USphereComponent* CollisionComponent = nullptr;

	ATC_ProjectileBase();

	void Fire(const FVector& ShootDirection);

protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
