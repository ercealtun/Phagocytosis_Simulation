// Fill out your copyright notice in the Description page of Project Settings.


#include "BacteriaCell.h"
#include "Engine/EngineTypes.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/BodyInstance.h"


ABacteriaCell::ABacteriaCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh->SetCollisionProfileName(FName("BacteriaCell"));
}

void ABacteriaCell::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABacteriaCell::BeginPlay()
{
	Super::BeginPlay();
	
	// ABacteriaCell::Division method called every 5 seconds
	GetWorldTimerManager().SetTimer(DivisionTimerHandle, this, &ABacteriaCell::Split, 5.0f);

	SetActorRelativeScale3D(FVector(2.56f,2.56f,2.56f));
}

void ABacteriaCell::Split()
{
	SpawnNewerCells();
}

void ABacteriaCell::SpawnNewerCells()
{
	if(IsSplitReady())
	{
		// Any of the XYZ axises can be taken here, because all the axises have the same scale
		NewerCellRadius = GetActorScale3D() / 3.5f;

		// FActorSpawnParameters structure is defined to determine the properties of the object to be spawned
		FActorSpawnParameters SpawnInfo;

		// This line of code specifies a method when spawning an Actor, where collisions are taken care of
		// and spawn still performed in the event of a collision
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// Mother cell position before splitting
		FVector LastPositionMotherDied = GetActorLocation();

		// Mother cell rotation before splitting
		FRotator LastRotationMotherDied = GetActorRotation();

		// Split phase
		if(GetWorld()) // Procedural checking if world exists or not
		{
			// Destroy mother mesh before splitting
			Mesh->DestroyComponent();
		
			for(int i=0; i < FMath::RandRange(1,4); ++i)
			{
				FVector NewLocation = LastPositionMotherDied + FVector(FMath::RandRange(-100.f, 100.f),FMath::RandRange(-100.f, 100.f), 0.f);
				ABacteriaCell* NewBacteriaCell = GetWorld()->SpawnActor<ABacteriaCell>(GetClass(), NewLocation, LastRotationMotherDied);
				NewBacteriaCell->SetActorRelativeScale3D(NewerCellRadius);
				if(GEngine)	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Bacteria size: %f"), NewBacteriaCell->GetActorScale3D().X));
			}
		}
	}

}

bool ABacteriaCell::IsSplitReady()
{
	if(GetActorScale3D().X >= 0.22f)
	{
		return true;
	}else
	{
		GetWorldTimerManager().ClearTimer(DivisionTimerHandle); // Stopping the timer
		return false;
	}


}

void ABacteriaCell::OnCellOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::OnCellOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}


