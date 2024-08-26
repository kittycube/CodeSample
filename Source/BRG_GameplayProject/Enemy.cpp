// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "PaperFlipbookComponent.h"
#include "PlayerCharacter.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
	GetRenderComponent()->SetSimulatePhysics(false);
	GetRenderComponent()->SetGenerateOverlapEvents(false);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	// add delegate for OnComponentHit
	GetRenderComponent()->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
}

// if an enemy is hit by the player from above, it dies. otherwise, the player dies
void AEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                   FVector NormalImpulse, const FHitResult& Hit)
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		// if hit from above
		if(Hit.Normal.Z < -0.50f)
		{
			// enemy falls through ground for a few seconds before being destroyed
			bIsActive = false;
			GetRenderComponent()->SetFlipbook(DisabledFlipbook);
			GetRenderComponent()->SetCollisionObjectType(ECC_GameTraceChannel1);
			GetRenderComponent()->SetSimulatePhysics(true);
			GetRenderComponent()->SetEnableGravity(true);
			SetLifeSpan(3.0f);
			// player bounces off dead enemy
			PlayerCharacter->LaunchCharacter(FVector(0.0f,0.0f,1000.0f), true, true);
		}
		else
		{
			GetRenderComponent()->SetFlipbook(CaughtMouseFlipbook);
			PlayerCharacter->Kill();
			bIsActive = false;
		}
	}
}