// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemSpawnRow.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase 
{
	/*FTableRowBase :언리얼 엔진에서
	“이 구조체는 데이터 테이블로 쓸 수 있다”
	라고 인식하게 해주는 베이스 구조체입니다.*/
	GENERATED_BODY()

	

/** ================= 1. UPROPERTY (리플렉션 시스템 변수) ================= **/
public:
	//아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	// 어떤 아이템 클래스를 스폰할 것인지?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;

	// 이 아이템의 스폰 확률은 어느정도인지?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;


/** ================= 2. UFUNCTION (리플렉션 시스템 함수) ================= **/

/** ================= 3. 생성자 및 필수 오버라이드 함수 ================= **/

/** ================= 4. 일반 메서드 (리플렉션이 필요 없는 함수) ================= **/
public:
	

/** ================= 5. 일반 멤버 변수 (리플렉션이 필요 없는 변수) ================= **/







};
