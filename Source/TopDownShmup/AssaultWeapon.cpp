// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultWeapon.h"

AAssaultWeapon::AAssaultWeapon() {
    FireRate = 5.0f;
    WeaponRange = 10000.0f;
}

void AAssaultWeapon::WeaponTrace() {
    static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
    static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));
    
    // Start from the muzzle's position
    FVector StartPos = WeaponMesh->GetSocketLocation(MuzzleSocket);
    // Get forward vector of MyPawn
    FVector Forward = MyPawn->GetActorForwardVector();
    // Calculate end position
    FVector EndPos = 10000 * Forward;
    
    // Perform the line trace to retrieve hit info
    FCollisionQueryParams TraceParams(WeaponFireTag, true, GetInstigator());
    
    // This fires the ray and checks against all objects w/ collision
    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos, FCollisionObjectQueryParams::AllObjects, TraceParams);
    
    // Did this hit anything?
    if (Hit.bBlockingHit) {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, Hit.Location);
    }
}

void AAssaultWeapon::OnStartFire() {
    Super::OnStartFire();
    
    if (!GetWorldTimerManager().IsTimerActive(FireTimer)) {
        GetWorldTimerManager().SetTimer(FireTimer, this, &AAssaultWeapon::WeaponTrace, 1/FireRate, true, 0.0f);
    }
    
    if (GEngine)
        {
            GEngine->ClearOnScreenDebugMessages();
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Firing")));
        }
}

void AAssaultWeapon::OnStopFire() {
    Super::OnStopFire();
    
    GetWorldTimerManager().ClearTimer(FireTimer);
    
    if (GEngine)
        {
            GEngine->ClearOnScreenDebugMessages();
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Not Firing")));
        }
}
