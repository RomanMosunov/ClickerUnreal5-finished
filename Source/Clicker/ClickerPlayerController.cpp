// Copy Rirght


#include "ClickerPlayerController.h"

void AClickerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}
