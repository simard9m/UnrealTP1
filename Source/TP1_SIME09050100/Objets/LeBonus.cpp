// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/LeBonus.h"

#include "Components/BoxComponent.h"

// Sets default values
ALeBonus::ALeBonus()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void ALeBonus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALeBonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALeBonus::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

