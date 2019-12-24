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
	if (TimeLeft <= 0) Destroy(); // bullet has lived for too long and is probably not gonna hit anything anymore.
}

void ABulletActor::OnHit(AActor *Self, AActor *Other, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AEnemyActor *Enemy = Cast<AEnemyActor>(Other))
	{
		UE_LOG(LogTemp, Warning, TEXT("ENEMY HIT!"));
		// We hit an enemy
		Enemy->Health -= Damage;
	}
	Destroy(); // Destroy bullet after hitting anything.
}
