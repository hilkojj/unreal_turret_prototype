// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawningFloor.generated.h"

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

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnRate = .3;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	int MaxEnemiesInWorld = 20;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AEnemyActor> EnemyClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
