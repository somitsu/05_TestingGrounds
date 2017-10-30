// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestingGoundsGameMode.h"
#include "TestingGoundsHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestingGoundsGameMode::ATestingGoundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingGoundsHUD::StaticClass();
}
