// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetEnableGravity(false);
	Mesh->SetSimulatePhysics(true);

	// Setting the fraction to 0.f
	Mesh->SetLinearDamping(0.0f);
	Mesh->SetAngularDamping(0.0f);

	SetRootComponent(Mesh);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere"));
	if(SphereMesh.Succeeded())
	{
		Mesh->SetStaticMesh(SphereMesh.Object);
	}
	
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();

	float RandomX = FMath::RandRange(0.f,1000.f);
	float RandomY = FMath::RandRange(0.f,1000.f);

	
	FVector ImpulseDirection = FVector3d(RandomX,RandomY,0.0f) ; // Set the impulse direction
	Power = 2.5f;
	
	// Apply impulse to the object
	Mesh->AddImpulse(Power * ImpulseDirection, NAME_None, true);

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACell::OnCellOverlap);

	
}

void ACell::OnCellOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor)
	{
		FString OtherActorName = OtherActor->GetName();
		if(GEngine)	GEngine->AddOnScreenDebugMessage(-1, 16.0f, FColor::Blue, FString::Printf(TEXT("Cell overlapped with %s"), *OtherActorName));
	}
	
}


// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Keep the objects always on the same Z axis
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 360.f));
	
}




