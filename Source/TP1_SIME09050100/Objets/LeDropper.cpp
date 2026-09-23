// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/LeDropper.h"

#include "LeBonus.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TP1_SIME09050100GameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALeDropper::ALeDropper()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Boxcollison qui est la root
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	
	//mesh qui suit
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);
	
	//component de mouvements
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	FloatingMovement->UpdatedComponent = RootComponent;
	
	//valeur de base
	FloatingMovement->MaxSpeed = 400.0f;
	FloatingMovement->Acceleration = 1200.0f;
	FloatingMovement->Deceleration = 1200.0f;

}

// Called when the game starts or when spawned
void ALeDropper::BeginPlay()
{
	Super::BeginPlay();
	//Choisir le targer de  mouvements
	ChooseNewTarget();
}

// Called every frame
void ALeDropper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Direction = TargetPosition - GetActorLocation();

	//Clamp le vector a seulement le Y
	Direction.X = 0.0f;
	Direction.Z = 0.0f;
	
	//Check si on est arrive
	if (FMath::Abs(Direction.Y) <= AcceptanceRadius)
	{
		//Drop le bonus, choisi la prochaine position. poteau
		DropBonus();
		ChooseNewTarget();
		return;
	}
	
	//s<en va vers la destination
	AddMovementInput(Direction.GetSafeNormal(), 1.0f);
}

void ALeDropper::ChooseNewTarget()
{
	TargetPosition = GetActorLocation();

	// position random dans le range
	TargetPosition.Y = FMath::FRandRange(MinY, MaxY);
}

//Bullshgit pour drop le bonus
void ALeDropper::DropBonus()
{
	if (!BonusClass)
	{
		return;
	}

	FVector SpawnLocation = GetActorLocation() + BonusSpawnOffset;

	FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParameters;

	SpawnParameters.Owner = this;

	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ALeBonus* SpawnedBonus = GetWorld()->SpawnActor<ALeBonus>(BonusClass,SpawnLocation,SpawnRotation,SpawnParameters);
	if (SpawnedBonus)
	{
		ATP1_SIME09050100GameMode* GameMode =
			Cast<ATP1_SIME09050100GameMode>(
				UGameplayStatics::GetGameMode(this)
			);

		if (GameMode)
		{
			GameMode->BonusSpawned();
		}
	}
}

