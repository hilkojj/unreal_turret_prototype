// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BulletActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class UNREAL_TURRET_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	UPROPERTY(EditAnywhere, Category = "Weapon settings")
	float TurretRotationSpeed = 10;

	bool Shooting = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapon mesh")
	UStaticMeshComponent *Mesh;
	
	UPROPERTY(EditAnywhere, Category = "Weapon settings")
	float FireRate = 10;

	UPROPERTY(EditAnywhere, Category = "Weapon settings")
	float BulletDamage = .4;

	UPROPERTY(EditAnywhere, Category = "Weapon settings")
	TSubclassOf<ABulletActor> BulletClass;

	float TimeSinceLastShot = 99;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
