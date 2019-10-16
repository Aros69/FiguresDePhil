// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LearnerProfil.generated.h"

/**
 * 
 */
UCLASS()
class TEMPUNREALPROJECT_API ULearnerProfil : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	int questionMetaphore;
	int reponseMetaphore;

	int questionComparaison;
	int reponseComparaison;

	int questionLitote;
	int reponseLitote;

	int questionOxymore;
	int reponseOxymore;
	
	int questionEuphemisme;
	int reponseEuphemisme;

	int questionSynecdoqye;
	int reponseSynecdoque;



	ULearnerProfil();
	
};
