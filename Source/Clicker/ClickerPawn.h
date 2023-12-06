// Copy Rirght

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ClickerPawn.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;
class UCameraComponent;

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

	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ClickerMesh;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UCameraComponent> MainCamera;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UTextRenderComponent> ScoreText;

	UPROPERTY() int32 Score = 0;
	UPROPERTY() int32 ClickPower = 1;

	UFUNCTION() void ClickEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
