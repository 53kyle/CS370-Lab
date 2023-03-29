// Fill out your copyright notice in the Description page of Project Settings.


#include "DwarfCharacter.h"
#include "AIDwarfController.h"

ADwarfCharacter::ADwarfCharacter() {
    AIControllerClass = AAIDwarfController::StaticClass();
}

void ADwarfCharacter::Attack() {
    UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->TakeDamage(DwarfDamage, FDamageEvent(), GetInstigatorController(), this);
}

void ADwarfCharacter::Die() {
    Destroy();
}

void ADwarfCharacter::StartAttack() {
    if (!GetWorldTimerManager().IsTimerActive(AttackTimer)) {
        GetWorldTimerManager().SetTimer(AttackTimer, this, &ADwarfCharacter::Attack, PlayAnimMontage(AttackAnim), true);
    }
}

void ADwarfCharacter::StopAttack() {
    GetWorldTimerManager().ClearTimer(AttackTimer);
    StopAnimMontage(AttackAnim);
}

float ADwarfCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
    float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    if (ActualDamage > 0.0f) {
        if (GEngine)
            {
                GEngine->ClearOnScreenDebugMessages();
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Dwarf Hit!")));
            }
        //Reduce health points
        Health -= ActualDamage;
        if (Health <= 0.0f)
        {
            // We're dead
            SetCanBeDamaged(false); // Don't allow further damage
            
            // Stop attack animation,
            StopAttack();
            
            // UnPossess the AI controller,
            Controller->UnPossess();
            
            // Remove the dwarf from the world
            GetWorldTimerManager().SetTimer(DeathTimer, this, &ADwarfCharacter::Die, PlayAnimMontage(DeathAnim), false);
        }
    }
   return ActualDamage;
}
