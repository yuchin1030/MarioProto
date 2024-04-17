// Fill out your copyright notice in the Description page of Project Settings.


#include "CppTurret.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharacterInterface.h"
#include "TurretAnimInterface.h"
#include "MarioRealRecentCharacter.h"
#include <../../../../../../../Source/Runtime/Engine/Classes/Components/ArrowComponent.h>
#include "Koopa_ball.h"
#include <Koopa_Violethat.h>
#include <Koopa_WhiteHat.h>

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


	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	spawnArrow->SetupAttachment(Beam1);

	violet1 = CreateDefaultSubobject<UArrowComponent>(TEXT("violet1"));
	violet1->SetupAttachment(TurretMesh);

	violet2 = CreateDefaultSubobject<UArrowComponent>(TEXT("violet2"));
	violet2->SetupAttachment(TurretMesh);

	violet3 = CreateDefaultSubobject<UArrowComponent>(TEXT("violet3"));
	violet3->SetupAttachment(TurretMesh);

	violet4 = CreateDefaultSubobject<UArrowComponent>(TEXT("violet4"));
	violet4->SetupAttachment(TurretMesh);

	violet5 = CreateDefaultSubobject<UArrowComponent>(TEXT("violet5"));
	violet5->SetupAttachment(TurretMesh);

	violet6 = CreateDefaultSubobject<UArrowComponent>(TEXT("violet6"));
	violet6->SetupAttachment(TurretMesh);

	violet7 = CreateDefaultSubobject<UArrowComponent>(TEXT("violet7"));
	violet7->SetupAttachment(TurretMesh);

	violet8 = CreateDefaultSubobject<UArrowComponent>(TEXT("violet8"));
	violet8->SetupAttachment(TurretMesh);

	white = CreateDefaultSubobject<UArrowComponent>(TEXT("White"));
	white->SetupAttachment(TurretMesh);

}

// Called when the game starts or when spawned
void ACppTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ChangeTargetTimerhandle, this, &ACppTurret::ChangeBeamTarget, ChangeTargetDelay, true, 1.f);	
	GetWorldTimerManager().SetTimer(TraceTimerhandle, this, &ACppTurret::TraceBeam, .1f, true, .1f);

	//GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet1->GetComponentLocation(), violet1->GetComponentRotation());
	//GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet2->GetComponentLocation(), violet2->GetComponentRotation());
	//GetWorld()->SpawnActor<AKoopa_WhiteHat>(white_bp, white->GetComponentLocation(), white->GetComponentRotation());
	//GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet3->GetComponentLocation(), violet3->GetComponentRotation());
	//GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet4->GetComponentLocation(), violet4->GetComponentRotation());
	//GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet5->GetComponentLocation(), violet5->GetComponentRotation());
	//GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet6->GetComponentLocation(), violet6->GetComponentRotation());
	//GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet7->GetComponentLocation(), violet7->GetComponentRotation());
	//GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet8->GetComponentLocation(), violet8->GetComponentRotation());
	
	//TurretMesh->PlayAnimation(Anims[0], false);
}

// Called every frame
void ACppTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("%f"),anyTime);
	currentTime += DeltaTime;
	anyTime += DeltaTime;
	if (anyTime < 20) {
	//if(currentTime<120&&currentTime>60){
		if (Enemy) {
			FollowEnemy(DeltaTime);
			if (currentTime > BalldelayTime) {
			UE_LOG(LogTemp,Warning,TEXT("hi"));
			//���� ��ź ������
			GetWorld()->SpawnActor<AKoopa_ball>(enemy_bp, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());

			currentTime = 0;
			}
		}
		else {
			UpdateLookAtTarget(DeltaTime);
			if (currentTime > BalldelayTime) {
			//	UE_LOG(LogTemp, Warning, TEXT("hiiiiiiiiiiiiiiiiiiii"));
			//���� ��ź ������
			GetWorld()->SpawnActor<AKoopa_ball>(enemy_bp, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());
			//GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet1->GetComponentLocation(), violet1->GetComponentRotation());
			
			currentTime = 0;
			}
		}
	}
	if ( anyTime>62&& anyTime < 73) {
		UpdateLookAtTarget(DeltaTime);
		if (currentTime > delayTime) {
		GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet1->GetComponentLocation(), violet1->GetComponentRotation());
		GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet2->GetComponentLocation(), violet2->GetComponentRotation());
		GetWorld()->SpawnActor<AKoopa_WhiteHat>(white_bp, white->GetComponentLocation(), white->GetComponentRotation());
		GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet3->GetComponentLocation(), violet3->GetComponentRotation());
		GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet4->GetComponentLocation(), violet4->GetComponentRotation());
		GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet5->GetComponentLocation(), violet5->GetComponentRotation());
		GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet6->GetComponentLocation(), violet6->GetComponentRotation());
		GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet7->GetComponentLocation(), violet7->GetComponentRotation());
		GetWorld()->SpawnActor<AKoopa_Violethat>(violet_bp, violet8->GetComponentLocation(), violet8->GetComponentRotation());
		currentTime = 0;
		}
	}
}
	//TraceBeam();

//}
//Ÿ�� �Ѿư��� �����
void ACppTurret::UpdateLookAtTarget(float DeltaTime)
{
	if (ChangeNumber < 100) {

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
	
//	if (ChangeNumber < 10) {
		if (TimerCount % 2 == 0) {
			FollowTarget->SetWorldLocation(Target1->GetComponentLocation());
			ChangeNumber++;
		
		}
		else {
			FollowTarget->SetWorldLocation(Target2->GetComponentLocation());
			ChangeNumber++;
		}
//	}
	//else {
	//	Beam1->SetHiddenInGame(false);
	//}

	//������� ���� �ð��� ������ Ÿ���� �����Ű�� �ڵ��̴�.
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket1");
	FVector End = FollowTarget->GetComponentLocation();
	TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	RotationDelta = TargetRotation - LookAtRotation;
	RotationDelta.Normalize();
	//������� ���� ���ư��� �ε巴�� ���ư�����

}
// ����Ʈ���̽��� ĳ���Ϳ��� �浹 ����
void ACppTurret::TraceBeam()
{
	
	FHitResult HitResult;
	FVector Start =TurretMesh->GetSocketLocation("BeamSocket");
	FVector End=Start+Beam1->GetRightVector()* -3000;

	FCollisionObjectQueryParams objQueryParams;
	objQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	objQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	//�浹 üũ���� ������ ���� �Ǵ� ������Ʈ
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);
	bool bResult = GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, objQueryParams, queryParams);
	
	if (bResult)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.ImpactPoint, FColor(0, 255, 0), false, 2.0f, 0, 1);
		CheckEnemy(HitResult.GetActor());
		//UE_LOG(LogTemp, Warning, TEXT("%s"),*HitResult.GetActor()->GetActorNameOrLabel());
		}
	else {
		
	}
// 	FCollisionQueryParams CollQueryParams;
// 	CollQueryParams.AddIgnoredActor(this);
// 
// 	bool bHit=GetWorld()->LineTraceSingleByChannel(OUT HitResult, Start, End, ECollisionChannel::ECC_Camera, CollQueryParams);
// 
// 	if (bHit) {
// 		CheckEnemy(HitResult.GetActor());
// 	}
// 	else{
// 		UE_LOG(LogTemp, Warning, TEXT("else"));
// 	}
}

void ACppTurret::CheckEnemy(AActor* HitActor) 
{
	if (HitActor->Implements<UCharacterInterface>()) {

		bool bEnemy=ICharacterInterface::Execute_IsEnemy(HitActor);

		if (bEnemy) {
			Enemy=HitActor;
		//	UE_LOG(LogTemp,Warning,TEXT("qqqqqqqqqqqqqqqqqqqqqq"));
		}
		else {
			
		}
	}
}

void ACppTurret::FollowEnemy(float DeltaTime)
{
	FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
	FVector End = Enemy->GetActorLocation();

	FRotator RotationToEnemy=UKismetMathLibrary::FindLookAtRotation(Start,End);

	LookAtRotation=FMath::RInterpTo(LookAtRotation,RotationToEnemy,DeltaTime,10);

	if (TurretMesh->GetAnimInstance()->Implements<UTurretAnimInterface>()) {
		ITurretAnimInterface::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
	}
}

//������� ���ڸ� ������ ���
void ACppTurret::Shoot()
{

}
