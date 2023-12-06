// Copy Rirght

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClickerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER_API AClickerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
};
