// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/InputComponent.h"
#include "BallCharacter.h"
#include "CppClawCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TEMPUNREALPROJECT_API ACppClawCharacter : public APaperCharacter
{
	GENERATED_BODY()

public: 

	virtual void Tick(float DeltaTime) override;

    float movementInput;
	bool isInAction;

	// Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp,
		bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit) override;


protected:
    // Called when the game starts or when spawned
    ACppClawCharacter();

	void MoveRight();

	void MoveLeft();

	void Stop();

	void Action();

	ABallCharacter* ballCatch;
	FVector lastBallLocation;

};
