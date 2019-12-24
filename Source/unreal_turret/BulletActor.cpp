// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include "EnemyActor.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(BulletMesh);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->InitialSpeed = 3000;
}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &ABulletActor::OnHit);
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeLeft -= DeltaTime;
	if (TimeLeft <= 0) Destroy();
}

void ABulletActor::OnHit(AActor *Self, AActor *Other, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT!"));
	if (AEnemyActor *Enemy = Cast<AEnemyActor>(Other))
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT ENEMY!"));
		// We hit an enemy
		Enemy->Health -= Damage;
	}
	Destroy();
}
