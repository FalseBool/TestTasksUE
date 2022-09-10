// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Nest.generated.h"

UCLASS()
class TESTTASK2_API ANest : public AActor
{
	GENERATED_BODY()
	
public:
	ANest();

	UFUNCTION(BlueprintCallable)
	void SpawnAI();

	UPROPERTY(EditAnywhere, Category = GameplaySettings)
	TSubclassOf<class APawn> AiToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioSettings)
	class USoundBase* SpawnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplaySettings)
	class AActor* TargetDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplaySettings)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* AnimationCurve;
protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void EvaluateAnimation(float Value);

	UFUNCTION()
	virtual void AnimationFinished();

	UFUNCTION()
	void PlaySpawnAnimation();

	UPROPERTY()
	APawn* SpawnedPawn;

	UPROPERTY()
	FTimeline AnimationTimeline;

	// Blackboard values setuped by string key. Is should be done outside. It depends from passed Behaviour Tree.
	UFUNCTION(BlueprintImplementableEvent)
	void SetupBehaivour(APawn* target);
};
