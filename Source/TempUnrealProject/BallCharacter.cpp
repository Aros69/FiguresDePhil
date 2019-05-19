// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCharacter.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PipeActor.h"

// Sets default values
// Based on : https://www.youtube.com/watch?v=EPRTgWt-km0
ABallCharacter::ABallCharacter(const class FObjectInitializer& PCIP) : Super(PCIP) {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    struct FConstructorStatics {
        ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> ballAsset;
        FConstructorStatics() 
            : ballAsset(TEXT("PaperFlipbook'/Game/Resources/Sprites/AttrapFig/ball_Flipbook.ball_Flipbook'")) {}
    };
    static FConstructorStatics constructor;
    this->GetSprite()->SetFlipbook(constructor.ballAsset.Get());

    FVector scale = GetActorScale();
    scale.X /= 4;
    scale.Y /= 4;
    scale.Z /= 4;
    SetActorScale3D(scale);


    text = CreateDefaultSubobject<UTextRenderComponent>("GeneratedBallText");
    if(text==nullptr){} 
    else {
        text->AttachToComponent(this->GetRootComponent(),  FAttachmentTransformRules::KeepRelativeTransform);
        text->SetVisibility(true);
        text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
        text->SetXScale(5);
        text->SetYScale(5);
        text->SetWorldSize(10.f);
        FVector l(0,1,-25);
        text->SetRelativeLocation(l);
        // Put the text in front of the camera
        FRotator r(0,90,0);
        text->SetRelativeRotation(r);
        setText("Init Text Ball");
		isDone = 0;
        /*if(GEngine)
    	    { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("YES")); }*/
    }
}

// Called when the game starts or when spawned
void ABallCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABallCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isDone == -1) {
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "Killing myself");
		Destroy();
	}
    /*FVector pos = GetActorLocation();
    pos.X += 0.5;
    SetActorLocation(pos);*/

    // Show position of the ball
    /*FString str = "(";
    str.Append(FString::SanitizeFloat(pos.X)).Append(", ").
            Append(FString::SanitizeFloat(pos.Y)).Append(", ").
            Append(FString::SanitizeFloat(pos.Z)).Append(")"); 
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, str);*/
}

void ABallCharacter::setText(const FString& newText) {
    if(text!=nullptr){
        FVector l(0,1,-25);
        text->SetRelativeLocation(l);
        text->K2_SetText(FText::FromString(formatTextInBall(newText)));
    }
}

FString ABallCharacter::formatTextInBall(const FString& str){
    FString res(str);
    // number of char puttable on each ligne of the ball
    int tabEspace[6] = {5, 12, 14, 14, 14, 5};
    int nextSpace = 0, tempCount = 0, nbSautLigne = 0, charRemoved = 0;
    while(nextSpace != -1 && nbSautLigne < 5) {
        nextSpace = str.Find(" ", ESearchCase::IgnoreCase, ESearchDir::FromStart, nextSpace+1);
        if(nextSpace-charRemoved > tabEspace[nbSautLigne]) {
            res.RemoveAt(tempCount);
            res.InsertAt(tempCount, '\n');
            charRemoved = tempCount;
            nbSautLigne++;
        } else if(nextSpace-charRemoved == tabEspace[nbSautLigne]) {
            res.RemoveAt(nextSpace);
            res.InsertAt(nextSpace, '\n');
            charRemoved = nextSpace;
            nbSautLigne++;
        } else if(nextSpace==-1 && str.Len()-charRemoved>tabEspace[nbSautLigne]){
            res.RemoveAt(tempCount);
            res.InsertAt(tempCount, '\n');
            charRemoved = tempCount;
            nbSautLigne++;
        }
        tempCount = nextSpace;
    }

    // Move text depending on modification
    FVector pos = text->RelativeLocation;
    pos.Z -= nbSautLigne*25;
    text->SetRelativeLocation(pos);

    return res;
}

void ABallCharacter::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
	const FHitResult & Hit) {
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if ((Other != NULL) && (Other != this) && (OtherComp != NULL))
	{
		if (Other->GetClass()->IsChildOf(APipeActor::StaticClass())) {
			if (GetActorLocation().Z > -20) {
				//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *Other->GetName()));
				if (((APipeActor*)Other)->figType == figType) {
					isDone = 1;
				}
				else {
					isDone = 2;
				}
			}
		}
	}
}