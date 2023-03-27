// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RootComponent"));
    
    RootComponent = WeaponMesh;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnStartFire() {
    if (FireAC == NULL) {
        FireAC = AWeapon::PlayWeaponSound(FireLoopSound);
    }
    else if (FireAC->IsPlaying() == false) {
        FireAC->Play();
    }
    
    if (FirePSC == NULL) {
        FirePSC = AWeapon::StartParticleSystem(MuzzleFX);
    }
    else {
        FirePSC->ActivateSystem();
    }
}

void AWeapon::OnStopFire() {
    if (FireAC != NULL) {
        FireAC->Stop();
    }
    UGameplayStatics::SpawnSoundAttached(FireFinishSound, RootComponent);
    if (FirePSC != NULL) {
        FirePSC->DeactivateSystem();
    }
}

UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* Sound) {
    UAudioComponent* AC = NULL;
    
    if(Sound) {
        AC = UGameplayStatics::SpawnSoundAttached(Sound, RootComponent);
    }
    
    return AC;
}

UParticleSystemComponent* AWeapon::StartParticleSystem(UParticleSystem* System) {
    UParticleSystemComponent* PSC = NULL;
    
    if(System) {
        PSC = UGameplayStatics::SpawnEmitterAttached(System, RootComponent, TEXT("MuzzleFlashSocket"));
    }
    
    PSC->bAutoActivate = false;
    PSC->bAutoDestroy = false;
    
    return PSC;
}
