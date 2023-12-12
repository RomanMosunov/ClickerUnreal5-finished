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
	FTimerHandle EverySecond;

	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ClickerMesh;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ClickPowerBtn;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> PassiveIncomeBtn;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UCameraComponent> MainCamera;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UTextRenderComponent> ScoreText;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UTextRenderComponent> ClickPowerTxt;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UTextRenderComponent> PassiveIncomeTxt;
	UPROPERTY(EditDefaultsOnly) TObjectPtr <UCurveFloat> CurveFloat;
	UPROPERTY(EditDefaultsOnly) TObjectPtr <USceneComponent> ClickerRoot;

	bool ClickPowerAvailable = false;
	bool PassiveIncomeAvailable = false;
	int32 Score = 0;
	int32 ClickPower = 1;
	int32 ClickPowerAdds = 1;
	int32 ClickPowerCost = 4;
	int32 PassiveIncome = 0;
	int32 PassiveIncomeAdds = 1;
	int32 PassiveIncomeCost = 10;
	UMaterialInstanceDynamic* ClickPowerMat;
	UMaterialInstanceDynamic* PassiveIncomeMat;

	UFUNCTION() void AddScorePerSecond();
	UFUNCTION() void BuyScorePerSecond(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	UFUNCTION() void ClickEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	UFUNCTION() void BuyClickPower(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);
	UFUNCTION() void TimelineProgress(const float Value);
	UFUNCTION() void UpdateShop();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
