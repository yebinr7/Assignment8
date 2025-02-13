// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallCoinItem.h"

ASmallCoinItem::ASmallCoinItem()
{
	PointValue = 10;
	ItemType = "SmallCoin";
}

void ASmallCoinItem::ActivateItem(AActor* activator)
{
	//기본 코인 동작은 부모에서 구현해뒀음
	Super::ActivateItem(activator);
	//DestroyItem();
}
