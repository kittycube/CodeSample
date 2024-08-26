// Fill out your copyright notice in the Description page of Project Settings.


#include "Cat.h"
#include "PaperFlipbookComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/InterpToMovementComponent.h"



ACat::ACat()
{
	PrimaryActorTick.bCanEverTick = true;
	GetRenderComponent()->SetRelativeScale3D(FVector(1.5f,1.0f,1.5f));

	// default visual indication set up
	MovementIndicator = CreateDefaultSubobject<UArrowComponent>(TEXT("MovementIndicator"));
	MovementIndicator->SetupAttachment(RootComponent);
	MovementIndicator->SetArrowLength(1000.0f);
	MovementIndicator->SetHiddenInGame(true);
	MovementIndicator->SetVisibility(true);

	// movement component set up
	MovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("MoveComponent"));
	MovementComponent->bSweep = true;
	MovementComponent->BehaviourType = EInterpToBehaviourType::PingPong;
	MovementComponent->ControlPoints.Empty();
	MovementComponent->SetAutoActivate(true);
	MoveSpeed = 1000.0f;
	
	MovementComponent->Duration = MovementIndicator->ArrowLength/MoveSpeed;
	MovementComponent->bPauseOnImpact = true;

	// interpolation set up
	FInterpControlPoint StartPoint;
	StartPoint.PositionControlPoint = FVector::Zero();
	StartPoint.bPositionIsRelative = true;
	MovementComponent->ControlPoints.Add(StartPoint);
	FInterpControlPoint EndPoint;
	FVector EndVector = FVector::Zero();
	EndVector.X = MovementIndicator->ArrowLength;
	EndPoint.PositionControlPoint = EndVector;
	EndPoint.bPositionIsRelative = true;
	MovementComponent->ControlPoints.Add(EndPoint);
}

void ACat::BeginPlay()
{
	Super::BeginPlay();
	MovementComponent->Activate();
}



