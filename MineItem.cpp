// Fill out your copyright notice in the Description page of Project Settings.


#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
AMineItem::AMineItem()
	/*:ExplosionDelay(5.0f),
	ExplosionRadius(300.0f),
	ExplosionDamage(30.0f)*/
{
	ExplosionDelay = (5.0f);
	ExplosionRadius = (300.0f);
	ExplosionDamage = 30;
	ItemType = "Mine";
	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(Scene);

}

void AMineItem::ActivateItem(AActor* Activator)
{
	// 지뢰를 "사용"한다고 가정했을 때의 로직
	// 여기서는 간단히 소멸시키지만,
	// 실제로는 지연 시간 후 폭발 로직을 구현하거나,
	// 폭발 이펙트, 데미지 계산 등을 추가할 수 있음


	//Activate 됐다면 5초후 폭발 실행
	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,//현재 지뢰 넣어주기
		&AMineItem::Explode,//함수객체? 비슷한건가(실제로 폭발하면 어떤 로직될지 안에서구현)
		ExplosionDelay //딜레이 몇초뒤에(생성자에서 설정ㄱ)
	);



}

void AMineItem::Explode()
{
	//현재 폭발로 인한 부딫힌 액터들 싹다 포인터에 받아옴
	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	//반복문 돌면서 Player 체크한 후 뎀지 주기
	for (AActor* Actor : OverlappingActors)
	{
		if(Actor&& Actor->ActorHasTag("Player"))//방어 && 플레이어인지 확인
		{

			// 실제 대미지 발생시켜서 이 마인의 폭발 범위 충돌체에 맞은 애들은 ApplyDamage통해 뎀지 입음

			UGameplayStatics::ApplyDamage(
				Actor,                      // 데미지를 받을 액터 ex)플레이어
				ExplosionDamage,            // 데미지 양
				nullptr,                    // 데미지를 유발한 주체 (지뢰를 설치한 캐릭터가 없으므로 nullptr) 매설자..
				this,                       // 데미지를 유발한 오브젝트(지뢰)
				UDamageType::StaticClass()  // 기본 데미지 유형
			);



			//화면에 일단 출력
			GEngine->AddOnScreenDebugMessage(
				-1, 2.0f, 
				FColor::Red, 
				FString::Printf(TEXT("Player damaged %d by MineItem"), ExplosionDamage)
			);
		}
	}


	//지뢰 제거(부모Item함수 이용)
	DestroyItem();
}
