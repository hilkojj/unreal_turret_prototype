// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	HealthBarBillboard = CreateDefaultSubobject<UMaterialBillboardComponent>("HealthBarBillboard");
	HealthBarBillboard->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	MoveDirection = FMath::VRand();
	MoveDirection.Z = 0; // don't move vertically.
	MoveDirection.Normalize();
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update healthbar billboard:
	auto Billboard = HealthBarBillboard->Elements[0];
	Billboard.BaseSizeY = Health * 80;
	HealthBarBillboard->SetElements(TArray<FMaterialSpriteElement>({ Billboard }));

	// Update movement:
	FVector MoveDelta = MoveDirection * MovementMultiplier * (FMath::Sin(GetWorld()->GetTimeSeconds() + DeltaTime) - FMath::Sin(GetWorld()->GetTimeSeconds()));
	AddActorWorldOffset(MoveDelta, true);

	// Destroy if no health left:
	if (Health <= 0)
	{
		Destroy();
		// todo: register score
	}
}

