// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"


class USphereComponent;
//class USphereComponent;

UCLASS()
class CHAPTER3_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;





	//interface의 순수가상함수 오버라이딩 
		
	//플레이어가 이 아이템의 범위에 들어왔을 때 호출
	//인자 엄청 복잡하게 받은 이유? 
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;

	//플레이어가 이 아이템의 범위 나갔을 때 
	//인자 엄청 복잡하게 받은 이유? 
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;

	//아이템이 사용되었을 때,
	virtual void ActivateItem(AActor* activator) override;

	//이 아이템의 유형 타입을 반환 Coin, Mine 등
	virtual FName GetItemType() const override;

	//아이템 제거하는 공통함수(추가 이펙트 로직 가능)
	virtual void DestroyItem();


protected:
	//루트 컴퍼넌트(씬)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;

	//충돌 컴퍼넌트(플레이어가 충돌체 오버랩됐을때..)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* Collision;
	
	//아이템 시각용 Mesh 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;



	//아이템 유형 편집 가능하게 지정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;


};
