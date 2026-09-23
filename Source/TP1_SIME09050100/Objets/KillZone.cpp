// Fill out your copyright notice in the Description page of Project Settings.


#include "Objets/KillZone.h"
#include "LeBonus.h"
#include "Components/BoxComponent.h"
#include "TP1_SIME09050100GameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKillZone::AKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	
	BoxCollision->SetGenerateOverlapEvents(true);
	
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this,&AKillZone::OnOverlap);
	
}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();

}
void AKillZone::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	ALeBonus* Bonus = Cast<ALeBonus>(OtherActor);

	if (Bonus)
	{
		UE_LOG(LogTemp, Warning, TEXT("BONUS MISSED"));

		ATP1_SIME09050100GameMode* GameMode =
			Cast<ATP1_SIME09050100GameMode>(UGameplayStatics::GetGameMode(this));

		if (GameMode)
		{
			GameMode->BonusMissed();
		}

		Bonus->Destroy();
	}
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

