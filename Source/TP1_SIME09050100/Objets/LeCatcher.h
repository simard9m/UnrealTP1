// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LeCatcher.generated.h"

class UFloatingPawnMovement;

UCLASS()
class TP1_SIME09050100_API ALeCatcher : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALeCatcher();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;
	
	UPROPERTY(VisibleAnywhere,Category=Movement)
	TObjectPtr<UFloatingPawnMovement> FloatingMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinY = -800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxY = 800.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float IdleSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idle")
	float IdleAcceptanceRadius = 40.0f;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	AActor* ObjectToCatch;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector Seek(FVector Position);
	
	UFUNCTION()
	void OnCatchOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	FVector IdleTarget;

	void ChooseNewIdleTarget();

	FVector SeekWithSpeed(FVector Position, float Speed);

};
