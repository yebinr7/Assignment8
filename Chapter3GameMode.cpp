// Copyright Epic Games, Inc. All Rights Reserved.

#include "Chapter3GameMode.h"
#include "Chapter3Character.h"
#include "UObject/ConstructorHelpers.h"

AChapter3GameMode::AChapter3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// 우리가 만든 GameState로 설정,기본값 변경?
	GameStateClass = AChapter3GameStateBase::StaticClass();
}
