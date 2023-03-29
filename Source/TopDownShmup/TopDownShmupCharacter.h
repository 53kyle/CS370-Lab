// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "SpawnManager.h"
#include "Weapon.h"
#include "TopDownShmupCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDownShmupCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
    
    UPROPERTY(EditAnywhere, Category = "Weapon")
    TSubclassOf<AWeapon> WeaponClass;

public:
	ATopDownShmupCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    void OnStartFire();
    
    void OnStopFire();
    
    void Die();
    
    void SpawnCharacter();
    
    UPROPERTY(EditAnywhere, Category = "Health")
    float Health = 100;
    
    bool IsDead();
    
    FTimerHandle DeathTimer;
    
private:
    AWeapon* MyWeapon;
    
    bool Dead = false;
    
protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* DeathAnim;
};

