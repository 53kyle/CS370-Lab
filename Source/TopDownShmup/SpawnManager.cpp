// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"



void ASpawnManager::BeginPlay() {
    Super::BeginPlay();
    
    SpawnCharacter();
    
}
void ASpawnManager::SpawnCharacter() {
    //ask about this later, need to know how weapon spawns were handled.
    if (DwarfCharacter) {
        UWorld* World = GetWorld();
        
        if (World) {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            
            FRotator Rotation(0.0f, 0.0f, -90.0f);
            
            int32 TArraySize = targetPoints.Num();
            
            MyCharacter = World->SpawnActor<ACharacter>(DwarfCharacter, targetPoints[FMath::RandRange(0,TArraySize-1)]->GetTargetLocation(), Rotation, SpawnParams);
            
            if (MyCharacter) {
                           //AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("WeaponPoint"));
                MyCharacter->AttachToComponent(MyCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("RootComponent"));
                MyCharacter->SpawnDefaultController();
            }
            
            
        }
    }

    //refer to the document for specific smaller details that are still important.
}
