// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDwarfController.h"
#include "DwarfCharacter.h"
#include "TopDownShmupCharacter.h"
#include "Kismet/GameplayStatics.h"

void AAIDwarfController::OnPossess(APawn* InPawn) {
    Super::OnPossess(InPawn);
    
    MyPawn = InPawn;
}

void AAIDwarfController::BeginPlay() {
    Super::BeginPlay();
    SetState(EDwarfState::EStart);
    
    MoveToActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    
    Range = 150.0f;
}

void AAIDwarfController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) {
    Super::OnMoveCompleted(RequestID, Result);
    
    SetState(EDwarfState::EAttacking);
    
    if (GetState() != EDwarfState::EDead) {
        Cast<ADwarfCharacter>(MyPawn)->StartAttack();
    }
    
    if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Move Completed")));
        }
}

void AAIDwarfController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (GetState() == EDwarfState::EStart) {
        SetState(EDwarfState::EChasing);
    }
    
    FVector DistanceVector = MyPawn->GetPawnViewLocation() - UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetPawnViewLocation();
    
    if (GetState() == EDwarfState::EAttacking && DistanceVector.Size() > Range) {
        SetState(EDwarfState::EChasing);
        MoveToActor(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
        Cast<ADwarfCharacter>(MyPawn)->StopAttack();
    }
    
    if (GetState() == EDwarfState::EAttacking && Cast<ATopDownShmupCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->IsDead() == true) {
        Cast<ADwarfCharacter>(MyPawn)->StopAttack();
    }
}

void AAIDwarfController::OnUnPossess() {
    Super::OnUnPossess();
    
    SetActorTickEnabled(false);
}

EDwarfState AAIDwarfController::GetState() const {
    return CurrentState;
}

void AAIDwarfController::SetState(EDwarfState NewState) {
    CurrentState = NewState;
}
