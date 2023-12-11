// Copy Rirght

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/TimelineComponent.h"
#include "ClickerPawn.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;
class UCameraComponent;
class UCurveFloat;
class USceneComponent;

UCLASS()
class CLICKER_API AClickerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AClickerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ClickerMesh;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ClickPowerBtn;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UCameraComponent> MainCamera;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UTextRenderComponent> ScoreText;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UTextRenderComponent> ClickPowerTxt;
	UPROPERTY(EditDefaultsOnly) TObjectPtr <UCurveFloat> CurveFloat;
	UPROPERTY(EditDefaultsOnly) TObjectPtr <USceneComponent> ClickerRoot;

	bool ClickPowerAvailable;
	int32 Score = 0;
	int32 ClickPower = 1;
	int32 ClickPowerAds = 1;
	int32 ClickPowerCost = 4;
	UMaterialInstanceDynamic* ClickPowerMat;

	UFUNCTION() void ClickEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	UFUNCTION() void TimelineProgress(const float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
