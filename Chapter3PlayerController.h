// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Chapter3PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class CHAPTER3_API AChapter3PlayerController : public APlayerController
{
	GENERATED_BODY()


/** ================= 1. UPROPERTY (리플렉션 시스템 변수) ================= **/
public:
	// UMG 위젯 클래스를 에디터에서 할당받을 변수 (리플렉션에 의해 자동으로 값이 할당됨 블루프린트 UI 설정해두면)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	
	// HUD 위젯 인스턴스 : 생성자에서 nullptr 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	UUserWidget* HUDWidgetInstance;


	// 메뉴 UI

	// 메인메뉴 클래스를 인스턴스에 할당하기 위한? 리플렉션 시스템에 의해서 자동으로 클래스 인식?됨
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass; // 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Menu")
	UUserWidget* MainMenuWidgetInstance;




/** ================= 2. UFUNCTION (리플렉션 시스템 함수) ================= **/
	
	// 현재 컨트롤러가 가지고 있는 HUD 반환 
	UFUNCTION(BlueprintPure, Category = "HUD")
	UUserWidget* GetHUDWidget() const;

	// HUD 표시
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameHUD();

	// 메인 메뉴 표시, 매개변수는 Restart할건지 확인
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ShowMainMenu(bool bIsRestart);

	// 게임 시작-> 메인메뉴 부터 시작하게
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void StartGame();


/** ================= 3. 생성자 및 필수 오버라이드 함수 ================= **/
public:
	AChapter3PlayerController();
/** ================= 4. 일반 메서드 (리플렉션이 필요 없는 함수) ================= **/
protected:
	virtual void BeginPlay() override;
/** ================= 5. 일반 멤버 변수 (리플렉션이 필요 없는 변수) ================= **/

	
};
