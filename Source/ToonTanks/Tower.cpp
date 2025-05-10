// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());


		if (Distance <= FireRange)
		{
			RotateTurret(Tank->GetActorLocation());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Tank is out of range"));
		}
	}
}


void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank NOT Found"));
	}
}