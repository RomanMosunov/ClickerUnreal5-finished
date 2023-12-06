// Copy Rirght


#include "ClickerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AClickerPawn::AClickerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClickerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClickerMesh"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));

	SetRootComponent(ClickerMesh);
	MainCamera->SetupAttachment(ClickerMesh);
	ScoreText->SetupAttachment(ClickerMesh);

	ClickerMesh->OnClicked.AddDynamic(this, &AClickerPawn::ClickEvent);
}

// Called when the game starts or when spawned
void AClickerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AClickerPawn::ClickEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Score += ClickPower;
	ScoreText->SetText(FText::AsNumber(Score));
}

// Called every frame
void AClickerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
