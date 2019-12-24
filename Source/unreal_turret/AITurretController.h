#pragma once

#include "EnemyActor.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "AITurretController.generated.h"

/**
 * The AI Turret Controller is capable of making a TurretPawn aim at enemies and shooting them.
 */
UCLASS()
class UNREAL_TURRET_API AAITurretController : public AAIController
{
	GENERATED_BODY()
	
public:
	void Tick(float DeltaTime) override;
};
