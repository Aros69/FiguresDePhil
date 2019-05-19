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

	UPROPERTY(VisibleInstanceOnly)
	UTextRenderComponent* text;

	// Needs to be populated somehow (e.g. by exposing to blueprints as uproperty and setting it there
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BallClass; 

	const TArray<FString> Comparaison = { "Rond comme un ballon",
									"Il est aussi calme que son frere",
									"La terre est bleue comme une orange",
									"La mer est si bleue qu'il n'y a que le sang qui soit plus rouge",
									"Le poete est semblable au Prince des nuees" };
	const TArray<FString> Metaphore = { "Rouge Tomate",
										"L\'or du soir",
										"Tu es la terre qui prend racine",
										"Le lac, divin miroir",
										"Ma jeunesse ne fut qu'un tenebreux orage"};

	const TArray<FString> Litote = { "Va, je ne te hais point",
									"Il n'est pas bien courageux",
									"Ce n'est pas mauvais",
									"Elle n'a pas fait le voyage pour rien"};
	const TArray<FString> Oxymore = { "Un silence assourdissant",
									"Une sublime horreur",
									"Cette obscure clarte qui tombe des etoiles",
									"Le superflu, chose tres necessaire",
									"Hate - toi lentement",
									"La vie, c'est mortel" };
	const TArray<FString> Euphemisme = { "Elle nous a quittes",
										"J'ai deux mots a lui dire",
										"Une longue maladie",
										"Cette petite grande ame venait de s'envoler",
										"Il est parti pour un monde meilleur" };
	const TArray<FString> Synecdoque = { "Il y a environ deux cents tetes dans ce theatre",
										"Je quitterai bientot ces murs",
										"Il a achete une toile de cet artiste prometteur",
										"La France remporte la Coupe du monde",
										"Je vais boire un verre"};

	const int figStyleLength = 6;
	const TArray<FString> figStyle[6] = {Comparaison, Euphemisme, Litote, Metaphore, Oxymore, Synecdoque};
	const FString figType[6] = { "Comparaison", "Euphemisme", "Litote", "Metaphore", "Oxymore", "Synecdoque" };

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

	void initBalls();
	

private:

	UWorld * world;

	int indexFig1;
	int indexFig2;

	int initBallOK = false;
};
