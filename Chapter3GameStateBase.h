// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Chapter3GameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER3_API AChapter3GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

/** ================= 1. UPROPERTY (리플렉션 시스템 변수) ================= **/
public:    
// 전역 점수를 저장하는 변수;;;이부분 좀 이상함
   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
    int32 Score;
	
	// 현재 레벨에서 스폰된 코인 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	
	// 플레이어가 수집한 코인 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;
	
	// 각 레벨이 유지되는 시간 (초 단위)
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float LevelDuration;
	
	// 현재 진행 중인 레벨 인덱스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	
	// 전체 레벨의 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;
	
	// 실제 레벨 맵 이름 배열. 여기 있는 인덱스를 차례대로 연동
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;


	//============================================================================
	//
	//
	//
	//				         웨이브 		
	//
	//
	// 
	//============================================================================


	// 각 레벨이 유지되는 시간 (초 단위)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	float WaveDuration;

	// 현재 진행 중인 웨이브 인덱스 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
	int32 CurrentWaveIndex;

	//UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category= "WaveScore")
	//int32 WaveScore; // 점수 조건에 사용 

	// 전체 레벨의 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxWaves;
  
/** ================= 2. UFUNCTION (리플렉션 시스템 함수) ================= **/
public:    
// 현재 점수를 읽는 함수
    UFUNCTION(BlueprintPure, Category = "Score")
    int32 GetScore() const;

    // 점수를 추가해주는 함수
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Amount);

	// 게임이 완전히 끝났을 때 (모든 레벨 종료) 실행되는 함수
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();


/** ================= 3. 생성자 및 필수 오버라이드 함수 ================= **/
public:
    AChapter3GameStateBase();
    virtual void BeginPlay() override;

/** ================= 4. 일반 메서드 (리플렉션이 필요 없는 함수) ================= **/
	
	// 레벨을 시작할 때, 아이템 스폰 및 타이머 설정
	void StartLevel();
	
	// 레벨 제한 시간이 만료되었을 때 호출
	void OnLevelTimeUp();
	
	// 코인을 주웠을 때 호출
	void OnCoinCollected();
	
	// 레벨을 강제 종료하고 다음 레벨로 이동
	void EndLevel();

	// 레벨당 웨이브
	void StartWave();

	// 웨이브별 Duration 감소함수 웨이브별 10초씩 감소
	float CalculateWaveDurationLinear(int CurrentWaveIndex, float InitialDuration = 60.0f, float MinDuration = 10.0f, float DecreasePerWave = 10.0f);
	
	// 웨이브별 타임 만료
	void OnWaveTimeUp();

	//void OnCoinCollectedInWave();
	
	// 웨이브 종료시, 다음 웨이브 or 다음 레벨 진행
	void EndWave();


	
	/** ================= 5. 일반 멤버 변수 (리플렉션이 필요 없는 변수) ================= **/
	// 매 레벨이 끝나기 전까지 시간이 흐르도록 관리하는 타이머
	FTimerHandle LevelTimerHandle;
};
