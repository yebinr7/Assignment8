// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CoinItem.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER3_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ACoinItem();

protected:
	// 부모 아이템에서 override한 Activate함수
	virtual void ActivateItem(AActor* activator)override;



	//코인 획득 시 얻을 점수(자식에서 상속 받아 바꿔주기)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue;

};
