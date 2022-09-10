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
	TSubclassOf<class APawn> AIToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AudioSettings)
	class USoundBase* SpawnSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplaySettings)
	class AActor* TargetDest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplaySettings)
	class UBehaviorTree* BehaviorTree;

protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	// Blackboard values setups by string key. Is should be done outside. It depends from passed Behaviour three.
	UFUNCTION(BlueprintImplementableEvent)
	void SetupBehaivour(APawn* target);

	UFUNCTION()
	void PlayScaleAnimation();

private:
	UPROPERTY()
	APawn* SpawnedPawn;

	UPROPERTY()
	FTimeline AnimationTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* AnimationCurve;

	UFUNCTION()
	void EvaluateAnimation(float Value);

	UFUNCTION()
	void AnimationFinished();
};
