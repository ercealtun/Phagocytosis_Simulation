// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "BacteriaCell.generated.h"

/**
 * 
 */
UCLASS()
class PHAGOCYTOSIS_SIM_API ABacteriaCell : public ACell
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABacteriaCell();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Division related methods & variables
	void Division();
	void SpawnNewerCells();

	UPROPERTY(VisibleAnywhere)
	FTimerHandle DivisionTimerHandle;

	float NewerCellRadius;
	
};
