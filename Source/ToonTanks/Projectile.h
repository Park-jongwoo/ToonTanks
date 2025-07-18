// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Camera/CameraShakeBase.h"
#include "Projectile.generated.h"


class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	class UParticleSystemComponent* TrailParticle;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
