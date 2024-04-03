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
	
	GetWorldTimerManager().SetTimer(ChangeTargetTimerhandle, this, &ACppTurret::ChangeBeamTarget, ChangeTargetDelay, true, 1.f);	
	GetWorldTimerManager().SetTimer(TraceTimerhandle, this, &ACppTurret::TraceBeam, .1f, true, .1f);
}

// Called every frame
void ACppTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLookAtTarget(DeltaTime);
	//TraceBeam();

}
//Ÿ�� �Ѿư��� �����
void ACppTurret::UpdateLookAtTarget(float DeltaTime)
{
	if (ChangeNumber < 4) {
		if (LookAtRotation.Equals(TargetRotation, 1.f)) {
			return;
		}

		//���۰� ���� �����̼� ���� ã�´�.
		LookAtRotation += RotationDelta * RotationRateMultiplier * DeltaTime;

		//�������̽��� update look at rotation�� �߰��ؼ� �������Ʈ�� �ٷ��(�ڼ��� ����ABP_Turret1��)
		if (TurretMesh->GetAnimInstance()->Implements<UTurretAnimInterface>()) {
			ITurretAnimInterface::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
		}
	}
	//������� ������ followtarget�� �����̼� ���� ���� �� �������� ���� ��� �ڵ��̴�.
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

	//������� ���� �ð��� ������ Ÿ���� �����Ű�� �ڵ��̴�.
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket1");
	FVector End = FollowTarget->GetComponentLocation();
	TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	RotationDelta = TargetRotation - LookAtRotation;
	RotationDelta.Normalize();
	//������� ���� ���ư��� �ε巴�� ���ư�����

}
// �ʿ� ���� �ڵ�. ���� ���� �� ��ü�� �΋H���� �� ���̸� ��ü�� ������� �ʵ��� �����ϴ� �ڵ��̴�(�� ���� ���� if���� �������� �ʾ� �۵����� �ʴ� �ڵ�)
void ACppTurret::TraceBeam()
{
	FHitResult HitResult;
	FVector Start =TurretMesh->GetSocketLocation("BeamSocket");
	FVector End=Start+Beam1->GetForwardVector()* 1500;

	FCollisionQueryParams CollQueryParams;
	CollQueryParams.AddIgnoredActor(this);

	bool bHit=GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, ECollisionChannel::ECC_Camera, CollQueryParams);

}

//������� ���ڸ� ������ ���
void ACppTurret::Shoot()
{

}
