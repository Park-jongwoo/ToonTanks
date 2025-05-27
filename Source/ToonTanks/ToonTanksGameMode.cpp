// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GamePlayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	// Handle the death of the actor
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		
	}

	else if (ATower* DestroyTower = Cast<ATower>(DeadActor))
	{
		DestroyTower->HandleDestruction();
	}

}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}