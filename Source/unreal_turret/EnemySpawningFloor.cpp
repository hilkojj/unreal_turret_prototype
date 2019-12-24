
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

	if (FMath::Rand() / float(RAND_MAX) < SpawnRate * DeltaTime) // this statement is roughly 'SpawnRate' times per second true.
	{
		// Spawn an enemy!
		// IF limit is not reached...

		TArray<AActor*> FoundEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActor::StaticClass(), FoundEnemies);

		if (FoundEnemies.Num() > MaxEnemiesInWorld)
			return; // limit reached, don't spawn more.

		UE_LOG(LogTemp, Warning, TEXT("SPAWN ENEMY!"));

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		FTransform EnemyTransform;

		// spawn enemy on random place on the floor:
		EnemyTransform.SetLocation(
			GetRandomPositionOnFloor()
		);

		// spawn enemy:
		GetWorld()->SpawnActor<AEnemyActor>(EnemyClass, EnemyTransform, SpawnParams);
	}
}

FVector AEnemySpawningFloor::GetRandomPositionOnFloor()
{
	// Get size of floor:
	FVector FloorOrigin, FloorExtent;
	GetActorBounds(true, FloorOrigin, FloorExtent);

	FloorOrigin -= FloorExtent;
	FloorOrigin.Z = 0;
	FloorExtent *= 2;

	return FloorOrigin + FloorExtent * FVector(FMath::Rand() / float(RAND_MAX), FMath::Rand() / float(RAND_MAX), 0);
}

