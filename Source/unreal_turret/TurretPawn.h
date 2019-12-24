#pragma once

#include "WeaponActor.h"

#include "Components/StaticMeshComponent.h"
#include "Classes/Camera/CameraComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretPawn.generated.h"

class AAITurretController;

UCLASS()
class UNREAL_TURRET_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurretPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent *BaseMesh;
	
	UPROPERTY(EditAnywhere, Category = "Meshes")
	UStaticMeshComponent *RotatingMesh;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent *Camera;

	// This list contains all Weapon blueprints that the player can equip. (Pressing spacebar will make the turret switch to the next Weapon in the list)
	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<TSubclassOf<AWeaponActor>> WeaponClasses;

	// Index of currently equipped weapon
	int CurrentWeaponIndex = -1;

	// equips the next Weapon at index CurrentWeaponIndex++
	void NextWeapon();

	// The weapon's vertical offset relative to the turret's base
	UPROPERTY(EditAnywhere, Category = "Weapons")
	float WeaponLocationZOffset = 100;

	// The currently equipped weapon
	AWeaponActor *Weapon;

	// Angle to aim for
	float TargetTurretAngle = 0;

	// Current angle
	float PreviousTurretAngle = 0;
	
	// Destroys current weapon and equips new one.
	void SwapWeapon(TSubclassOf<AWeaponActor> Class);

	// Rotate towards this.PreviousTurretAngle, speed depends on Weapon.TurretRotationSpeed
	void RotateToTarget(float DeltaTime);

	// Called when player moves mouse vertically, this will update TargetTurretAngle. Not used by AI
	void MouseXMoved(float Amount);

	// Make the weapon start shooting
	void StartShooting();

	// Make the weapon stop shooting
	void StopShooting();

	friend AAITurretController; // the AI is allowed to control the turret

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
