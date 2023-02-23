#include "Characters/TC_TurretBase.h"
#include "Actors/TC_ProjectileBase.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Controllers/TC_AIBaseController.h"
#include "Kismet/KismetMathLibrary.h"

ATC_TurretBase::ATC_TurretBase()
{
	if (USkeletalMeshComponent* MainMesh = GetMesh())
	{
		MainMesh->DestroyComponent();
	}

	PrimaryActorTick.bCanEverTick = true;
	TurretBarrel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBarrel"));
	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBase"));
	TurretTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretTop"));
	SpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPosition"));

	TurretBase->SetupAttachment(RootComponent);
	TurretTop->SetupAttachment(TurretBase, "TopSocket");
	TurretBarrel->SetupAttachment(TurretTop);
	SpawnPosition->SetupAttachment(RootComponent);

}

void ATC_TurretBase::Attack()
{
	ATC_AIBaseController* BaseController = Cast<ATC_AIBaseController>(GetController());
	if (!BaseController)
		return;

	AActor* TargetActor = Cast<AActor>(BaseController->GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>("TargetActor"));
	if (!TargetActor)
		return;

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ATC_ProjectileBase* ProjectileBase = GetWorld()->SpawnActor<ATC_ProjectileBase>(ProjectileToSpawn, SpawnPosition->GetComponentTransform(), Params);
	if (ProjectileBase)
	{
		ProjectileBase->Fire(UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), TargetActor->GetActorLocation()));
	}
}

void ATC_TurretBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimer, this, &ATC_TurretBase::OnDestroyTimer, TimeToDestroy, true);
}

void ATC_TurretBase::OnDestroyTimer()
{
	Destroy();
}
