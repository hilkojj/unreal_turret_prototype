#pragma once

#include "BulletActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

/**
 * A Weapon can shoot bullets with a certain Damage at a certain FireRate
 **/
UCLASS()
class UNREAL_TURRET_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	// The rotation speed of a Turret. Heavy weapons should rotate slower. (Degrees/Second)
	UPROPERTY(EditAnywhere, Category = "Weapon settings")
	float TurretRotationSpeed = 10;

	bool Shooting = false; // Set to true to start shooting

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Weapon mesh")
	UStaticMeshComponent *Mesh;
	
	// Bullets per second
	UPROPERTY(EditAnywhere, Category = "Weapon settings")
	float FireRate = 10;

	// Damage that a bullet does to an enemy
	UPROPERTY(EditAnywhere, Category = "Weapon settings")
	float BulletDamage = .4;

	// Bullet blueprint
	UPROPERTY(EditAnywhere, Category = "Weapon settings")
	TSubclassOf<ABulletActor> BulletClass;

	float TimeSinceLastShot = 99;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
