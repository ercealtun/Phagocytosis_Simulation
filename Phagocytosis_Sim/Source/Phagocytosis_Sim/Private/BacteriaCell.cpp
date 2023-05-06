// Fill out your copyright notice in the Description page of Project Settings.


#include "BacteriaCell.h"

ABacteriaCell::ABacteriaCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABacteriaCell::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABacteriaCell::BeginPlay()
{
	Super::BeginPlay();
	
	// ABacteriaCell::Division method called every 5 seconds
	GetWorldTimerManager().SetTimer(DivisionTimerHandle, this, &ABacteriaCell::Division, 5.0f);
}

void ABacteriaCell::Division()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 16.0f, FColor::Blue, TEXT("Hello there"));
	}
	SpawnNewerCells();
}

void ABacteriaCell::SpawnNewerCells()
{
	// Any of the XYZ axises can be taken here, because all the axises have the same scale
	NewerCellRadius = GetActorRelativeScale3D().X * 0.5;

	// FActorSpawnParameters structure is defined to determine the properties of the object to be spawned
	FActorSpawnParameters SpawnInfo;

	// This line of code specifies a method when spawning an Actor, where collisions are taken care of
	// and spawn still performed in the event of a collision
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Mother cell position before splitting
	FVector SplitPosition = GetActorLocation();

	// Mother cell rotation before splitting
	FRotator SplitRotation = GetActorRotation();

	// Destroy mother mesh before splitting
	Mesh->DestroyComponent();

	// Splitting
	if(GetWorld()) // Procedural checking if world exists or not
	{
		for(int i=0;i<FMath::RandRange(1,4);++i)
		{
			FVector NewLocation = SplitPosition + FVector(FMath::RandRange(-100.f, 100.f), FMath::RandRange(-100.f, 100.f), 0.f);

			FTransform SpawnTransform = FTransform(SplitRotation, NewLocation, FVector(NewerCellRadius, NewerCellRadius, NewerCellRadius));

			GetWorld()->SpawnActor<ABacteriaCell>(this->GetClass(), SpawnTransform, SpawnInfo);
		}
	}
}


