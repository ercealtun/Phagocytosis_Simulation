// Fill out your copyright notice in the Description page of Project Settings.


#include "Overlapper.h"

#include "IPropertyTable.h"
#include "Components/BoxComponent.h"

// Sets default values
AOverlapper::AOverlapper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create collision component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetBoxExtent(FVector(50.f,50.f,50.f)); // Set collision box size
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // Set collision settings
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetLinearDamping(0.0f);
	CollisionComponent->SetAngularDamping(0.0f);

}

// Called when the game starts or when spawned
void AOverlapper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOverlapper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

