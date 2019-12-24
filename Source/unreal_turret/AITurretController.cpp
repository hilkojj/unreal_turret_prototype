// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "EnemyActor.h"
#include "TurretPawn.h"
#include "AITurretController.h"

void AAITurretController::Tick(float DeltaTime)
{
    ATurretPawn *Turret = Cast<ATurretPawn>(GetPawn());
    if (!Turret) return; // Controller is not controlling a Turret

    UE_LOG(LogTemp, Warning, TEXT("hi!"));

    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActor::StaticClass(), FoundEnemies);

    if (FoundEnemies.Num() == 0)
    {
        Turret->StopShooting();
        return;
    }

    auto Delta = FoundEnemies[0]->GetActorLocation() - Turret->GetActorLocation();
	float Angle = FMath::RadiansToDegrees(atan2(Delta.Y, Delta.X));

    Turret->TargetTurretAngle = Angle;

    if (FMath::Abs(Turret->PreviousTurretAngle - Turret->TargetTurretAngle) < 10)
        Turret->StartShooting();
    else Turret->StopShooting();
}
