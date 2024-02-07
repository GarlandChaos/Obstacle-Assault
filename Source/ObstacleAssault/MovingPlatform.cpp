// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (target != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Actor was not null"), *GetName());
		startLocation = target->GetActorLocation() + targetDifference;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Actor was null"), *GetName());
		startLocation = GetActorLocation();
	}

	SetActorLocation(startLocation);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(const float DeltaTime)
{

	if (HasPlatformReachedLimit()) 
	{
		startLocation = startLocation + GetDirectionVector(ED_Direction) * distanceLimit;
		ED_Direction = GetOpposedDirectionVector(ED_Direction);
	}
	
	FVector localVector = GetActorLocation() + GetDirectionVector(ED_Direction) * speed * DeltaTime;
	SetActorLocation(localVector);
}

void AMovingPlatform::RotatePlatform(const float DeltaTime)
{
	//UE_LOG(LogTemp, Display, TEXT("Rotating platform with delta time: %f"), DeltaTime);
	AddActorLocalRotation(rotationSpeed * DeltaTime);
}

double AMovingPlatform::GetDistanceFromStartLocation() const
{	
	return FVector::Dist(startLocation, GetActorLocation());;
}

bool AMovingPlatform::HasPlatformReachedLimit() const
{
	return GetDistanceFromStartLocation() >= distanceLimit;
}

FVector AMovingPlatform::GetDirectionVector(EDirection direction) const
{
	switch (direction)
	{
		case EDirection::Forward:
			return FVector(1, 0, 0);
		case EDirection::Back:
			return FVector(-1, 0, 0);
		case EDirection::Left:
			return FVector(0, -1, 0);
		case EDirection::Right:
			return FVector(0, 1, 0);
		case EDirection::Up:
			return FVector(0, 0, 1);
		case EDirection::Down:
			return FVector(0, 0, -1);
		default:
			return FVector(0, 0, 0);
	}
}

EDirection AMovingPlatform::GetOpposedDirectionVector(EDirection direction) const
{
	switch (direction)
	{
		default:
		case EDirection::Forward:
			return EDirection::Back;
		case EDirection::Back:
			return EDirection::Forward;
		case EDirection::Left:
			return EDirection::Right;
		case EDirection::Right:
			return EDirection::Left;
		case EDirection::Up:
			return EDirection::Down;
		case EDirection::Down:
			return EDirection::Up;
	}
}

void AMovingPlatform::LogOvershootDistanceIfAny() const
{
	double distanceFromStartLocation = GetDistanceFromStartLocation();
	if (distanceFromStartLocation >= distanceLimit)
	{
		float overshootDistance = distanceFromStartLocation - distanceLimit;
		UE_LOG(LogTemp, Warning, TEXT("Overshoot distance from %s: %f"), *GetName(), overshootDistance);
	}
}