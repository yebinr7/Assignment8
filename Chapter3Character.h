// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Chapter3Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AChapter3Character : public ACharacter
{
	GENERATED_BODY()

/** ================= 1. UPROPERTY (리플렉션 시스템 변수) ================= **/
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;


public:
	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	
	// 현재 체력
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	




/** ================= 2. UFUNCTION (리플렉션 시스템 함수) ================= **/
protected:
	// 사망 처리 함수 (체력이 0 이하가 되었을 때 호출)
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void OnDeath();


/** ================= 3. 생성자 및 필수 오버라이드 함수 ================= **/
public:
	AChapter3Character();

protected:

	// 데미지 처리 함수 - 외부로부터 데미지를 받을 때 호출됨
	// 또는 AActor의 TakeDamage()를 오버라이드
	virtual float TakeDamage(float DamageAmount, 
					struct FDamageEvent const& DamageEvent, 
					AController* EventInstigator, 
					AActor* DamageCauser) override;



	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/** ================= 4. 일반 메서드 (리플렉션이 필요 없는 함수) ================= **/
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// 현재 체력을 가져오는 함수
	UFUNCTION(BlueprintPure, Category = "Health")
	int32 GetHealth() const;

	// 체력을 회복시키는 함수
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);



/** ================= 5. 일반 멤버 변수 (리플렉션이 필요 없는 변수) ================= **/


	






};

