// Fill out your copyright notice in the Description page of Project Settings.


#include "CppClawCharacter.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "PipeActor.h"

void DebugVector2(FVector t) {
	FString str = "(";
	str.Append(FString::SanitizeFloat(t.X)).Append(", ").
		Append(FString::SanitizeFloat(t.Y)).Append(", ").
		Append(FString::SanitizeFloat(t.Z)).Append(")");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, str);
}

ACppClawCharacter::ACppClawCharacter(){
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Set this pawn to be controlled by the lowest-numbered player
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    movementInput = 0;
}

void ACppClawCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent){
    Super::SetupPlayerInputComponent(InputComponent);

    // Respond when our "Grow" key is pressed or released.
    InputComponent->BindAction("RightP1", IE_Pressed, this, &ACppClawCharacter::MoveRight);
    InputComponent->BindAction("RightP1", IE_Released, this, &ACppClawCharacter::Stop);

    InputComponent->BindAction("LeftP1", IE_Pressed, this, &ACppClawCharacter::MoveLeft);
    InputComponent->BindAction("LeftP1", IE_Released, this, &ACppClawCharacter::Stop);

    InputComponent->BindAction("ActionP1", IE_Pressed, this, &ACppClawCharacter::Action);
}

void ACppClawCharacter::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
    if(!isInAction){
		if (NewLocation.X < -260) {
			NewLocation.X = -260;
		}
		else if (NewLocation.X > 260) {
			NewLocation.X = 260;
		}
		NewLocation.X += movementInput;
	} else {
		NewLocation.Z += movementInput;
		if (NewLocation.Z >= 120 && movementInput>0) {
			isInAction = !isInAction;
			movementInput = 0;
			if (ballCatch != nullptr) {
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, ballCatch->GetName());
			}
		}
		if (NewLocation.Z <= -120) {
			movementInput = 2;
		}
	}
	SetActorLocation(NewLocation);
}

void ACppClawCharacter::MoveRight(){
	if (!isInAction) {
		movementInput = 5;
	}
}

void ACppClawCharacter::MoveLeft(){
	if (!isInAction) {
		movementInput = -5;
	}
}

void ACppClawCharacter::Stop(){
	if (!isInAction) {
		movementInput = 0;
	}
}

void ACppClawCharacter::Action(){
	if (!isInAction) {
		if (ballCatch == nullptr) {
			movementInput = -2;
			isInAction = !isInAction;
		}
		else {
			ballCatch == nullptr;
		}
	}
}

void ACppClawCharacter::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp,
						bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, 
						const FHitResult & Hit) {
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	
	if ((Other != NULL) && (Other != this) && (OtherComp != NULL))
	{
		if (Other->GetClass()->IsChildOf(APipeActor::StaticClass())) {movementInput = 2;}
		else if (Other->GetClass()->IsChildOf(ACppClawCharacter::StaticClass())) {}
		else if (Other->GetClass()->IsChildOf(ABallCharacter::StaticClass())) {
			if (ballCatch == nullptr) {
				ballCatch = (ABallCharacter*)Other;
			}
			movementInput = 1;
		}
		else {movementInput = 1;}
	}
}