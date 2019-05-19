// Fill out your copyright notice in the Description page of Project Settings.


#include "AttrapFigLevel.h"

#include "Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "EngineUtils.h"

void DebugVector(FVector t){
	FString str = "(";
    str.Append(FString::SanitizeFloat(t.X)).Append(", ").
            Append(FString::SanitizeFloat(t.Y)).Append(", ").
            Append(FString::SanitizeFloat(t.Z)).Append(")"); 
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, str);
}

void DebugString(FString t) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, t);
}

// Sets default values
AAttrapFigLevel::AAttrapFigLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	text = CreateDefaultSubobject<UTextRenderComponent>("GeneratedGameText");
	if (text == nullptr) {}
	else {
		text->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		text->SetVisibility(true);
		text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
		text->SetXScale(5);
		text->SetYScale(5);
		text->SetWorldSize(10.f);
		/*FVector l(0, 1, -25);
		text->SetRelativeLocation(l);*/
		FHitResult SweepHitResult;
		text->K2_SetWorldLocation(FVector(0, 100, 0), false, SweepHitResult, true);

		// Put the text in front of the camera
		/*FRotator r(0, 90, 0);
		text->SetRelativeRotation(r);*/
		text->K2_SetText(FText::FromString("Base Text Game"));
	}
}
	

// Called when the game starts or when spawned
void AAttrapFigLevel::BeginPlay()
{
	Super::BeginPlay();
	// Récuếration du monde pour créer à l'execution des objets dans le monde
	
	
	if(!world){
		world = GetWorld();
	}
	TArray<AActor *> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BallClass, actors);
	for (int i = 0; i < actors.Num(); ++i) {
		ballArray.Add((ABallCharacter*)actors[i]);
	}

	if (ballArray.Num() != 0) {
		initBalls();
	}

	for (TActorIterator<APipeActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		APipeActor *pipe = *ActorItr;
		if (pipe->GetName()=="PipeActor2") {
			pipe2 = pipe;
			pipe2->figType = 2;
		} else {
			pipe1 = pipe;
			pipe1->figType = 1;
		}
	}
	if (pipe1 != nullptr && pipe2 != nullptr) {
		pipe1->setText(figType[indexFig1]);
		pipe2->setText(figType[indexFig2]);
	}
}

// Called every frame
void AAttrapFigLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!initBallOK && ballArray.Num() != 0) {
		initBalls();
	}
	text->SetXScale(text->XScale+1);
	text->SetYScale(text->YScale+1);
	checkBalls();
	if (ballsRemain == 0) {
		// We are in the endgame now
	}
}

void AAttrapFigLevel::checkBalls() {
	for (int i = 0; i < ballArray.Num(); i++) {
		if (ballArray[i] != nullptr) {
			if (ballArray[i]->isDone == 1) {
				// Print bien joué !
				//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Nice AttrapFig");
				ballArray[i]->isDone = -1;
				ballArray[i] = nullptr;
				ballsRemain--;
			}
			else if (ballArray[i]->isDone == 2) {
				// Print pas de chance
				//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Bad AttrapFig");
				ballArray[i]->isDone = -1;
				ballArray[i] = nullptr;
				ballsRemain--;
			}
		}
	}
}

AActor* AAttrapFigLevel::spawnActor(TSubclassOf<class AActor> objectToSpawn, 
								FActorSpawnParameters spawnParam, 
								FRotator rotation, 
								FVector position) {
	if(world){
		return world->SpawnActor<AActor>(objectToSpawn, position, rotation, spawnParam);
	} else {
		return nullptr;
	}
}

FString AAttrapFigLevel::ReadFile(FString filename) {
	//Project Contenet Dir = "[project]/Content/"
	FString directory = FPaths::ProjectContentDir();
	FString result;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();
	if (file.CreateDirectory(*directory)) {
		FString myFile = directory + "/Data/" + filename;
		//DebugString(myFile);
		FFileHelper::LoadFileToString(result, *myFile);
	}
	return result;
}

int AAttrapFigLevel::numberOfLine(FString file) {
	int res = 0, lastLineIndex = 0;
	do {
		lastLineIndex = file.Find("\n", ESearchCase::IgnoreCase, ESearchDir::FromStart, lastLineIndex+1);
		res++;
	} while(lastLineIndex != -1 && lastLineIndex+1 != file.Len());
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(res));
	return res;
}

void AAttrapFigLevel::initBalls() {
	TArray<AActor *> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BallClass, actors);
	for (int i = 0; i < actors.Num(); ++i) {
		ballArray.Add((ABallCharacter*)actors[i]);
	}

	if (ballArray.Num() != 0) {
		// Tirage aléatoire du premier type de figure, récupéartion du fichier et des figures expemples	
		indexFig1 = FMath::RandHelper(figStyleLength);
		//FString figureFile = ReadFile("Figures/" + figStyle[indexFig1] + ".txt");
		int nbFig = figStyle[indexFig1].Num();
		TArray<FString> figures1 = figStyle[indexFig1];
		/*for (int i = 0; i < nbFig - 1; ++i) {
			figures1.Add(FString());
			figureFile.Split("\n", &figures1.Top(), &figureFile, ESearchCase::IgnoreCase, ESearchDir::FromStart);
		}
		figures1.Add(figureFile);*/

		// Récupération aléatoire des 3 premières figures de styles
		TArray<int> tempArray;
		for (int i = 0; i < nbFig; ++i) {
			tempArray.Add(i);
		}

		int fig1 = FMath::RandHelper(nbFig), fig2, fig3;
		tempArray.Remove(fig1);
		fig2 = tempArray[FMath::RandHelper(nbFig - 1)];
		tempArray.Remove(fig2);
		fig3 = tempArray[FMath::RandHelper(nbFig - 2)];

		ballArray[0]->setText(figures1[fig1]);
		ballArray[0]->figType = 1;
		ballArray[1]->setText(figures1[fig2]);
		ballArray[1]->figType = 1;
		ballArray[2]->setText(figures1[fig3]);
		ballArray[2]->figType = 1;

		// Tirage aléatoire du second type de figure
		do {
			indexFig2 = FMath::RandHelper(figStyleLength);
		} while (indexFig2 == indexFig1);
		//figureFile = ReadFile("Figures/" + figStyle[indexFig2] + ".txt");
		nbFig = figStyle[indexFig2].Num();
		TArray<FString> figures2 = figStyle[indexFig2];
		/*for (int i = 0; i < nbFig - 1; ++i) {
			figures2.Add(FString());
			figureFile.Split("\n", &figures2.Top(), &figureFile, ESearchCase::IgnoreCase, ESearchDir::FromStart);
		}
		figures2.Add(figureFile);*/

		// Récupération aléatoire des 3 premières figures de styles
		tempArray.Empty();
		for (int i = 0; i < nbFig; ++i) {
			tempArray.Add(i);
		}
		fig1 = FMath::RandHelper(nbFig);
		tempArray.Remove(fig1);
		fig2 = tempArray[FMath::RandHelper(nbFig - 1)];
		tempArray.Remove(fig2);
		fig3 = tempArray[FMath::RandHelper(nbFig - 2)];

		ballArray[3]->setText(figures2[fig1]);
		ballArray[3]->figType = 2;
		ballArray[4]->setText(figures2[fig2]);
		ballArray[4]->figType = 2;
		ballArray[5]->setText(figures2[fig3]);
		ballArray[5]->figType = 2;

		initBallOK = true;
	}
}