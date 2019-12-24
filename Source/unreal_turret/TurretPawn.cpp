#include <cmath>

#include "TurretPawn.h"
#include "Components/InputComponent.h"

// Sets default values
ATurretPawn::ATurretPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RotatingMesh = CreateDefaultSubobject<UStaticMeshComponent>("RotatingMesh");

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetRelativeLocation(FVector(-1000, 0, 800));
	Camera->SetRelativeRotation(FRotator(-45, 0, 0));
	Camera->SetupAttachment(BaseMesh);

	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();

	NextWeapon();
}

void ATurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MouseX", this, &ATurretPawn::MouseXMoved);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATurretPawn::StartShooting);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATurretPawn::StopShooting);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &ATurretPawn::NextWeapon);
}

void ATurretPawn::MouseXMoved(float Amount)
{
	if (Amount == 0)
	{
		// stop rotating turret when mouse stops moving:
		TargetTurretAngle = PreviousTurretAngle;
		return;
	}
	if (FMath::Abs(TargetTurretAngle + Amount - PreviousTurretAngle) < 180)
		TargetTurretAngle += Amount;
}

void ATurretPawn::StartShooting()
{
	if (Weapon) Weapon->Shooting = true;
}

void ATurretPawn::StopShooting()
{
	if (Weapon) Weapon->Shooting = false;
}

void ATurretPawn::NextWeapon()
{
	if (WeaponClasses.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Turret has 0 weapons!"));
		return;
	}

	CurrentWeaponIndex++;
	if (!WeaponClasses.IsValidIndex(CurrentWeaponIndex))
		CurrentWeaponIndex = 0;

	SwapWeapon(WeaponClasses[CurrentWeaponIndex]);
}

void ATurretPawn::SwapWeapon(TSubclassOf<AWeaponActor> Class)
{
	if (Weapon)
	{
		// remove the old weapon
		if (!Weapon->Destroy())
		{
			UE_LOG(LogTemp, Error, TEXT("Could not destroy weapon!"));
			return;
		}
	}

	if (!Class) return; // there will be no new weapon

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	Weapon = GetWorld()->SpawnActor<AWeaponActor>(Class, SpawnParams);

	Weapon->AttachToComponent(RotatingMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Weapon->AddActorLocalOffset(FVector(0, 0, WeaponLocationZOffset));
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateToTarget(DeltaTime);
}

void ATurretPawn::RotateToTarget(float DeltaTime)
{
	// auto Delta = GetActorLocation() - Target;
	// float Angle = FMath::RadiansToDegrees(atan2(Delta.Y, Delta.X));

	float DeltaAngle = std::fmodf(TargetTurretAngle, 360) - PreviousTurretAngle;
	if (DeltaAngle < -180) DeltaAngle += 360;
	else if (DeltaAngle > 180) DeltaAngle -= 360;

	float MaxStep = Weapon->TurretRotationSpeed * DeltaTime;

	float
		Step = FMath::Max(-MaxStep, FMath::Min(MaxStep, DeltaAngle)),

		NewAngle = std::fmodf(PreviousTurretAngle + Step, 360);

	RotatingMesh->SetWorldRotation(FRotator(0, NewAngle, 0));

	PreviousTurretAngle = NewAngle;
}

