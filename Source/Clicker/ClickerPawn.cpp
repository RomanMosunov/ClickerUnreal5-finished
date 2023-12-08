// Copy Rirght


#include "ClickerPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AClickerPawn::AClickerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClickerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClickerMesh"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));
	ClickerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ClickerRoot"));

	check(ClickerRoot);
	check(ClickerMesh);
	check(MainCamera);
	check(ScoreText);

	SetRootComponent(ClickerRoot);

	ClickerMesh->SetupAttachment(ClickerRoot);
	ClickerMesh->SetRelativeLocation(FVector::ZeroVector);

	MainCamera->SetupAttachment(ClickerRoot);
	MainCamera->SetRelativeLocation(FVector(-600, 400, 200));

	ScoreText->SetupAttachment(ClickerRoot);
	ScoreText->SetRelativeTransform(FTransform(FRotator(0, 180, 0), FVector(0, 0, 200.0), FVector::OneVector));
	ScoreText->SetWorldSize(100);

	ClickerMesh->OnClicked.AddDynamic(this, &AClickerPawn::ClickEvent);
}

// Called when the game starts or when spawned
void AClickerPawn::BeginPlay()
{
	Super::BeginPlay();
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}
}

void AClickerPawn::ClickEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Score += ClickPower;
	ScoreText->SetText(FText::AsNumber(Score));
	CurveTimeline.PlayFromStart();
}

void AClickerPawn::TimelineProgress(const float Value)
{
	const FVector StartScale = FVector::OneVector;
	const FVector EndScale = FVector(0.8, 0.8, 0.8);
	const FVector NewScale = FMath::Lerp(StartScale, EndScale, Value);
	ClickerMesh->SetRelativeScale3D(NewScale);
}

// Called every frame
void AClickerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);
}
