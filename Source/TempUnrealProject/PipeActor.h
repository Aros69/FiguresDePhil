// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"

#include "PipeActor.generated.h"

/**
 * 
 */
UCLASS()
class TEMPUNREALPROJECT_API APipeActor : public APaperSpriteActor
{
	GENERATED_BODY()
	

public:

	APipeActor(const class FObjectInitializer& PCIP);

	UPROPERTY(VisibleInstanceOnly)
	UTextRenderComponent* text;

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setText(FString str);

	int figType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
