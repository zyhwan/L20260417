// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = AMyPawn::StaticClass();

	for (TFieldIterator<FProperty> Iter(GetClass()); Iter; ++Iter)
	{
		auto Value = *Iter;
		UE_LOG(LogTemp, Warning, TEXT("Property %s"), *Value->GetName());

	}

}
