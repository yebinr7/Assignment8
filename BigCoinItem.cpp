// Fill out your copyright notice in the Description page of Project Settings.


#include "BigCoinItem.h"

ABigCoinItem::ABigCoinItem()
{
	PointValue = 50;
	ItemType = "BigCoin";
}

void ABigCoinItem::ActivateItem(AActor* activator)
{
	//DestroyItem(); // 아이템 소멸(부모의 DestroyItem() 혹은 자체 로직

	//부모인 코인에서 코인 먹는 효과 만들어놨음
	Super::ActivateItem(activator);


	//빅 코인만의 추가 동작(이펙트, 사운드 재생 등)을 여기서 추가할 수 있음

}
