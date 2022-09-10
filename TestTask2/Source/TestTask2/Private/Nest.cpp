// Fill out your copyright notice in the Description page of Project Settings.

#include "Nest.h"
#include "DrawDebugHelpers.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ANest::ANest()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANest::BeginPlay()
{
	Super::BeginPlay();
	if (AnimationCurve)
	{
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;

		TimelineCallback.BindUFunction(this, FName(TEXT("EvaluateAnimation")));
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("AnimationFinished")});
		AnimationTimeline.AddInterpFloat(AnimationCurve, TimelineCallback);
		AnimationTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

void ANest::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AnimationTimeline.TickTimeline(deltaTime);
}

void ANest::EvaluateAnimation(float Value)
{
	SpawnedPawn->SetActorScale3D(FVector(Value));
}

void ANest::AnimationFinished()
{
	SetupBehaivour(SpawnedPawn);
}

void ANest::SpawnAI()
{
	if (AnimationTimeline.IsPlaying())
	{
		return;
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FTransform Transform;
	Transform.SetLocation(GetActorLocation());
	Transform.SetRotation(GetActorQuat());
	Transform.SetScale3D(FVector::ZeroVector);

	SpawnedPawn = GetWorld()->SpawnActor<APawn>(AIToSpawn, Transform, SpawnParameters);
	PlayScaleAnimation();
}

void ANest::PlayScaleAnimation()
{
	if (!AnimationCurve)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("AnimationCurve is not set!"));
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SpawnSound, GetActorLocation());
	AnimationTimeline.PlayFromStart();
}
