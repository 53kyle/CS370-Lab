// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownShmupCharacter.h"
#include "TopDownShmup.h"

ATopDownShmupCharacter::ATopDownShmupCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void ATopDownShmupCharacter::BeginPlay() {
    Super::BeginPlay();
    
    if(WeaponClass) {
        UWorld* World = GetWorld();
        
        if (World) {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            
            FRotator Rotation(0.0f, 0.0f, -90.0f);
            
            MyWeapon = World->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, Rotation, SpawnParams);
            
            if (MyWeapon) {
                MyWeapon->WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("WeaponPoint"));
            }
        }
    }
    
    MyWeapon->MyPawn = this;
}

void ATopDownShmupCharacter::OnStartFire() {
    if (MyWeapon) {
        MyWeapon->OnStartFire();
    }
}

void ATopDownShmupCharacter::OnStopFire() {
    if (MyWeapon) {
        MyWeapon->OnStopFire();
    }
}

void ATopDownShmupCharacter::Die() {
    GetMesh()->Deactivate();
}

float ATopDownShmupCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
    float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    if (ActualDamage > 0.0f) {
        if (GEngine)
            {
                GEngine->ClearOnScreenDebugMessages();
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Player Hit!")));
            }
        //Reduce health points
        Health -= ActualDamage;
        if (Health <= 0.0f)
        {
            // We're dead
            SetCanBeDamaged(false); // Don't allow further damage
            
            Dead = true;
            
            Controller->SetIgnoreLookInput(true);
            Controller->SetIgnoreMoveInput(true);
            
            GetWorldTimerManager().SetTimer(DeathTimer, this, &ATopDownShmupCharacter::Die, PlayAnimMontage(DeathAnim) - 0.25f, false);
            
            OnStopFire();
        }
    }
   return ActualDamage;
}

bool ATopDownShmupCharacter::IsDead() {
    return Dead;
}
