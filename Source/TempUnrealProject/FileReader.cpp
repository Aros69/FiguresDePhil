// Fill out your copyright notice in the Description page of Project Settings.


#include "FileReader.h"


// Sets default values for this component's properties
UFileReader::UFileReader()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	nameFile = "Figures/Comparaison.txt";
}

UFileReader::UFileReader(FString filename)
{
	PrimaryComponentTick.bCanEverTick = false;
	nameFile = filename;
}

FString UFileReader::ReadFile(){
	return ReadFile(nameFile);
}

FString UFileReader::ReadFile(FString filename)
{
	//Read file ini [project]/Content/Data/ 
    //you can change with other location
	FString directory = FPaths::Combine(FPaths::ProjectContentDir(), "Data");
	FString result;
	IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();
	if (file.CreateDirectory(*directory)) {
		FString myFile = directory + "/" + filename;
		FFileHelper::LoadFileToString(result, *myFile);
	}
	//UE_LOG(LogTemp, Warning, result);
	return result;
}

// Called when the game starts
void UFileReader::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFileReader::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

