// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeActor.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"


APipeActor::APipeActor(const class FObjectInitializer& PCIP): Super(PCIP) {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    struct FConstructorStatics {
        ConstructorHelpers::FObjectFinderOptional<UPaperSprite> ballAsset;
        FConstructorStatics() 
            : ballAsset(TEXT("PaperSprite'/Game/Resources/Sprites/AttrapFig/box1_Sprite.box1_Sprite'")) {}
            
    };
    static FConstructorStatics constructor;
    this->GetRenderComponent()->SetSprite(constructor.ballAsset.Get());

    FVector scale = GetActorScale();
    scale.X = 0.7;
	scale.Y = 0.7;
    scale.Z = 0.7;
    SetActorScale3D(scale);
    /*FVector position = GetActorLocation();
    position.X = -100;
    SetActorLocation(position);*/

    //text = NewObject<UTextRenderComponent>();
    text = CreateDefaultSubobject<UTextRenderComponent>("InitTextPipe");

    if(text==nullptr){
        /*if(GEngine)
    	    { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("New needed for text !!!!")); }*/
    } else {
        text->AttachToComponent(this->GetRootComponent(),  FAttachmentTransformRules::KeepRelativeTransform);
        text->SetVisibility(true);
        text->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
        text->SetTextRenderColor(FColor::Black);
        text->SetXScale(4);
        text->SetYScale(4);
        text->SetWorldSize(10.f);
        // TODO fusionner les deux set K2_SetRelativeLocationAndRotation()
        FVector l(0,10,0);
        text->SetRelativeLocation(l);
        FRotator r(0,90,0);
        text->SetRelativeRotation(r);
        text->K2_SetText(FText::FromString("Init Text Pipe"));
        /*if(GEngine)
    	    { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("YES")); }*/
    }
}

void APipeActor::BeginPlay() {}

void APipeActor::Tick(float DeltaTime) {}

void APipeActor::setText(FString str) {
	text->SetXScale(4);
	text->SetYScale(4);
	text->K2_SetText(FText::FromString(str));
}
