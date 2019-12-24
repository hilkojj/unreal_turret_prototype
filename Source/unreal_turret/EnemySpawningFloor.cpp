// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawningFloor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawningFloor::AEnemySpawningFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

// Called when the game starts or when spawned
void AEnemySpawningFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawningFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FMath::Rand() / float(RAND_MAX) < SpawnRate * DeltaTime)
	{
		// Spawn an enemy!
		// IF limit is not reached...

		TArray<AActor*> FoundEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActor::StaticClass(), FoundEnemies);

		UE_LOG(LogTemp, Warning, TEXT("CURRENT NR OF ENEMIES: %d"), FoundEnemies.Num());

		if (FoundEnemies.Num() > MaxEnemiesInWorld)
			return; // limit reached

		UE_LOG(LogTemp, Warning, TEXT("SPAWN ENEMY!"));

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		FTransform EnemyTransform;

		FVector FloorOrigin, FloorExtent;

		GetActorBounds(true, FloorOrigin, FloorExtent);

		FloorOrigin -= FloorExtent;
		FloorOrigin.Z = 0;
		FloorExtent *= 2;

		EnemyTransform.SetLocation(FloorOrigin + FloorExtent * FVector(FMath::Rand() / float(RAND_MAX), FMath::Rand() / float(RAND_MAX), 0));

		GetWorld()->SpawnActor<AEnemyActor>(EnemyClass, EnemyTransform, SpawnParams);
	}
}

