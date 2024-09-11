// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include <EnhancedInputLibrary.h>

#include "MainGuy.generated.h"


UCLASS()
class NOTVIEWFINDER_API AMainGuy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainGuy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(const FInputActionValue& value);
	void MoveRight(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	void TakePicture();

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float LookSpeedLR = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float LookSpeedUD = 0.75f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveForwardAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveRightAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TakePictureAction = nullptr;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
