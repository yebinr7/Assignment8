// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Chapter3GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER3_API UChapter3GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
/** ================= 1. UPROPERTY (리플렉션 시스템 변수) ================= **/
public:

	// 게임 전체 누적 점수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;

	// 현재 레벨 인덱스 (GameState에서도 관리할 수 있지만, 맵 전환 후에도 살리고 싶다면 GameInstance에 복제할 수 있음)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;



/** ================= 2. UFUNCTION (리플렉션 시스템 함수) ================= **/
public:

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
/** ================= 3. 생성자 및 필수 오버라이드 함수 ================= **/
public:
	UChapter3GameInstance();
/** ================= 4. 일반 메서드 (리플렉션이 필요 없는 함수) ================= **/

/** ================= 5. 일반 멤버 변수 (리플렉션이 필요 없는 변수) ================= **/


};
