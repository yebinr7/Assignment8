// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseItem.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//루트 컴포넌트 설정
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	// 충돌 컴포넌트 생성 및 설정
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	// 겹침만 감지하는 프로파일 설정
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	// 루트 컴포넌트로 설정
	Collision->SetupAttachment(Scene);

	//스태틱 메시 컴포넌트 생성 및 설정
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	//메시가 불필요하게 충돌을 막지 않기 위해서 별도로 NOCollision 등으로 설정 가능함


	// Overlap 이벤트 바인딩!!!! 핵심

	/*
	이 방식은 언리얼 엔진에서 제공하는 강력한 이벤트 처리 메커니즘 중 하나로,
	동적 델리게이트를 통해 런타임에 유연하게 이벤트를 처리할 수 있도록 해줘.
	특히 Overlap 이벤트는 게임 내 상호작용 구현에 필수적인 요소라서 자주 사용돼
	*/
	//내가 만든 함수인 OnItemOvelap으로 바인딩시킨다.
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);
}




//// Called when the game starts or when spawned
//void ABaseItem::BeginPlay()
//{
//	Super::BeginPlay();
//
//}
//
//// Called every frame
//void ABaseItem::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}



void ABaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// otherActor가 플레이어인지 확인 태그 활용
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!!")));
		// 아이템 사용 (획득) 로직 호출
		ActivateItem(OtherActor);
	}
	
}

void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

void ABaseItem::ActivateItem(AActor* activator)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Overlap!!")));
}

FName ABaseItem::GetItemType() const
{
	return ItemType;//각각의 객체들의 타입들
}

void ABaseItem::DestroyItem()
{
	Destroy(); //AActor제공 함수
}


