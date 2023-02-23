#include "NewWorld_AICharacter.h"
#include "Camera/CameraComponent.h"
#include "Characters/TC_TurretBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "HeadMountedDisplayFunctionLibrary.h"

ANewWorld_AICharacter::ANewWorld_AICharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	TurretSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("TurretSpawnPosition"));
	TurretSpawnPosition->SetupAttachment(RootComponent);
}

void ANewWorld_AICharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("SpawnTurret", IE_Pressed, this, &ANewWorld_AICharacter::SpawnTurret);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANewWorld_AICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANewWorld_AICharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ANewWorld_AICharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ANewWorld_AICharacter::LookUpAtRate);
}

void ANewWorld_AICharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ANewWorld_AICharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ANewWorld_AICharacter::SpawnTurret()
{
	if (!TurretSpawnPosition || !TurretToSpawn)
		return;

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FVector SpawnPosition = TurretSpawnPosition->GetComponentLocation();
	// This souldn't be this way, but for time purposes we will manage the Z position this way.
	SpawnPosition.Z = 185.001297;

	FTransform NewTransform;
	NewTransform.SetLocation(SpawnPosition);
	NewTransform.SetRotation(TurretSpawnPosition->GetComponentRotation().Quaternion());
	ATC_TurretBase* TurretSpawner = GetWorld()->SpawnActor<ATC_TurretBase>(TurretToSpawn, NewTransform, Params);
	if (TurretSpawner)
	{
		TurretSpawner->SpawnDefaultController();
	}
}

void ANewWorld_AICharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ANewWorld_AICharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
