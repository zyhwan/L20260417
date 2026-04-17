// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyStaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/ArrowComponent.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyRocket.h"



// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(40.0f, 44.0f, 12.0f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/P38/Body/SM_P38_Body.SM_P38_Body'"));

	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller
	(TEXT("/Script/Engine.StaticMesh'/Game/Assets/P38/Propeller/SM_P38_Propeller.SM_P38_Propeller'"));

	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(37.f, 21.f, 0.f));
	Right->SetRelativeLocation(FVector(37.f, -21.f, 0.f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(150.f, 0.f, 0.f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->TargetArmLength = 150.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetOffset = FVector(0.f, 0.f, 33.f);


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 1000.f;

	static ConstructorHelpers::FClassFinder<AMyRocket> BP_Rocket
	(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Rocket.BP_Rocket_C'"));
	if (BP_Rocket.Succeeded())
	{
		RocketTemplate = BP_Rocket.Class;
	}
}

void AMyPawn::Rotate(const FInputActionValue& Value)
{
	FVector2D Rot = Value.Get<FVector2D>();
	Rot = Rot * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f;

	AddActorLocalRotation(FRotator(Rot.Y, 0, Rot.X));
}

void AMyPawn::Fire(const FInputActionValue& Value)
{
	GetWorld()->SpawnActor<AMyRocket>(RocketTemplate, Arrow->K2_GetComponentToWorld());

}

void AMyPawn::Boost(const FInputActionValue& Value)
{
	BoostValue = 1.0f;
}

void AMyPawn::UnBoost(const FInputActionValue& Value)
{
	BoostValue = 0.5f;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), BoostValue);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &AMyPawn::Rotate);
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPawn::Fire);
		UIC->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPawn::Boost);
		UIC->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPawn::UnBoost);

	}

}

