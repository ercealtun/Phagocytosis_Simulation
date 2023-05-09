// Fill out your copyright notice in the Description page of Project Settings.


#include "WhiteBloodCell.h"

#include "BacteriaCell.h"

AWhiteBloodCell::AWhiteBloodCell()
{
	Mesh->SetCollisionProfileName(FName("WhiteBloodCell"));
}

void AWhiteBloodCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWhiteBloodCell::BeginPlay()
{
	Super::BeginPlay();
	SetActorRelativeScale3D(FVector(0.64f,0.64f,0.64f));
	Power = 10.f;
}

void AWhiteBloodCell::OnCellOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABacteriaCell *CastedBacteriaCell = Cast<ABacteriaCell>(OtherActor);
	FString EatenBacteriaCellName = OtherActor->GetName();
	if(CastedBacteriaCell->GetActorScale3D().X < 0.22f)
	{
		if(GEngine)	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("WBC ate the %s"), *EatenBacteriaCellName ));
		OtherActor->Destroy();
	}
}
