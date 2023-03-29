// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"



void ASpawnManager::SpawnCharacter() {
    //ask about this later, need to know how weapon spawns were handled.
    if (DwarfCharacter) {
        UWorld* World = GetWorld();
        
        if (World) {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            
            FRotator Rotation(0.0f, 0.0f, -90.0f);
            
            float TArraySize = targetPoints.Num();
            
            MyCharacter = World->SpawnActor<ACharacter>(DwarfCharacter, targetPoints[FMath::FRandRange(0.0f,TArraySize)]->GetTargetLocation(), Rotation, SpawnParams);
            
            if (MyCharacter) {
                MyCharacter->SkeletalMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("DwarfGrunt_R_new"));
            }
            

        }
    }

    //refer to the document for specific smaller details that are still important.
}
