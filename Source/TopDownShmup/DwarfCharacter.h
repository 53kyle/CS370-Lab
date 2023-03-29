// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "DwarfCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API ADwarfCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
    ADwarfCharacter();
    
    void Attack();
    
    void Die();
    
    void StartAttack();
    
    void StopAttack();
    
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    UPROPERTY(EditAnywhere, Category = "Health")
    float Health = 20.0f;
    
    UPROPERTY(EditAnywhere, Category = "Damage")
    float DwarfDamage = 10.0f;
    
    FTimerHandle AttackTimer;
    
    FTimerHandle DeathTimer;
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* AttackAnim;
    
    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* DeathAnim;
};
