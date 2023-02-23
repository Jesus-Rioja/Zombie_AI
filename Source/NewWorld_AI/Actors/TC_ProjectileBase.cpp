#include "Actors/TC_ProjectileBase.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Characters/TC_CharacterBaseAI.h"
#include "Controllers/TC_AIBaseController.h"

ATC_ProjectileBase::ATC_ProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(15.f);
	RootComponent = CollisionComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->InitialSpeed = 600.f;
	ProjectileMovementComponent->MaxSpeed = 600.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->bIsHomingProjectile = false;
	// ProjectileMovementComponent->HomingAccelerationMagnitude = 300.f;

	InitialLifeSpan = 2.f;
}

void ATC_ProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentHit.AddUniqueDynamic(this, &ATC_ProjectileBase::OnHit);
}

void ATC_ProjectileBase::Fire(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void ATC_ProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ATC_CharacterBaseAI* CharacterBase = Cast<ATC_CharacterBaseAI>(OtherActor);
	ATC_AIBaseController* BaseController = CharacterBase ? Cast<ATC_AIBaseController>(CharacterBase->GetController()) : nullptr;
	if (BaseController)
	{
		BaseController->AddActorWithAggro(this, 2.f);
	}
	Destroy();
}