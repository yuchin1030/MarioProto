// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "CppTurret.generated.h"

UCLASS()
class MARIOREALRECENT_API ACppTurret : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Beam1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Target1;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Target2;


	UPROPERTY(VisibleAnywhere)
	USceneComponent* FollowTarget;

	UPROPERTY()
	FTimerHandle ChangeTargetTimerhandle;

	UPROPERTY()
	FTimerHandle TraceTimerhandle;

	//rotation related variables
	int32 TimerCount = 0;
	FRotator LookAtRotation;
	FRotator TargetRotation;
	FRotator RotationDelta;


	UPROPERTY(EditAnywhere)
	float ChangeTargetDelay=3.5f;

	UPROPERTY(EditAnywhere)
	int32 ChangeNumber=0;

	UPROPERTY(EditAnywhere)
	float RotationRateMultiplier=1.f;

	UFUNCTION()
	void UpdateLookAtTarget(float DeltaTime);

	UFUNCTION()
	void ChangeBeamTarget();

	UFUNCTION()
	void TraceBeam();

	UFUNCTION()
	void Shoot();

	
public:	
	// Sets default values for this actor's properties
	ACppTurret();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USkeletalMeshComponent* TurretMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
