// Fill out your copyright notice in the Description page of Project Settings.

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

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<TSubclassOf<AWeaponActor>> WeaponClasses;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	float WeaponLocationZOffset = 100;

	AWeaponActor *Weapon;

	float TargetTurretAngle = 0;
	float PreviousTurretAngle = 0;
	
	void SwapWeapon(TSubclassOf<AWeaponActor> Class);

	void RotateToTarget(float DeltaTime);

	void MouseXMoved(float Amount);

	void StartShooting();

	void StopShooting();

	int CurrentWeaponIndex = -1;

	void NextWeapon();

	friend AAITurretController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
