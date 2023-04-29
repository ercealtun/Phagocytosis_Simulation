// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Cell.generated.h"


UCLASS()
class PHAGOCYTOSIS_SIM_API ACell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACell();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionComponent;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	


};
