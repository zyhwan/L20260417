// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"

// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

