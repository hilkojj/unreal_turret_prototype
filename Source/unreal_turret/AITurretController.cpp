#include "Kismet/GameplayStatics.h"
#include "TurretPawn.h"
#include "AITurretController.h"

void AAITurretController::Tick(float DeltaTime)
{
    ATurretPawn *Turret = Cast<ATurretPawn>(GetPawn());
    if (!Turret) return; // Controller is not controlling a Turret

    // Find ALL enemies:
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActor::StaticClass(), FoundEnemies);

    if (FoundEnemies.Num() == 0)
    {
        Turret->StopShooting(); // No enemies in world. Stop shooting.
        return;
    }

    for (auto Enemy : FoundEnemies)
    {    
        auto Delta = Enemy->GetActorLocation() - Turret->GetActorLocation(); // difference in enemy & turret location

        if (Delta.Size() > 700) continue; // Enemy is probably too far away to shoot at. TODO: don't make range hardcoded.

        float Angle = FMath::RadiansToDegrees(atan2(Delta.Y, Delta.X)); // Angle between enemy & turret

        Turret->TargetTurretAngle = Angle; // Setting Turret->TargetTurretAngle will make the Turret rotate to the new angle.

        float AngleDelta = FMath::Abs(Turret->PreviousTurretAngle - Angle);

        // If the turret is (almost) at the desired angle -> start shooting the enemy
        if (AngleDelta < 20 || AngleDelta > 340)
            Turret->StartShooting();
        else 
            Turret->StopShooting(); // Turret needs to rotate more before the shooting can start.

        break;
    }
}
