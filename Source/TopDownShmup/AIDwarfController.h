// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEnemyController.h"
#include "AIDwarfController.generated.h"

/**
 * 
 */
UENUM()
enum class EDwarfState
{
    EStart, EChasing, EAttacking, EDead, EUnknown
};

UCLASS()
class TOPDOWNSHMUP_API AAIDwarfController : public AAIEnemyController
{
	GENERATED_BODY()
    
public:
    APawn* MyPawn;
    
    UFUNCTION(BlueprintPure, Category = "State")
    EDwarfState GetState() const;
    
    void SetState(EDwarfState NewState);
    
    UPROPERTY(EditDefaultsOnly, Category = "AI Properties")
    float Range;
    
private:
    EDwarfState CurrentState;
	
protected:
    virtual void OnPossess(APawn* InPawn) override;
    
    virtual void OnUnPossess() override;
    
    virtual void BeginPlay() override;
    
    virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
    
public:
    virtual void Tick(float DeltaTime) override;
};
