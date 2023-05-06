// Fill out your copyright notice in the Description page of Project Settings.


#include "WhiteBloodCell.h"

AWhiteBloodCell::AWhiteBloodCell()
{
}

void AWhiteBloodCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWhiteBloodCell::BeginPlay()
{
	Super::BeginPlay();

	Power = 10.f;
}
