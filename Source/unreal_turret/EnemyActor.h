#pragma once

#include "Components/MaterialBillboardComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

/**
 * An enemy has Health and moves around.
 * They also show a HealthBar above them.
 **/
UCLASS()
class UNREAL_TURRET_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

	float Health = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent *Mesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UMaterialBillboardComponent *HealthBarBillboard;

	// The direction this enemy moves back and forth
	FVector MoveDirection;

	// The distance this enemy travels in MoveDirection
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementMultiplier = 200;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
