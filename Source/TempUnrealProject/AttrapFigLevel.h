// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "BallCharacter.h"
#include "PipeActor.h"


#include "AttrapFigLevel.generated.h"

UCLASS()
class TEMPUNREALPROJECT_API AAttrapFigLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttrapFigLevel();

	FString ReadFile(FString filename); 

	// Needs to be populated somehow (e.g. by exposing to blueprints as uproperty and setting it there
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BallClass; 

	const int figStyleLength = 6;
	const FString figStyle[6] = {"Comparaison", "Euphemisme", "Litote", "Metaphore", "Oxymore", "Synecdoque"};
	
	TArray<ABallCharacter *> ballArray;
	APipeActor * pipe1;
	APipeActor * pipe2;
	int ballsRemain = 6;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* spawnActor(TSubclassOf<class AActor> objectToSpawn, 
			FActorSpawnParameters spawnParam, 
			FRotator rotation, FVector position);

	int numberOfLine(FString file);

	void checkBalls();
	

private:

	UWorld * world;

	int indexFig1;
	int indexFig2;
};
