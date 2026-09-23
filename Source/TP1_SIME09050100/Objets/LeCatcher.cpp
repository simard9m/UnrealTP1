// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/LeCatcher.h"

#include "AITypes.h"
#include "LeBonus.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/MapErrors.h"
#include "TP1_SIME09050100GameMode.h"

// Sets default values
ALeCatcher::ALeCatcher()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this,&ALeCatcher::OnCatchOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);
	
	FloatingMovement =  CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovement"));
	FloatingMovement->UpdatedComponent = RootComponent;
	
	FloatingMovement->MaxSpeed = 1200.0f;
	FloatingMovement->Acceleration = 2000.0f;
	FloatingMovement->Deceleration = 0.0f;
}

// Called when the game starts or when spawned
void ALeCatcher::BeginPlay()
{
	Super::BeginPlay();
	
	ObjectToCatch = UGameplayStatics::GetActorOfClass(GetWorld(), ALeBonus::StaticClass());
}

// Called every frame
void ALeCatcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!IsValid(ObjectToCatch))
	{
		ObjectToCatch = UGameplayStatics::GetActorOfClass(
			GetWorld(),
			ALeBonus::StaticClass()
		);
	}

	if (IsValid(ObjectToCatch))
	{
		FVector TargetPosition = ObjectToCatch->GetActorLocation();

		float DistanceY = FMath::Abs(TargetPosition.Y - GetActorLocation().Y);

		//Direct en dessous
		if (DistanceY < 15.0f)
		{
			FVector CurrentVelocity = FloatingMovement->Velocity;

			CurrentVelocity.Y = 0.0f;

			FloatingMovement->Velocity = CurrentVelocity;

			return;
		}

		FVector Steering = Seek(TargetPosition);

		Steering.X = 0.0f;
		Steering.Z = 0.0f;

		AddMovementInput(Steering.GetSafeNormal(),1.0f);
	}
}

// Called to bind functionality to input
void ALeCatcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ALeCatcher::Seek(FVector Position)
{
	FVector Desired = Position - GetActorLocation();
	
	Desired.X = 0.0f;
	Desired.Z = 0.0f;
	
	Desired.Normalize();
	
	Desired *= FloatingMovement->MaxSpeed;
	FVector Steering = Desired - FloatingMovement ->Velocity;
	
	return Steering;
}

void ALeCatcher::OnCatchOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	ALeBonus* Bonus = Cast<ALeBonus>(OtherActor);
	UE_LOG(LogTemp, Warning, TEXT("BONUS CAUGHT!"));
	if (Bonus)
	{
		ATP1_SIME09050100GameMode* GameMode =
			Cast<ATP1_SIME09050100GameMode>(UGameplayStatics::GetGameMode(this));

		if (GameMode)
		{
			GameMode->BonusCaught();
		}

		if (ObjectToCatch == Bonus)
		{
			ObjectToCatch = nullptr;
		}

		Bonus->Destroy();
	}
}


