// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "Chapter3/Chapter3Character.h"

AHealingItem::AHealingItem()
{
	HealAmount = 20;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	//플레이어 캐릭터의 체력 20만큼 회복시키는 로직
	//베이스아이템에서 충돌처리 하면서 다형성으로 여기로 불려짐
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AChapter3Character* playerCharacter =
			Cast<AChapter3Character>(Activator)) //발동한 AActor다운캐스팅으로 player인지 확인후
		{
			//플레이어가 맞다면
			playerCharacter->AddHealth(HealAmount); // 피회복 포션 값으로  플레이어 매서드를통해 회복
		}
		




		//회복 디버그 메시지
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Player gained %d HP!"), HealAmount));
	
		//아이템도 이때 사라지게
		DestroyItem();

	}


	
}
