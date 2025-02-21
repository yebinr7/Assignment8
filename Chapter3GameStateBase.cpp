// Fill out your copyright notice in the Description page of Project Settings.


#include "Chapter3GameStateBase.h"
#include "Chapter3GameInstance.h"

#include "Chapter3PlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinItem.h"

#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"





AChapter3GameStateBase::AChapter3GameStateBase()
	:Score(0), //0으로 이니셜라이즈
	SpawnedCoinCount(0),
	CollectedCoinCount(0),
	LevelDuration(30.0f),
	CurrentLevelIndex(0),
	MaxLevels(3),
	WaveDuration(0),
	CurrentWaveIndex(0),
	//WaveScore(0),
	MaxWaves(3)
{
}

void AChapter3GameStateBase::BeginPlay()
{
	Super::BeginPlay();

	// 게임 시작 시 첫 레벨부터 진행하기
	StartLevel();


	// 게임스테이트(전역 공유 데이터 관리하는)
	GetWorldTimerManager().SetTimer( // 월드매니저 객체 불러와서 타이머 설정
		HUDUpdateTimerHandle, // 내가 만든 핸들 타이머에
		this, // 이 게임 스테이트 객체에서 타이머 실행 
		&AChapter3GameStateBase::UpdateHUD, // 내가 만든 함수 발생하게 (함수포인터 방식) 
		0.1f, // 0.1 초마다 발생 -> 매프레임에서 하는 것 대신에... 
		true  // 반복 실행 여부
	);

}

void AChapter3GameStateBase::StartLevel()
{
	// 컨트롤러에서 HUD 켜주기 UpdateHUD() -> 
	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		//다운 캐스팅
		if (AChapter3PlayerController* chapter3PlayerController = Cast<AChapter3PlayerController>(playerController))
		{
			chapter3PlayerController->ShowGameHUD(); // 그냥 HUD 켜주기
		}
	}



	// 볼륨레벨 전환 활용코드 
	if (UGameInstance* gameInstance = GetGameInstance())
	{
		UChapter3GameInstance* chapter3GameInstance = Cast<UChapter3GameInstance>(gameInstance);
		if (chapter3GameInstance)
		{
			CurrentLevelIndex = chapter3GameInstance->CurrentLevelIndex;
		}
	}


	//// HUD 업데이트?;
	//UpdateHUD();


	// 레벨(Map)마다 웨이브 3개씩 존재함
	// 점수 오를 때마다 웨이브 증가 
	// 현재 웨이브 번호, 웨이브 증가할 때 마다 스폰 개수 늘어남 
	// 화면에 Wave 시작이라고 떠야함 

	// 웨이브 시작 메서드 -> 1, 2, 3 웨이브 분리 
	StartWave();




	//// 레벨 시작 시, 코인 개수 초기화
	//SpawnedCoinCount = 0;
	//CollectedCoinCount = 0;

	//// 현재 맵에 배치된 모든 SpawnVolume을 찾아 아이템 40 개 스폰
	//TArray<AActor*> foundVloumes; // 액터포인터벡터 만들어서  여기에 담는것인가?
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(),
	//	ASpawnVolume::StaticClass(),
	//	foundVloumes);

	//const int32 itemToSpawn = 40; //상수 값 constexpr 사용?

	//for (int32 i = 0; i < itemToSpawn; ++i)
	//{
	//	if (foundVloumes.Num() > 0) // AActor 벡터에 존재한다면
	//	{
	//		// 다운 캐스팅으로 받아와서
	//		ASpawnVolume* spawnVolume = Cast<ASpawnVolume>(foundVloumes[0]);
	//		if (spawnVolume)// 받아온 스폰볼륨
	//		{
	//			// 그 박스 스폰 액터 구역에서 랜덤으로 아이템 만들어내기
	//			AActor* spawnedActor = spawnVolume->SpawnRandomItem();

	//			// 만약 스폰된 액터가 코인 타입이라면 SpawnedCoinCount 증가시키기
	//			if (spawnedActor && spawnedActor->IsA(ACoinItem::StaticClass()))
	//				SpawnedCoinCount++;
	//		}
	//	}
	//}


	//// 이 스폰맵은 30초 후에 OnLevelTimeUp 호출 되도록 타이머 설정!
	//GetWorldTimerManager().SetTimer(
	//	LevelTimerHandle,
	//	this,
	//	&AChapter3GameStateBase::OnLevelTimeUp,
	//	LevelDuration,
	//	false
	//);

	//// 로그도 찍기 처음 생성자에서 이 스폰볼륨, 코인 스폰
	//UE_LOG(LogTemp, Warning, TEXT("Level %d Start!, Spawned %d coin"),
	//	CurrentLevelIndex + 1,
	//	SpawnedCoinCount);

}

void AChapter3GameStateBase::OnLevelTimeUp()
{
	// 시간이 다되면 이함수 부름
	EndLevel(); //밑에서 구현
}

void AChapter3GameStateBase::OnCoinCollected()
{
	// 이 함수가 불린다? -> 코인 얻은것 -> 점수 이 스테이트(정적같은느낌)에서 관리 매너지 느낌
	CollectedCoinCount++;

	// 점수 얻을때마다 로그 출력
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"),
		CollectedCoinCount,
		SpawnedCoinCount)

		// 현재 스폰볼륨에서 스폰된 코인을 전부 얻었다면 레벨 즉시 종료
		/*if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
			EndLevel();*/

		// 확장되서 현재 웨이브에서 스폰된 코인 모두 먹었다면 wave 즉시종료
		if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
			EndWave();

}

void AChapter3GameStateBase::EndLevel()
{
	// 타이머를 해제해야함 끝났으니
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	


	//;;; 노트에 없는내용: EndLevel 이 됐으니 게임인스턴스의 레벨 증가 
	if (UGameInstance* gameInstance = GetGameInstance())
	{
		UChapter3GameInstance* chapter3GameInstance = Cast< UChapter3GameInstance>(gameInstance);
		if (chapter3GameInstance)
		{
			// 레벨이 끝날때마다 인스턴스가 관리하는 총 점수에 점수 업데이트 해야함
			// 이렇게 말고 그냥 웨이브 모두 끝나서 다음 레벨로 넘어갈때, 누적합 하지말고 계속 가기
			//AddScore(Score);
			// 다음 레벨 인덱스로(게임 볼륨 이동ㄱㄱ)
			CurrentLevelIndex++;

			chapter3GameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	// 모든 레벨을 다 돌았다면 게임 오버 처리
	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver(); //볼륨 모두 클리어했음
		return;
	}

	// 레벨 맵 이름이 있다면 해당 맵 불러오기
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(),LevelMapNames[CurrentLevelIndex]);
	}
	else// 없으면
	{
		OnGameOver();
	}
}



void AChapter3GameStateBase::OnGameOver()
{
	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		if (AChapter3PlayerController* chapter3PlayerController = Cast<AChapter3PlayerController>(playerController))
		{
			chapter3PlayerController->SetPause(true); // 게임오버시 못움직에 설정
			chapter3PlayerController->ShowMainMenu(true); // 게임 오버니깐 restart 로 true 해줘야함  -> 리스타트 버튼이 생김 
		}
	}

	// 게임 끝! 
	//UpdateHUD(); // 게임 끝나면 HUD 갱신해줘야함 
	UE_LOG(LogTemp, Warning, TEXT("Game Over!!"));
	// 여기서 UI를 띄운다거나, 재시작 기능을 넣을 수도 있음
}


int32 AChapter3GameStateBase::GetScore() const
{
	return Score;
}

void AChapter3GameStateBase::AddScore(int32 Amount)
{
	//;;; 이부분 노트에 없음
	// 누적 점수 추가 (한 레벨에서 얻은 점수 누적하기 위해서) 
	if (UGameInstance* gameInstance = GetGameInstance())
	{

		UChapter3GameInstance* chapter3Instance = Cast<UChapter3GameInstance>(gameInstance);
		if (chapter3Instance)
			chapter3Instance->AddToScore(Amount); //싱글톤에 추가하는거와 유사하게 전역느낌으로 점수 누적관리
	}
	


	Score += Amount;// 이거해줘야 디테일 창에서 보임;;;
}



// 재사용! 
void AChapter3GameStateBase::StartWave()
{

	// 레벨1-> 웨이브 1, 2, 3
	// 레벨2-> 웨이브 1, 2, 3

	//// 1. 현재 웨이브 어떤 정보 가지고 만들어 졌는지
	//UE_LOG(LogTemp, Warning, TEXT("Wave %d Start!, Spawned %d coin"),
	//	CurrentWaveIndex + 1,
	//	SpawnedCoinCount);
	
	// 게임스테이트에서 현재 웨이브 관리
	
	// 각 웨이브 인덱스마다 조건 다르게 설정하기 
	// 현재 들어온게 0, 1, 2 인지 virtual 한 상태

	// 웨이브 인덱스에 따라 시간 조건 설정
		// 웨이브 낮을 수록 시간 길다

	// 웨이브 인덱스에 따라서 점수 조건 설정
	

	// 웨이브 시작 시, 코인 개수 초기화, 현재 누적 코인개수
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	// 현재 맵에 배치된 모든 SpawnVolume을 찾아 아이템 40 개 스폰
	TArray<AActor*> foundVloumes; // 액터포인터벡터 만들어서  여기에 담는것인가?
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),
		ASpawnVolume::StaticClass(),
		foundVloumes);


	// 웨이브 마다 난이도 다르게 아이템이 생성됨! -> 런타임이라 const 불가?

	//const int32 itemToSpawn = 40; //상수 값 constexpr 사용?
	

	int32 itemToSpawn = 0;
	itemToSpawn = (CurrentWaveIndex + 1) * FMath::RandRange(10, 15);


	for (int32 i = 0; i < itemToSpawn; ++i)
	{
		if (foundVloumes.Num() > 0) // AActor 벡터에 존재한다면
		{
			// 다운 캐스팅으로 받아와서
			ASpawnVolume* spawnVolume = Cast<ASpawnVolume>(foundVloumes[0]);
			if (spawnVolume)// 받아온 스폰볼륨
			{
				// 그 박스 스폰 액터 구역에서 랜덤으로 아이템 만들어내기
				AActor* spawnedActor = spawnVolume->SpawnRandomItem();

				// 만약 스폰된 액터가 코인 타입이라면 SpawnedCoinCount 증가시키기
				if (spawnedActor && spawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
				
				////UE_LOG(LogTemp, Warning, TEXT("Spawned % d coin"),SpawnedCoinCount);

			}
		}
	}


	// 시간도 난이도에 따라서 점차 줄어들게!
	WaveDuration = CalculateWaveDurationLinear(CurrentWaveIndex);
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AChapter3GameStateBase::OnWaveTimeUp,
		WaveDuration,
		false
	);

	// 이 스폰맵은 30초 후에 OnLevelTimeUp 호출 되도록 타이머 설정!
	//GetWorldTimerManager().SetTimer(
	//	LevelTimerHandle,
	//	this,
	//	&AChapter3GameStateBase::OnLevelTimeUp,
	//	LevelDuration,
	//	false
	//);

	// 로그도 찍기 처음 생성자에서 이 스폰볼륨, 코인 스폰
	UE_LOG(LogTemp, Warning, TEXT("Level %d,Wave %d Start!!!,Spawned %d coin"),
		CurrentLevelIndex + 1,
		CurrentWaveIndex +1,
		SpawnedCoinCount);

}

float AChapter3GameStateBase::CalculateWaveDurationLinear(int currentWaveIndex, float initialDuration, float minDuration, float decreasePerWave)
{
	// DecreasePerWave는 매 웨이브마다 줄어드는 시간 (예: 5초)
	float duration = initialDuration - currentWaveIndex * decreasePerWave;
	return FMath::Max(duration, minDuration); // 최소 지속 시간 보장
}

void AChapter3GameStateBase::OnWaveTimeUp()
{
	EndWave();
}

void AChapter3GameStateBase::EndWave()
{
	// 타이머를 해제해야함 끝났으니
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	
	// 만약 웨이브가 남아있다면 다음 웨이브 ㄱㄱ

	// 웨이브 끝이면 다음 레벨로 ㄱㄱ



	if (UGameInstance* gameInstance = GetGameInstance())
	{
		UChapter3GameInstance* chapter3GameInstance = Cast< UChapter3GameInstance>(gameInstance);
		if (chapter3GameInstance)
		{
			// 웨이브가 끝날때마다 인스턴스가 관리하는 총 점수에 점수 업데이트 해야함
			// 웨이브 끝날때마다 누적하기 보다 Score += Amount;를 통해서 점수 그냥 디테일창에서 보이게 ㄱㄱ
			//AddScore(Score);
			// 다음 레벨 인덱스로
			CurrentWaveIndex++;

			// 모든 웨이브를 다 돌았다면 -> 다음 레벨로
			if (CurrentWaveIndex >= MaxWaves)
			{
				EndLevel(); // 웨이브 클리어했음
				return;
			}
			
			//핵심!!! 증가한 채로 다시 웨이브 재구성
  			StartWave();
		}
	}

	//// 모든 웨이브를 다 돌았다면 -> 다음 레벨로
	//if (CurrentWaveIndex >= MaxWaves)
	//{
	//	EndLevel(); // 웨이브 클리어했음
	//	return;
	//}

	

}

void AChapter3GameStateBase::UpdateHUD()
{
	// 1. 월드에서 첫번째플레이어의(내가만든) 컨트롤러 포인터로 받아온다. APlayerController
	// 2. APlayerController로 받아왔으니 내가 만든 컨트롤러 chapter3Controller로 다운캐스팅한다.
	// 3. 내 컨트롤러안에 있는 HUD Get으로 얻어와서 UUserWidget 포인터로 가져온다.
	// 4. Time 이라고 적혀있는 widget을 다운캐스팅하여 TextBlock 포인터로 가져온다.
		// 5. 월드에서 관리하고 있는 레벨타이머핸들 가져와서 몇초 남았나 float로 받아온다.
		// 6. TextBlock포인터에 그 받아온 남은 시간 값 설정해준다 -> (UI에서 이제 보이게됨)
	// 7. Score 도 마찬가지로 Score라 적혀있는거 TextBlock 포인터로 가지고온다. 
		// 8. 게임인스턴스 포인터로 받야온다.
		// 9. 내가 만든 게임인스턴스로 다운캐스팅 하고
		// 10. 존재한다면(nullptr 방어코드) UTextBlock 포인터에 스코어 값 설정해준다. 
	// 11. 레벨값도 마찬가지로 Level이라 적혀있는거 TextBlock 포인터로 가져온다.
		// 12. 현재레벨 +1 해서(idx 0부터시작했기에) TextBlock 포인터에 값 설정해준다. 


	if (APlayerController* playerController = GetWorld()->GetFirstPlayerController())
	{
		if (AChapter3PlayerController* chapter3PlayerController = Cast<AChapter3PlayerController>(playerController))
		{
			if (UUserWidget* hUDWidget = chapter3PlayerController->GetHUDWidget())
			{
				// 시간 UI에 표시
				if (UTextBlock* timeText = Cast<UTextBlock>(hUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					// myCheck:
					float remainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					//float remainingTime = WaveDuration;
					timeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), remainingTime))); // 12.3 같은 문자열 FString->FText로 변환해야함
				}

				// 스코어 UI에 표시
				if (UTextBlock* scoreText = Cast<UTextBlock>(hUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					// 스코어는 게임 인스턴스에 존재하는 누적 스코어 보여주고 싶음
					if (UGameInstance* gameInstance = GetGameInstance()) //; 이 전역함수 도대체 어디서나온겨?
					{
						UChapter3GameInstance* chapter3GameInstance = Cast<UChapter3GameInstance>(gameInstance);
						if (chapter3GameInstance)
						{
							scoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), chapter3GameInstance->TotalScore)));
						}
					}
				}

				// 레벨의 인덱스 표시 
				if (UTextBlock* levelIndexText = Cast<UTextBlock>(hUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					// 레벨은 게임스테트에서 관리하고 있으니깐 현재 this가 가지고 있음
					levelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1 )));
				}

			}
		}
	}

	


}
