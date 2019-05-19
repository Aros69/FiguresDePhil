// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Public/HAL/PlatformFilemanager.h"
#include "FileReader.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEMPUNREALPROJECT_API UFileReader : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFileReader();

	UFileReader(FString filename);

	FString ReadFile(FString filename);
	FString ReadFile();

	FString nameFile;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

		
	
};
