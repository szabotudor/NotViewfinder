// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGuy.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

// Sets default values
AMainGuy::AMainGuy()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 75.0f));
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainGuy::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AMainGuy::MoveForward(const FInputActionValue& value)
{
	if (value.GetMagnitude() != 0.0f)
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, value.GetMagnitude() * MoveSpeed);
	}
}

void AMainGuy::MoveRight(const FInputActionValue& value)
{
	if (value.GetMagnitude() != 0.0f)
	{
		FVector Right = GetActorRightVector();
		AddMovementInput(Right, value.GetMagnitude() * MoveSpeed);
	}
}

void AMainGuy::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X * LookSpeedLR);

	FRotator CameraRotation = Camera->GetRelativeRotation();
	CameraRotation.Pitch = FMath::ClampAngle(CameraRotation.Pitch + LookInput.Y * LookSpeedUD, -90.0f, 90.0f);
	CameraRotation.Roll = 0.0f;
	CameraRotation.Yaw = 0.0f;
	Camera->SetRelativeRotation(CameraRotation);
}

void AMainGuy::TakePicture()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Picture Taken"));
}

// Called every frame
void AMainGuy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainGuy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AMainGuy::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AMainGuy::MoveRight);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainGuy::Look);
		EnhancedInputComponent->BindAction(TakePictureAction, ETriggerEvent::Completed, this, &AMainGuy::TakePicture);
	}
}

