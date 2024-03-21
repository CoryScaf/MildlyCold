// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Engine/EngineBaseTypes.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/MathFwd.h"
#include "UObject/ConstructorHelpers.h"
#include "HAL/Platform.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    boom_arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera boom"));
    boom_arm->SetupAttachment(RootComponent);
    boom_arm->TargetArmLength = 300.0f;
    boom_arm->bUsePawnControlRotation = true;

    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera->SetupAttachment(boom_arm, USpringArmComponent::SocketName);
    camera->bUsePawnControlRotation = true;

    character_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    character_mesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> face(TEXT("/Script/Engine.StaticMesh'/Game/Models/head.head'"));
    character_mesh->SetStaticMesh(face.Object);
    character_mesh->SetRelativeRotation(FRotator(0, 180, 0));
    character_mesh->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
    character_mesh->SetRelativeLocation(FVector(0, 0, -50));

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJump);
}

void AMainCharacter::MoveForward(float value) {
    FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y).RotateAngleAxis(-90.0, {0.0, 0.0, 1.0});
    AddMovementInput(dir, value);
}

void AMainCharacter::MoveRight(float value) {
    FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(dir, value);
}

void AMainCharacter::StartJump() {
    bPressedJump = true;
}

void AMainCharacter::StopJump() {
    bPressedJump = false;
}
