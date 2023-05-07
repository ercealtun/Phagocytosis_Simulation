// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell.h"
#include "WhiteBloodCell.generated.h"

/**
 * 
 */
UCLASS()
class PHAGOCYTOSIS_SIM_API AWhiteBloodCell : public ACell
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AWhiteBloodCell();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnCellOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;

private:
	
};
