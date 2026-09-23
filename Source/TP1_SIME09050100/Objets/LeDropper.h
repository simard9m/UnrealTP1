// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LeDropper.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;
class ALeBonus;

UCLASS()
class TP1_SIME09050100_API ALeDropper : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALeDropper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;
	
	//le Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	
	//Mouvement
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	UFloatingPawnMovement* FloatingMovement;
	
	//Quel bonus va spawner
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropper")
	TSubclassOf<ALeBonus> BonusClass;
	
	//limites
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropper")
	float MinY = -800.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropper")
	float MaxY = 800.0f;
	
	//Distance qui dit si on a reach le point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropper")
	float AcceptanceRadius = 30.0f;
	
	//ou on drop le bonus
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dropper")
	FVector BonusSpawnOffset = FVector(0.0f, 0.0f, -100.0f);
	
private:
	//La position qu'on se dirige vers
	FVector TargetPosition;
	
	//Methodes internes pour dropper le bonus et choisir un target de position
	void ChooseNewTarget();
	
	void DropBonus();
};
