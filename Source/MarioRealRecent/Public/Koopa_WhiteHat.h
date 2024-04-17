// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Koopa_WhiteHat.generated.h"

UCLASS()
class MARIOREALRECENT_API AKoopa_WhiteHat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKoopa_WhiteHat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class UBoxComponent* boxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="MySettings|Components")
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="MySettings|Components")
	class UArrowComponent* arrow;

	UPROPERTY(EditAnywhere, Category="MySettings|Variables")
	int32 traceRate = 50;

	UPROPERTY(EditAnywhere, Category="MySettings|Variables")
	float moveSpeed = 180;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Variables")
	bool bStopRotWhiteHat = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Variables")
	bool bStopLocWhiteHat = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Variables")
	FVector dir;

private:
	FVector moveDirection;

	FRotator WhiteRot= FRotator(0,10,0);

	

};
