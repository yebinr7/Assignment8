// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER3_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	


protected:
	


/** ================= 1. UPROPERTY (리플렉션 시스템 변수) ================= **/
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component");
	USphereComponent* ExplosionCollision; //폭발과 동시에 어느 범위 만큼 충돌 감지를해서 데미지를 줄건지!! 충돌컴포넌트


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float ExplosionDelay;	//폭발까지 걸리는 시간 5초



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float ExplosionRadius; 	//폭발 범위

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	int32 ExplosionDamage; //폭말 데미지

	


/** ================= 2. UFUNCTION (리플렉션 시스템 함수) ================= **/
	



/** ================= 3. 생성자 및 필수 오버라이드 함수 ================= **/
public:
	AMineItem();
protected:
	//부모 아이템 오버라이딩함수 
	virtual void ActivateItem(AActor* Activator) override;
	
/** ================= 4. 일반 메서드 (리플렉션이 필요 없는 함수) ================= **/
	//지뢰 폭발
	void Explode();

/** ================= 5. 일반 멤버 변수 (리플렉션이 필요 없는 변수) ================= **/
	//지뢰 발동 여부 핸들(커널 번호표?)
	FTimerHandle ExplosionTimerHandle;

	
};
