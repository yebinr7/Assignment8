// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoinItem.h"
#include "SmallCoinItem.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER3_API ASmallCoinItem : public ACoinItem
{
	GENERATED_BODY()
	
public:
	ASmallCoinItem();

	virtual void ActivateItem(AActor* activator) override;

};
