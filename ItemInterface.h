// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHAPTER3_API IItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//순수 가상함수들 -> 오버라이딩 필수 

	UFUNCTION() //있어야만 런타임에 엔진이 함수 찾을 수 있다..
	//플레이어가 이 아이템의 범위에 들어왔을 때 호출
	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;

	UFUNCTION()
	//플레이어가 이 아이템의 범위 나갔을 때
	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;

	//아이템이 사용되었을 때,
	virtual void ActivateItem(AActor* activator) = 0;

	//이 아이템의 유형 타입을 반환 Coin, Mine 등
	virtual FName GetItemType() const = 0;


};
