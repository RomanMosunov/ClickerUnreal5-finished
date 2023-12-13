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

	//Create components of class
	ClickerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClickerMesh"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));
	ClickerRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ClickerRoot"));
	ClickPowerBtn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClickPowerBtn"));
	ClickPowerTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ClickPowerTxt"));
	PassiveIncomeBtn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PassiveIncomeBtn"));
	PassiveIncomeTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("PassiveIncomeTxt"));

	check(ClickerRoot);
	check(ClickerMesh);
	check(MainCamera);
	check(ScoreText);
	check(ClickPowerBtn);
	check(ClickPowerTxt);
	check(PassiveIncomeBtn);
	check(PassiveIncomeTxt);

	//Setup component Defaults
	SetRootComponent(ClickerRoot);

	ClickerMesh->SetupAttachment(ClickerRoot);
	ClickerMesh->SetRelativeLocation(FVector::ZeroVector);

	MainCamera->SetupAttachment(ClickerRoot);
	MainCamera->SetRelativeLocation(FVector(-600.0, 400.0, 200.0));

	ScoreText->SetupAttachment(ClickerRoot);
	ScoreText->SetRelativeTransform(FTransform(FRotator(0.0, 180.0, 0.0), FVector(0.0, 0.0, 200.0), FVector::OneVector));
	ScoreText->SetWorldSize(100);

	ClickPowerBtn->SetupAttachment(ClickerRoot);
	ClickPowerBtn->SetRelativeLocation(FVector(0.0, 500.0, 400.0));

	ClickPowerTxt->SetupAttachment(ClickerRoot);
	ClickPowerTxt->SetRelativeTransform(FTransform(FRotator(0.0, 180.0, 0.0), FVector(0.0, 600.0, 350.0), FVector::OneVector));
	ClickPowerTxt->SetWorldSize(50);

	PassiveIncomeBtn->SetupAttachment(ClickerRoot);
	PassiveIncomeBtn->SetRelativeLocation(FVector(0.0, 500.0, 200.0));
	
	PassiveIncomeTxt->SetupAttachment(ClickerRoot);
	PassiveIncomeTxt->SetRelativeTransform(FTransform(FRotator(0.0, 180.0, 0.0), FVector(0.0, 600.0, 200.0), FVector::OneVector));
	PassiveIncomeTxt->SetWorldSize(50);

	//Set OnClick Events
	ClickerMesh->OnClicked.AddDynamic(this, &AClickerPawn::ClickEvent);
	ClickPowerBtn->OnClicked.AddDynamic(this, &AClickerPawn::BuyClickPower);
	PassiveIncomeBtn->OnClicked.AddDynamic(this, &AClickerPawn::BuyScorePerSecond);
}

// Called when the game starts or when spawned
void AClickerPawn::BeginPlay()
{
	Super::BeginPlay();

	//Create material instances
	ClickPowerMat = ClickPowerBtn->CreateAndSetMaterialInstanceDynamic(0);
	PassiveIncomeMat = PassiveIncomeBtn->CreateAndSetMaterialInstanceDynamic(0);
	
	//Add Float track for "Timeline" function
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}

	// Set timer for "Passive income" function
	if (!EverySecond.IsValid())
	{
		GetWorldTimerManager().SetTimer(EverySecond, this, &AClickerPawn::AddScorePerSecond, 1.0, true);
	}
		AClickerPawn::UpdateShop();
}

void AClickerPawn::AddScorePerSecond()
{
	Score += PassiveIncome;
	AClickerPawn::UpdateShop();
}

void AClickerPawn::BuyScorePerSecond(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (PassiveIncomeAvailable)
	{
		Score -= PassiveIncomeCost;
		PassiveIncome += 1;
		PassiveIncomeCost *= 2;
		AClickerPawn::UpdateShop();
	}
}

void AClickerPawn::ClickEvent(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Score += ClickPower;
	AClickerPawn::UpdateShop();
	CurveTimeline.PlayFromStart();
}

void AClickerPawn::BuyClickPower(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (ClickPowerAvailable)
	{
		Score -= ClickPowerCost;
		ClickPower += ClickPowerAdds;
		ClickPowerCost *= 2;
		AClickerPawn::UpdateShop();
	}
}

//Timeline function (simple animation)
void AClickerPawn::TimelineProgress(const float Value)
{
	const FVector StartScale = FVector::OneVector;
	const FVector EndScale = FVector(0.8, 0.8, 0.8);
	const FVector NewScale = FMath::Lerp(StartScale, EndScale, Value);
	ClickerMesh->SetRelativeScale3D(NewScale);
}

//base function, that updates shop state every second
void AClickerPawn::UpdateShop()
{
	//Format String data and Setup Text components
	FString Active = FString::Printf(TEXT("Click power: %d \n Next level: %d"), ClickPower, ClickPowerCost);
	FString Passive = FString::Printf(TEXT("Score per second: %d \n Next level: %d"), PassiveIncome, PassiveIncomeCost);
	ClickPowerTxt->SetText(FText::FromString(Active));
	PassiveIncomeTxt->SetText(FText::FromString(Passive));
	ScoreText->SetText(FText::AsNumber(Score));

	//Dynamic update for material color
	{
		if (ClickPowerMat)
			if (Score >= ClickPowerCost)
			{
				ClickPowerAvailable = true;
				ClickPowerMat->SetVectorParameterValue("Color", FLinearColor(0.2, 1.0, 0.2));
				//ClickPowerMat->SetVectorParameterValue("Color", FLinearColor::Green);
			}
			else
			{
				ClickPowerAvailable = false;
				ClickPowerMat->SetVectorParameterValue("Color", FLinearColor::Gray);
			}
	}
	if(PassiveIncomeMat)
	{
		if (Score >= PassiveIncomeCost)
		{
			PassiveIncomeAvailable = true;
			PassiveIncomeMat->SetVectorParameterValue("Color", FLinearColor(0.2, 1.0, 0.2));
		}
		else
		{
			PassiveIncomeAvailable = false;
			PassiveIncomeMat->SetVectorParameterValue("Color", FLinearColor::Gray);
		}
	}
}

// Called every frame
void AClickerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get Delta time for Timeline animation
	CurveTimeline.TickTimeline(DeltaTime);
}
