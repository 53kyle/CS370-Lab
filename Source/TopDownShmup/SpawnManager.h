// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "DwarfCharacter.h"
#include "SpawnManager.generated.h"


UCLASS()
class TOPDOWNSHMUP_API ASpawnManager : public ATargetPoint
{
	GENERATED_BODY()
    
public:
    
     //four "editanywhere" uproperties for later
     UPROPERTY(EditAnywhere, Category = "TArray")
    TArray<ATargetPoint*> targetPoints;
     UPROPERTY(EditAnywhere, Category = "ACharacter")
    TSubclassOf<ACharacter> DwarfCharacter;
     UPROPERTY(EditAnywhere, Category = "MinSpawnTime")
    float minspawntime = 1.0f;
     UPROPERTY(EditAnywhere, Category = "MaxSpawnTime")
    float maxspawntime = 10.0f;
     
    virtual void SpawnCharacter();
    
private:
    ACharacter* MyCharacter;

	
};
