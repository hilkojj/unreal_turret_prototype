#pragma once

#include "EnemyActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawningFloor.generated.h"

/**
 * The Enemy Spawning Floor is the Floor in the game that spawns enemies on it.
 **/
UCLASS()
class UNREAL_TURRET_API AEnemySpawningFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawningFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *Mesh;

	// Nr of enemies spawned per second (roughly)
	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnRate = .3;

	// Stop spawning when this nr of enemies is reached:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int MaxEnemiesInWorld = 20;

	// Enemy Blueprint:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AEnemyActor> EnemyClass;

	FVector GetRandomPositionOnFloor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
