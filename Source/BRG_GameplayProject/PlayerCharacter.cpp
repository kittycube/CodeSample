// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GamePlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

float GroundMoveSpeed = 2000.0f;
float JumpMoveSpeed = 500.0f;
FVector SpriteLocation = FVector(-40.0f,0.0f,-40.0f);

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Configure sizing
	GetCapsuleComponent()->InitCapsuleSize(52.0f,52.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetSimulatePhysics(true);
	GetSprite()->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));
	GetSprite()->SetRelativeLocation(SpriteLocation);

	// Configure character movement
	GetCharacterMovement()->MaxStepHeight = 0.0f; // cannot automatically step up, must jump
	GetCharacterMovement()->MaxWalkSpeed = GroundMoveSpeed;
	GetCharacterMovement()->JumpZVelocity = 2000.0f;
	GetCharacterMovement()->AirControl = 0.75f;
	GetCharacterMovement()->GravityScale = 3.0F;
	
	// Create a camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1500.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
	CameraBoom->SocketOffset = FVector(0.0f,0.0f,700.0f);
	
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// hide player character and disable movement upon death
void APlayerCharacter::Kill()
{
	if(const AGamePlayerController* GPC = Cast<AGamePlayerController>(GetController()))
	{
		// display lose text
		GPC->GetGameWidget()->LoseGame();
	}
	GetCapsuleComponent()->SetSimulatePhysics(false);
	GameStatus = Lost;
	GetSprite()->SetVisibility(false);
	GetMovementComponent()->Deactivate();
}

// hide player character and disable movement when won
void APlayerCharacter::WinGame()
{
	if(const AGamePlayerController* GPC = Cast<AGamePlayerController>(GetController()))
	{
		// display win text
		GPC->GetGameWidget()->WinGame();
	}
	GameStatus = Won;
	GetSprite()->SetVisibility(false);
	GetMovementComponent()->Deactivate();
}

// increment cheese count by 1 and update displayed text
void APlayerCharacter::EatCheese()
{
	CheeseCount++;
	if(const AGamePlayerController* GPC = Cast<AGamePlayerController>(GetController()))
	{
		GPC->GetGameWidget()->ChangeCheeseCount(CheeseCount);
	}}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//initial set up of camera z height
	const AActor* PlayerStart = UGameplayStatics::GetGameMode(this)->FindPlayerStart(GetController());
	const FVector StartLocation = PlayerStart->GetActorLocation();
	CameraZ = StartLocation.Z + CameraBoom->SocketOffset.Z;
	StartZ = CameraZ;
	
	GetMovementComponent()->Activate();
}

// left and right movement based on input
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		// MovementValue is input float, -1 for left, 1 for right
		const float MovementValue = Value.Get<float>();
		// add movement
		const FVector ForwardDirection = FVector::ForwardVector;
		AddMovementInput(ForwardDirection, MovementValue);
		// adjust sprite location to keep capsule component at the head
		FVector TempLocation = SpriteLocation;
		TempLocation.X *= MovementValue;
		GetSprite()->SetRelativeLocation(TempLocation);
		// switch sprite direction
		if(MovementValue >= 0)
		{
			GetSprite()->SetRelativeRotation(FRotator(0.0f,0.0f,0.0f));
		}
		else
		{
			GetSprite()->SetRelativeRotation(FRotator(0.0f,180.0f,0.0));
		}
	}
}

// overriden jump function for custom air movement
void APlayerCharacter::Jump()
{
	// slow movement in the air
	if(!GetCharacterMovement()->IsFalling())
	{
		Super::Jump();
		GetCharacterMovement()->Velocity /= 2;
		GetCharacterMovement()->MaxWalkSpeed = JumpMoveSpeed;
	}
}

// reset the game level
void APlayerCharacter::RestartGame()
{
	// disabled while in game
	if(GameStatus != Playing)
	{
		GameStatus = Playing;
		const FName LevelName = *UGameplayStatics::GetCurrentLevelName(this);
		UGameplayStatics::OpenLevel(this, LevelName);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// determine panning
	AGamePlayerController* GPC = Cast<AGamePlayerController>(GetController());
	FVector2D ScreenLocation;
	GPC->ProjectWorldLocationToScreen(GetActorLocation(),ScreenLocation);
	int X;
	int ViewportY;
	GPC->GetViewportSize(X,ViewportY);
	if(ScreenLocation.Y < 0.0f && !bPannedUp)
	{
		CameraZ = GetActorLocation().Z + CameraBoom->SocketOffset.Z;
		bPannedUp = true;
	}
	if(ScreenLocation.Y > ViewportY)
	{
		CameraZ = StartZ;
		bPannedUp = false;
	}
	// keep camera Z locked
	FVector CamLocation = FollowCamera->GetComponentLocation();
	CamLocation.Z = CameraZ;
	FollowCamera->SetWorldLocation(CamLocation);
	
	// resume walking speed if on ground
	if(GetCharacterMovement()->IsMovingOnGround())
	{
		GetCharacterMovement()->MaxWalkSpeed = GroundMoveSpeed;
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Restart
		EnhancedInputComponent->BindAction(RestartAction, ETriggerEvent::Triggered, this, &APlayerCharacter::RestartGame);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

