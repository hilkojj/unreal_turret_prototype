
#include "WeaponActor.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	// Print the weapon's properties to the screen:
	FString Message = FString::Printf(
		TEXT("---WEAPON PROPERTIES:---\nFire Rate: %f\nDamage: %f\nTurret Rotation Speed: %f\n------"), 
		FireRate, BulletDamage, TurretRotationSpeed
	);
	GEngine->AddOnScreenDebugMessage(0, 4.f, FColor::Blue, Message); 
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastShot += DeltaTime;

	if (Shooting && TimeSinceLastShot >= 1 / FireRate) // 1/FireRate is the time between shots
	{
		// Shoot!!

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bNoFail = true;

		FTransform BulletTransform;
		BulletTransform.SetLocation(GetActorForwardVector() * 220 + GetActorLocation());
		BulletTransform.SetRotation(GetActorRotation().Quaternion());
		BulletTransform.SetScale3D(FVector(1));

		auto Bullet = GetWorld()->SpawnActor<ABulletActor>(BulletClass, BulletTransform, SpawnParams);
		Bullet->Damage = BulletDamage;

		TimeSinceLastShot = 0;
	}
}

