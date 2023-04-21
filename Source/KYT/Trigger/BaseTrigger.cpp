// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTrigger.h"

// Sets default values
ABaseTrigger::ABaseTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(mRoot);

	//mRoot->bVisualizeComponent = true;

	mShape = ETriggerShape::Box;

}

void ABaseTrigger::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (mBox && mShape == ETriggerShape::Box)
		return;

	else if (mSphere && mShape == ETriggerShape::Sphere)
		return;

	else if (mCapsule && mShape == ETriggerShape::Capsule)
		return;

	if (mBox)
	{
		mBox->DetachFromParent();
		mBox->DestroyComponent();
		mBox = nullptr;
	}

	else if (mSphere)
	{
		mSphere->DetachFromParent();
		mSphere->DestroyComponent();
		mSphere = nullptr;
	}

	else if (mCapsule)
	{
		mCapsule->DetachFromParent();
		mCapsule->DestroyComponent();
		mCapsule = nullptr;
	}

	switch (mShape)
	{
	case ETriggerShape::Box:
		mBox = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), TEXT("Box"));
		mBox->RegisterComponent();
		mBox->AttachToComponent(mRoot, FAttachmentTransformRules::KeepRelativeTransform);

		mBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrigger::BeginOverlap);
		mBox->OnComponentEndOverlap.AddDynamic(this, &ABaseTrigger::EndOverlap);
		break;
	case ETriggerShape::Sphere:
		mSphere = NewObject<USphereComponent>(this, USphereComponent::StaticClass(), TEXT("Sphere"));
		mSphere->RegisterComponent();
		mSphere->AttachToComponent(mRoot, FAttachmentTransformRules::KeepRelativeTransform);

		mSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrigger::BeginOverlap);
		mSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseTrigger::EndOverlap);
		break;
	case ETriggerShape::Capsule:
		mCapsule = NewObject<UCapsuleComponent>(this, UCapsuleComponent::StaticClass(), TEXT("Capsule"));
		mCapsule->RegisterComponent();
		mCapsule->AttachToComponent(mRoot, FAttachmentTransformRules::KeepRelativeTransform);

		mCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrigger::BeginOverlap);
		mCapsule->OnComponentEndOverlap.AddDynamic(this, &ABaseTrigger::EndOverlap);
		break;
	}

	ChangeCollisionProfile(TEXT("PlayerTrigger"));
}

// Called when the game starts or when spawned
void ABaseTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTrigger::ChangeShape(ETriggerShape Shape)
{
	if (mShape == Shape)
		return;

	if (mBox)
	{
		mBox->DetachFromParent();
		mBox->DestroyComponent();
		mBox = nullptr;
	}

	else if (mSphere)
	{
		mSphere->DetachFromParent();
		mSphere->DestroyComponent();
		mSphere = nullptr;
	}

	else if (mCapsule)
	{
		mCapsule->DetachFromParent();
		mCapsule->DestroyComponent();
		mCapsule = nullptr;
	}

	switch (Shape)
	{
	case ETriggerShape::Box:
		mBox = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), TEXT("Box"));
		mBox->RegisterComponent();
		mBox->AttachToComponent(mRoot, FAttachmentTransformRules::KeepRelativeTransform);

		mBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrigger::BeginOverlap);
		mBox->OnComponentEndOverlap.AddDynamic(this, &ABaseTrigger::EndOverlap);
		break;
	case ETriggerShape::Sphere:
		mSphere = NewObject<USphereComponent>(this, USphereComponent::StaticClass(), TEXT("Sphere"));
		mSphere->RegisterComponent();
		mSphere->AttachToComponent(mRoot, FAttachmentTransformRules::KeepRelativeTransform);

		mSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrigger::BeginOverlap);
		mSphere->OnComponentEndOverlap.AddDynamic(this, &ABaseTrigger::EndOverlap);
		break;
	case ETriggerShape::Capsule:
		mCapsule = NewObject<UCapsuleComponent>(this, UCapsuleComponent::StaticClass(), TEXT("Capsule"));
		mCapsule->RegisterComponent();
		mCapsule->AttachToComponent(mRoot, FAttachmentTransformRules::KeepRelativeTransform);

		mCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABaseTrigger::BeginOverlap);
		mCapsule->OnComponentEndOverlap.AddDynamic(this, &ABaseTrigger::EndOverlap);
		break;
	}

	mShape = Shape;
}

void ABaseTrigger::ChangeCollisionProfile(const FString& Name)
{
	switch (mShape)
	{
	case ETriggerShape::Box:
		mBox->SetCollisionProfileName(*Name);
		break;
	case ETriggerShape::Sphere:
		mSphere->SetCollisionProfileName(*Name);
		break;
	case ETriggerShape::Capsule:
		mCapsule->SetCollisionProfileName(*Name);
		break;
	}
}

void ABaseTrigger::EnableCollision(bool Enable)
{
	switch (mShape)
	{
	case ETriggerShape::Box:
		if (!Enable)
			mBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		else
			mBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	case ETriggerShape::Sphere:
		if (!Enable)
			mSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		else
			mSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	case ETriggerShape::Capsule:
		if (!Enable)
			mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		else
			mCapsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		break;
	}
}

void ABaseTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TriggerBegin(SweepResult, OtherActor);

}

void ABaseTrigger::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TriggerEnd();

}

void ABaseTrigger::TriggerBegin(const FHitResult& SweepResult, AActor* OtherActor)
{
}

void ABaseTrigger::TriggerEnd()
{
}

