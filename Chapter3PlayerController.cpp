// Fill out your copyright notice in the Description page of Project Settings.
#include "Chapter3PlayerController.h"
#include "Chapter3GameStateBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h" // 헤더 추가

#include "Chapter3GameInstance.h"

#include "Kismet/GameplayStatics.h" // 함수 모음집
#include "Components/TextBlock.h" // 텍스트블럭 바인딩 시 필요? 

#define 엔진꺼

AChapter3PlayerController::AChapter3PlayerController()
	:HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{
}

UUserWidget* AChapter3PlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}


// 메뉴UI 표시
void AChapter3PlayerController::ShowMainMenu(bool bIsRestart)
{
	// 어디선가 MainMenu를 켰다면...
	// HUD 가 켜져있으면 닫기 -> 약간 방어코드
	if (HUDWidgetInstance/*내가 만든 HUD*/)
	{
		HUDWidgetInstance->RemoveFromParent(); // 메모리에 있는 객체 삭제해주고
		HUDWidgetInstance = nullptr; // 포인터도 null 가르키게 안전하게 해논다. 
	}

	// 이미 메인메뉴가 떠있다면? 다시 제거하고 새로 띄우기
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

//============================================================================

	// 메뉴 UI 진짜 만들기 시작
	if (MainMenuWidgetClass) // 리플렉션 시스템에 의해 BP를 통해 바인딩(?) 됐다면..
	{
		// 인스턴스에 진짜 메모리 할당하기(리플랙션 받아온 애로)
		//MainMenuWidgetInstance = CreateWidget<UUserWidget>(this/*여기 컨트롤러에 만들꺼임*/, MainMenuWigetClass/*리플랙션으로 내가 BP에서 만든거 자동으로 만들어진 클라스*/);
		
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport(); // 뷰포트에 연결 
			엔진꺼 bShowMouseCursor = true;	// 엔진코드 마우스 커서가 보이게 함( 메인 메뉴 UI이니깐~)
			엔진꺼 SetInputMode(FInputModeUIOnly()); // 인풋모드? UI만 가능하게 설정
		}


		// BP 로 만들어논 버튼 StartButtonText 이름 받아와서 
		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			// restart 상황이면..
			if (bIsRestart/*para로 들어온..*/)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart"))); // Restart FString-> FText로 변화해서 설정하기 
			}
			else // 스타트 
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}
		
		if (bIsRestart) //리스타트 상황이라면.. 애니메이션 켜주기
		{

			// 게임오버 됐으니 메인메뉴에서 애니메이션 틀어주기
			UFunction* playAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim")); // 이름가진 애니메이션 찾아와서 UFunction부모형태로 받아온후..

			if (playAnimFunc) // 애니메이션 존재한다면..
			{
				MainMenuWidgetInstance->ProcessEvent(playAnimFunc, nullptr/*매개변수있는지*/); // 블루프린트 그래프에서 만들어둔 함수 실행시키기(깜빡깜빡)
			}

			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
			{	// Text 형태 위젯으로 다운 캐스팅해서..

				// UGameplayStatics 정적함수에서 이 컨트롤러에 대한 게임인스턴스 가져와서 게임인스턴스에 받아오고
				if (UChapter3GameInstance* chapter3GameInstance = Cast<UChapter3GameInstance>(UGameplayStatics::GetGameInstance(this)))
				{
					// FStirng으로 일단 표현하고 그걸 FText로 변환해서 텍스트위젯(메인메뉴의 게임오버에..) 세팅해준다.
					TotalScoreText->SetText(FText::FromString(
						FString::Printf(TEXT("Total Score: %d"), chapter3GameInstance->TotalScore)
					));
				}
			}
		}


	}

}



// 게임 HUD 표시
void AChapter3PlayerController::ShowGameHUD()
{
	// HUD 켜져 있다면 닫기
	if (HUDWidgetInstance)
	{							엔진꺼
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;  // nullptr로 안전하게 옮기기
	}

	// 이미 Menu가 켜져있다면 제거-> 게임 HUD 표시하기 위해
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}


	if (HUDWidgetClass)
	{
		// BP에서 리플랙션으로 할당한 HUDWidgetClass 에 맞는 HUD객체 만들어서 인스턴스에 할당(메모리)
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass); // 실제 메모리에 만들기 
		if (HUDWidgetInstance) // 방어코드
		{
			HUDWidgetInstance->AddToViewport(); 엔진꺼 // 이 HUD 뷰포트에 켜주기

	엔진꺼	bShowMouseCursor = false; // 메인 메뉴일때, 커서 꺼놨으니 다시켜야함!
	엔진꺼  SetInputMode(FInputModeGameOnly()); // 메인 메뉴일때, 게임모드 UI만 가능하게 설정했어서 다시 Game만 가능하게 바꿔주기

			// 월드에 있는 나의 게임스테이트 받아와서 
			AChapter3GameStateBase* chapter3GameState =
				GetWorld() ? GetWorld()->GetGameState<AChapter3GameStateBase>() : nullptr;
			
			if (chapter3GameState)
			{
				// 다시 HUD 업데이트 해주기!(게임 스테이트의 비긴플레이에서 타이머만들어놔서 0.1초 마다 업데이트 계속 돌아가고 있음)
				chapter3GameState->UpdateHUD();
			}
		}
	}
	
}


// 게임 시작- MenuLevel -> BasicLevel로 감..
void AChapter3PlayerController::StartGame()
{
	if (UChapter3GameInstance* chapter3GameInstance = Cast<UChapter3GameInstance>
		(UGameplayStatics::GetGameInstance(this))) // 현재 컨트롤러에 연결되어 있는 게임인스턴스 얻어와서 내가 만든클래스로 캐스팅
	{
		chapter3GameInstance->CurrentLevelIndex = 0; 
		
		//웨이브도 초기화..해줘야하나???..
		
		chapter3GameInstance->TotalScore = 0;
	}
	엔진꺼
		UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel")); // BasicLevel이름가진 애 찾아서 레벨맵 변경
		
	
		SetPause(false); // 게임오버시 멈추게 했으니 다시 움직이게 설정.. 
}


void AChapter3PlayerController::BeginPlay()
{
	Super::BeginPlay();


	// 게임 실행 시 메뉴 레벨에서 메뉴 UI가 먼저 표시되도록!(HUD보다)
	FString currentMapName = GetWorld()->GetMapName(); // 프로젝트 세팅에서 메인메뉴 레벨을 먼저 시작하도록 세팅해놈 따라서 GetWorld 에서 맵 가져오면 이름 MainMenu맵임
	if (currentMapName.Contains("MenuLevel")) // 맵 이름이 MenuLevel 이라면...
	{
		ShowMainMenu(false); // 처음 비긴하는거니깐 리스타트는 꺼준다.
	}





	// ShowMainMenu 에서 만들고 있기 때문에!! 
	//// HUD 위젯 생성 및 표시
	//if (HUDWidgetClass) // 자동으로 리플랙션 시스템에 의해 HUDWidgetClass 에 할당된다! 블루프린트에서 UI 위젯을 지정하면 자동으로 값이 할당됨.
	//{
	//	HUDWidgetInstance = CreateWidget<UUserWidget>(this/*현재컨트롤러에..*/, HUDWidgetClass/*리플랙션으로 자동으로 정해진..클래스*/); // UI위젯을 동적으로 생성, 컨트롤러에 HUD를 만든다.
	//	if (HUDWidgetInstance)// 잘 만들어 졌다면..
	//	{
	//		HUDWidgetInstance->AddToViewport(); // 게임 화면에 실질적으로 보여지게 하는 함수! 
	//	}
	//}

	// 게임스테이트 얻어오는데 월드에서 방어코드로 존재하면 얻어오기 존재 X -> nullptr 
	AChapter3GameStateBase* chapter3GameState =
		GetWorld() ? GetWorld()->GetGameState<AChapter3GameStateBase>() : nullptr;

	if (chapter3GameState)// 존재한다면
	{
		chapter3GameState->UpdateHUD(); // 플레이어의 컨트롤러 비긴플레이시 HUD 업데이트해주기
	}

}
