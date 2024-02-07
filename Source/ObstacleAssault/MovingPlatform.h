// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UENUM()
enum class EDirection : uint8
{
	Forward,
	Back,
	Left,
	Right,
	Up,
	Down
};

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void MovePlatform(const float DeltaTime);
	void RotatePlatform(const float DeltaTime);
	double GetDistanceFromStartLocation() const;
	bool HasPlatformReachedLimit() const;
	FVector GetDirectionVector(EDirection direction) const;
	EDirection GetOpposedDirectionVector(EDirection direction) const;
	void LogOvershootDistanceIfAny() const;

	UPROPERTY(EditAnywhere, meta = (DisplayThumbnail = "true"))
	AActor* const target = nullptr;

	UPROPERTY(EditAnywhere)
	FVector targetDifference = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere)
	float speed = 1;

	UPROPERTY(EditAnywhere)
	float distanceLimit = 0;

	UPROPERTY(EditAnywhere)
	FRotator rotationSpeed;

	UPROPERTY(EditAnywhere)
	EDirection ED_Direction = EDirection::Forward;

	FVector startLocation = FVector(0, 0, 0);

	//UPROPERTY(VisibleAnywhere)
	//double currentDistanceFromStartLocation = 0;
};
