// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoinItem.h"
#include "BigCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER3_API ABigCoinItem : public ACoinItem
{
	GENERATED_BODY()

public:
	ABigCoinItem();

	//I -> BaseItem -> ... -> ABigCoinItme 런타임 다형성! 
	virtual void ActivateItem(AActor* activator) override;
	
};
