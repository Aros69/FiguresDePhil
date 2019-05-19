// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"

#include "BallCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TEMPUNREALPROJECT_API ABallCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
public:

	ABallCharacter(const class FObjectInitializer& PCIP);

	UPROPERTY(VisibleInstanceOnly)
	UTextRenderComponent* text;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setText(const FString& newText);

	int figType;

	virtual void NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp,
				bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
				const FHitResult & Hit) override;

	int isDone;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	FString formatTextInBall(const FString& str);
	
	
};
