// Fill out your copyright notice in the Description page of Project Settings.


#include "Overlapper.h"

#include "IPropertyTable.h"
#include "Components/BoxComponent.h"

// Sets default values
AOverlapper::AOverlapper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void AOverlapper::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AOverlapper::OnBoxOverlap);
}

void AOverlapper::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FString OtherActorName = OtherActor->GetName();
	if(GEngine && OtherActor)
	{
		if(OtherActor->ActorHasTag("Cell"))
		{
			//GEngine->AddOnScreenDebugMessage(1,.7f,FColor::Red, TEXT("Yes its the cell"));
		}
		
	}
}

// Called every frame
void AOverlapper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

