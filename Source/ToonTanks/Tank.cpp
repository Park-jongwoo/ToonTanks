// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Rotator.h"
#include "DrawDebugHelpers.h"


ATank::ATank()
{


	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Bind the Move function to the input axis "MoveForward"
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, 
			false, 
			HitResult);
		FVector HitLocation = HitResult.ImpactPoint;
		DrawDebugSphere(GetWorld(), HitLocation, 25.f, 12, FColor::Green, false, -1.f);
	}


};
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());

	DrawDebugSphere(GetWorld(), GetActorLocation() + FVector(0.f, 0.f, 200.f),
		100.f, 12, FColor::Red,
		true,
		30.f);
}

void ATank::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;
	AddActorLocalRotation(DeltaRotation, true);

}