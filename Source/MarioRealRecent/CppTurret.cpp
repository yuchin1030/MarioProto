// Fill out your copyright notice in the Description page of Project Settings.


#include "CppTurret.h"
#include "Kismet/KismetMathLibrary.h"
#include "TurretAnimInterface.h"

#define OUT


// Sets default values
ACppTurret::ACppTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(Root);

	//Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beam"));
	//Beam->SetupAttachment(TurretMesh, TEXT("BeamSocket"));

	Beam1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beam1"));
	Beam1->SetupAttachment(TurretMesh, TEXT("BeamSocket1"));


	Target1 = CreateDefaultSubobject<USceneComponent>(TEXT("Target1"));
	Target1->SetupAttachment(Root);

	Target2 = CreateDefaultSubobject<USceneComponent>(TEXT("Target2"));
	Target2->SetupAttachment(Root);

	FollowTarget = CreateDefaultSubobject<USceneComponent>(TEXT("FollowTarget"));
	FollowTarget->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ACppTurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(Timerhandle, this, &ACppTurret::ChangeBeamTarget, ChangeTargetDelay, true, 1.f);
	
}

// Called every frame
void ACppTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLookAtTarget(DeltaTime);

}
//타겟 쫓아가게 만들기
void ACppTurret::UpdateLookAtTarget(float DeltaTime)
{
	if (ChangeNumber < 4) {
		if (LookAtRotation.Equals(TargetRotation, 1.f)) {
			return;
		}

		//시작과 끝의 로테이션 값을 찾는다.
		LookAtRotation += RotationDelta * RotationRateMultiplier * DeltaTime;

		//인터페이스에 update look at rotation을 추가해서 블루프린트로 다뤘다(자세한 것은ABP_Turret1에)
		if (TurretMesh->GetAnimInstance()->Implements<UTurretAnimInterface>()) {
			ITurretAnimInterface::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
		}
	}
	//여기까지 만들어둔 followtarget의 로테이션 값을 구해 그 방향으로 빔을 쏘는 코드이다.
}

void ACppTurret::ChangeBeamTarget()
{
	TimerCount++;
	if (ChangeNumber < 4) {
		if (TimerCount % 2 == 0) {
			FollowTarget->SetWorldLocation(Target1->GetComponentLocation());
			ChangeNumber++;
		}
		else {
			FollowTarget->SetWorldLocation(Target2->GetComponentLocation());
			ChangeNumber++;
		}
	}
	else {
		Beam1->SetHiddenInGame(false);
	}

	//여기까지 일정 시간이 지나면 타겟을 변경시키는 코드이다.
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket1");
	FVector End = FollowTarget->GetComponentLocation();
	TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	RotationDelta = TargetRotation - LookAtRotation;
	RotationDelta.Normalize();
	//여기까지 목이 돌아갈때 부드럽게 돌아가도록

}
//여기부턴 모자를 날리는 기술
void ACppTurret::Shoot()
{

}
