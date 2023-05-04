// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetEnableGravity(false);
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetLinearDamping(0.0f);
	MeshComponent->SetAngularDamping(0.0f);
	MeshComponent->SetWorldScale3D(FVector(100.f,100.f,100.f));
	RootComponent = MeshComponent;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere"));
	if(SphereMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(SphereMesh.Object);
	}


	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetSphereRadius(50.f);
	CollisionComponent->SetupAttachment(MeshComponent);
	
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();


	FVector ImpulseDirection = FVector3d(-400.0f,-400.0f,0.0f) ; // Set the impulse direction
	float ImpulseMagnitude = 1.0f;  // Set the impulse magnitude
	// Apply the impulse to the object
	MeshComponent->AddImpulse(ImpulseMagnitude * ImpulseDirection, NAME_None, true);
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACell::OnSphereOverlap);

	
}

void ACell::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GEngine && OtherActor)
	{
		if(OtherActor->ActorHasTag("Overlapper"))
		{
			GEngine->AddOnScreenDebugMessage(1,.3f,FColor::Red, TEXT("Yes its the cell"));

			CurrentDirection.X = -CurrentDirection.X;
			CurrentDirection.Y = -CurrentDirection.Y;
			
			float ImpulseMagnitude = 1.0f;  // Set the impulse magnitude
			MeshComponent->AddImpulse(ImpulseMagnitude * CurrentDirection, NAME_None, true);
			
		}
		
	}
}


// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	CurrentDirection = GetActorForwardVector();
	
	
}




