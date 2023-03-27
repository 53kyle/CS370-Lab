// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Engine/EngineTypes.h"
#include "AssaultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API AAssaultWeapon : public AWeapon
{
	GENERATED_BODY()
    
public:
    AAssaultWeapon();
    
    void WeaponTrace();
    
    float FireRate;
    
    float WeaponRange;
    
    FTimerHandle FireTimer;
    
    virtual void OnStartFire() override;
    
    virtual void OnStopFire() override;
    
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem* HitFX;
};
