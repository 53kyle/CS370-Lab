// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
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
    TSubclassOf<ACharacter> BP_Dwarf;
     UPROPERTY(EditAnywhere, Category = "MinSpawnTime")
    float minspawntime = 1.0f;
     UPROPERTY(EditAnywhere, Category = "MaxSpawnTime")
    float maxspawntime = 2.0f;
     
    void SpawnCharacter();
    

	
};
