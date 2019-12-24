// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITurretController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_TURRET_API AAITurretController : public AAIController
{
	GENERATED_BODY()
	

public:

	void Tick(float DeltaTime) override;


};
