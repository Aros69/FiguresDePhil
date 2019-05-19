// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
// Based on : https://www.youtube.com/watch?v=EPRTgWt-km0
ABallActor::ABallActor(const class FObjectInitializer& PCIP) : Super(PCIP) {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    struct FConstructorStatics {
        ConstructorHelpers::FObjectFinderOptional<UPaperSprite> ballAsset;
        FConstructorStatics() 
            : ballAsset(TEXT("PaperSprite'/Game/Resources/Sprites/AttrapFig/ball_Sprite.ball_Sprite'")) {}
    };
    static FConstructorStatics constructor;
    this->GetRenderComponent()->SetSprite(constructor.ballAsset.Get());

    //text = NewObject<UTextRenderComponent>();
    text = CreateDefaultSubobject<UTextRenderComponent>("Hello!!!");

    if(text==nullptr){
        /*if(GEngine)
    	    { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("New needed for text !!!!")); }*/
    } else {
        text->AttachToComponent(this->GetRootComponent(),  FAttachmentTransformRules::KeepRelativeTransform);
        text->SetVisibility(true);
        text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
        text->SetTextRenderColor(FColor::Red);
        text->SetXScale(10);
        text->SetYScale(10);
        text->SetWorldSize(10.f);
        // TODO fusionner les deux set K2_SetRelativeLocationAndRotation()
        FVector l(0,150,0);
        text->SetRelativeLocation(l);
        FRotator r(0,90,0);
        text->SetRelativeRotation(r);
        text->K2_SetText(FText::FromString("Hello!!!"));
        /*if(GEngine)
    	    { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("YES")); }*/
    }
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    FVector pos = GetActorLocation();
    pos.X += 5;
    SetActorLocation(pos);

    FString str = "(";
    str.Append(FString::SanitizeFloat(pos.X)).Append(", ").
            Append(FString::SanitizeFloat(pos.Y)).Append(", ").
            Append(FString::SanitizeFloat(pos.Z)).Append(")"); 
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, str);

    /*if(text!=nullptr) {
        FVector pos = text->GetComponentLocation();
        FString str = "(";
        str.Append(FString::SanitizeFloat(pos.X)).Append(", ").
            Append(FString::SanitizeFloat(pos.Y)).Append(", ").
            Append(FString::SanitizeFloat(pos.Z)).Append(")");
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, text->Text.ToString());
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, str); 
    }*/
}
    
