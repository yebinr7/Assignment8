// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

//구조체는 헤더파일 필요없나?..
#include "ItemSpawnRow.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;//true;

	// 박스 컴포넌트 생성 & 이 액터의 루트로 설정
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	//루트 하위에 붙히는 박스 컴포넌트
	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);


}




FVector ASpawnVolume::GetRandomPointInVolume() const
{
	// 1) 박스 컴포넌트의 스케일된  Extent ,즉 X/Y/Z 방향으로 반지름(절반 길이)를 구한다.
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();

	// 2) 박스 컴포넌트의 중심 좌표 
	FVector BoxCenter = SpawningBox->GetComponentLocation();

	// 3) 각 축별로 무작위 값 생성
	return BoxCenter + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> itemClass)
{
	if (!itemClass) return nullptr; //방어코드?

	// spawnActor가 성공하면 스폰된 액터의 포인터가 반환됨
	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(
		itemClass,//들어온 para 아이템클래스
		GetRandomPointInVolume(),//내가 만든 랜덤함수
		FRotator::ZeroRotator
	);
	
	return spawnedActor;
}

AActor* ASpawnVolume::SpawnRandomItem()
{
	if (FItemSpawnRow* selectedRow = GetRandomItem())
	{
		if (UClass* actualClass = selectedRow->ItemClass.Get())
		{
			// 여기서 SpawnItem()을 호출하고, 스폰된 AActor 포인터를 리턴
			return SpawnItem(actualClass);
		}
	}
	return nullptr;
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	// 방어코드
	if (!ItemDataTable) return nullptr;

	// 1. 모든 행을 가져오기(행백터)
	TArray<FItemSpawnRow*> allRows;
	static const FString contextString(TEXT("ItemSpawnContext"));
	ItemDataTable->GetAllRows(contextString, allRows);

	if (allRows.IsEmpty()) return nullptr;

	// 2. 전체 확률의 합 구하기
	float totalChance = 0.0f; //초기화
	for (const FItemSpawnRow* row : allRows)
	{
		if (row) // row가 유효?
		{
			totalChance += row->SpawnChance; //스폰확률을 토탈값에 더하기
		}
	}

	// 3. 0 ~ 토탈확률 사이 랜덤 값
	const float randvalue = FMath::FRandRange(0.0f, totalChance);
	float accumulateChance = 0.0f;

	// 4. 누적 활률로 아이템 선택
	for (FItemSpawnRow* row : allRows)
	{
		accumulateChance += row->SpawnChance;

		if (randvalue <= accumulateChance)
			return row;

	}


	return nullptr;
}





// Called when the game starts or when spawned
//void ASpawnVolume::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void ASpawnVolume::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

