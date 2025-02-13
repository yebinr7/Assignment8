// Fill out your copyright notice in the Description page of Project Settings.


#include "Chapter3GameInstance.h"

UChapter3GameInstance::UChapter3GameInstance()
	:TotalScore(0),
	CurrentLevelIndex(0)
{

}


void UChapter3GameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
 	UE_LOG(LogTemp, Warning, TEXT("Total Score Updated: %d"), TotalScore);
}
