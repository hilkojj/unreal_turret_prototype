#pragma once

#include "GameFramework/ProjectileMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

/**
 * Bullets are spawned by Weapons, and they do damage to Enemies
 **/
UCLASS()
class UNREAL_TURRET_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

	// Damage done to enemy upon hit
	float Damage = .5;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *BulletMesh;

	// Projectile Movement is a built-in feature of Unreal.
	UPROPERTY(EditAnywhere, Category = "Components")
	UProjectileMovementComponent *Movement;

	// time to live
	float TimeLeft = 4;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * Called when bullet hits anything
	 **/
	UFUNCTION()
	void OnHit(AActor *Self, AActor *Other, FVector NormalImpulse, const FHitResult& Hit);

};
