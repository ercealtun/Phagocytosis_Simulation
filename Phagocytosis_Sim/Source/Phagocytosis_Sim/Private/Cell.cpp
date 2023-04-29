// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ACell::ACell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// MeshComponent assignments
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

	// CollisionComponent assignments
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetSphereRadius(50.f);
	CollisionComponent->SetupAttachment(MeshComponent);
	
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACell::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void ACell::BeginPlay()
{
	Super::BeginPlay();


	FVector ImpulseDirection =FVector3d(-800.0f,-500.0f,0.0f) ; // Set the impulse direction
	float ImpulseMagnitude = 1.0f;  // Set the impulse magnitude

	// Apply the impulse to the object
	MeshComponent->AddImpulse(ImpulseMagnitude * ImpulseDirection, NAME_None, true);
	

	
}

void ACell::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FString OtherActorName = OtherActor->GetName();
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, OtherActorName);
	}
}

// Called every frame
void ACell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}




