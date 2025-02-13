// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"
#include "Engine/World.h"
#include "Chapter3GameStateBase.h"
ACoinItem::ACoinItem()
	:PointValue(0)
{
	ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* activator)
{
	//플레이어 태그 확인
	if (activator && activator->ActorHasTag("Player"))
	{

		if (UWorld* world = GetWorld())
		{
			//게임스테이트 존재한다면?
			if (AChapter3GameStateBase* gameState = world->GetGameState<AChapter3GameStateBase>())
			{
				// 점수 VS 실질적으로 먹은 개수 

				//데이터영역과 유사한 gameState에 스코어 추가 
				gameState->AddScore(PointValue);
				
				//코인 먹었으면 데이터영역과 유사한 gameState에서 실질적으로 
				gameState->OnCoinCollected(); //	CollectedCoinCount++; 이게됨-> max 개 먹으면 다음레벨 ㄱ 

			}
		}


		//점수 획득 디버그 메시지
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,
			FString::Printf(TEXT("Player gained %d points"), PointValue));

		//객체 삭제->virtual이라 자식도 삭제?
		DestroyItem();
	}

}
