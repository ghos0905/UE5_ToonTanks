// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::Move(float value)
{

    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation, true);
}
void ATank::Turn(float value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult);

        DrawDebugSphere(
            GetWorld(),
            HitResult.ImpactPoint + FVector(0.f, 0.f, 200.f),
            25.f,
            12,
            FColor::Red,
            false,
            -1.f);
    }
}
