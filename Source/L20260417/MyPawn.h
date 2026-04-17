// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <EnhancedInputLibrary.h>

#include "InputAction.h"

#include "MyPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UMyStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class UArrowComponent;


class UInputAction;
class AMyRocket;

UCLASS()
class L20260417_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMyStaticMeshComponent> Left;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UMyStaticMeshComponent> Right;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UFloatingPawnMovement> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float MoveSpeed = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float RotationSpeed = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float BoostValue = 0.5f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	//float PropellerRotationSpeed = 7200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Rotate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Boost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TSubclassOf<AMyRocket> RocketTemplate;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Rotate(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);
	void Boost(const FInputActionValue& Value);
	void UnBoost(const FInputActionValue& Value);
};
