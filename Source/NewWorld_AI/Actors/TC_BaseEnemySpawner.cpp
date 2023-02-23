#include "Actors/TC_BaseEnemySpawner.h"
#include "Characters/TC_CharacterBaseAI.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Controllers/TC_AIBaseController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "TC_AttackerManager.h"

ATC_BaseEnemySpawner::ATC_BaseEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
}

void ATC_BaseEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ATC_BaseEnemySpawner::OnSpawnTimer, TimeToSpawn, true);
}

void ATC_BaseEnemySpawner::OnSpawnTimer()
{
	if (CurrentEnemisSpawned < MaxEnemiesToSpawn)
	{
		FTransform SpawnTransform;
		FActorSpawnParameters Params;
		const FVector& RandomPointInSphere = GetRandomPointInSphere();
		const float RandomYaw = UKismetMathLibrary::RandomFloatInRange(0.f, 999.f);
		const FQuat NewQuaternion = UKismetMathLibrary::MakeRotator(0.f, 0.f, RandomYaw).Quaternion();
		
		SpawnTransform.SetLocation(RandomPointInSphere);
		SpawnTransform.SetRotation(NewQuaternion);

		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (ATC_CharacterBaseAI* SpawnerEnemy = GetWorld()->SpawnActor<ATC_CharacterBaseAI>(ActorToSpawn, SpawnTransform, Params))
		{
			
			SpawnerEnemy->SpawnDefaultController();
			Cast<ATC_AIBaseController>(SpawnerEnemy->GetController())->BlackboardComponent->SetValueAsBool("bCanAttack", true);
			SpawnerEnemy->Spawner = this;
			++CurrentEnemisSpawned;
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

FVector ATC_BaseEnemySpawner::GetRandomPointInSphere() const
{
	FVector RandomPoint;

	const float SphereRadius = SphereComponent->GetScaledSphereRadius();
	const float RandomSpherePoint = UKismetMathLibrary::RandomFloatInRange(0.f, SphereRadius);
	const FVector& RandomUnitVector = UKismetMathLibrary::RandomUnitVector();
	
	RandomPoint = SphereComponent->GetComponentLocation();
	RandomPoint +=(RandomUnitVector * RandomSpherePoint);

	// RandomPoint.Z = 228.001297;

	return RandomPoint;
}

void ATC_BaseEnemySpawner::RemoveAttackingEnemy(ATC_CharacterBaseAI* Enemy)
{
	if (!AttackManager.Get())
		return;
	AttackManager.Get()->RemoveAttackingEnemy(Enemy);
}

void ATC_BaseEnemySpawner::RemoveWaitingEnemy(ATC_CharacterBaseAI* Enemy)
{
	if (!AttackManager.Get())
		return;
	AttackManager.Get()->RemoveWaitingEnemy(Enemy);
}

bool ATC_BaseEnemySpawner::AddAttackingEnemy(ATC_CharacterBaseAI* Enemy) const
{
	if (!AttackManager.Get())
		return false;

	return AttackManager.Get()->AddCurrentAttackingEnemies(Enemy);
}

bool ATC_BaseEnemySpawner::IsEnemyAttacking(ATC_CharacterBaseAI* Enemy) const
{
	if (!AttackManager.Get())
		return false;

	return AttackManager.Get()->IsEnemyAttacking(Enemy);
}

bool ATC_BaseEnemySpawner::IsEnemyWaiting(ATC_CharacterBaseAI* Enemy) const
{
	if (!AttackManager.Get())
		return false;

	return AttackManager.Get()->IsEnemyWaiting(Enemy);
}

void ATC_BaseEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

