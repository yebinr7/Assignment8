// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class CHAPTER3_API ASpawnVolume : public AActor
{
GENERATED_BODY()
/** ================= 1. UPROPERTY (리플렉션 시스템 변수) ================= **/
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;

	// 스폰 영역을 담당할 박스 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	
	// 아이템 데이터 테이블(랜덤 확률 적힌 테이블)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	UDataTable* ItemDataTable;


/** ================= 2. UFUNCTION (리플렉션 시스템 함수) ================= **/
public:
	// 스폰 볼륨 내부에서 무작위 좌표를 얻어오는 함수
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FVector GetRandomPointInVolume() const;

	// 특정 아이템 클래스를 스폰하는 함수
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnItem(TSubclassOf<AActor> itemClass);

	// 랜덤아이템 만드는 함수 -> 데이터 테이블 참고해서 만듬
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem();
	
	// 아이템 랜덤 테이블 가져오기
	FItemSpawnRow* GetRandomItem() const;
	

/** ================= 3. 생성자 및 필수 오버라이드 함수 ================= **/
public:
	// Sets default values for this actor's properties
	ASpawnVolume();


protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:
	// Called every frame
	/*virtual void Tick(float DeltaTime) override;*/
/** ================= 4. 일반 메서드 (리플렉션이 필요 없는 함수) ================= **/

/** ================= 5. 일반 멤버 변수 (리플렉션이 필요 없는 변수) ================= **/




	
	




};
