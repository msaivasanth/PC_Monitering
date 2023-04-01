// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"
#include "MyActor.h"
#include "MyGameInstance.h"
//#include "MyGameInstance.h"

// Sets default values
AMyActor1::AMyActor1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor1::BeginPlay()
{
	Super::BeginPlay();
	//FActorSpawnParameters sp;
	//sp.Owner = this;

	//FVector loc(490.0f, -990.0f, 150.0f);
	//FRotator rot(0.0f,0.0f,0.0f);
	///*GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	//int32 lab=0;
	//int32 sys=0;
	//if (GameInstance)
	//{
	//	if (GameInstance->WebSocket->IsConnected())
	//	{
	//		lab = GameInstance->lab;
	//		sys = GameInstance->sys;
	//	}
	//	
	//}*/
	//for (int i = 0; i < 10; i++) {
	//	if (i%10 == 0) {
	//		loc.Y = -990.0f;
	//		loc.X -= 50 + 100.0f;
	//	}
	//	loc.Y += 50 + 100.0f;
	//	GetWorld()->SpawnActor<AActor>(Actortospawn, loc, rot);
	//}

}

// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FActorSpawnParameters sp;
	sp.Owner = this;

	FVector loc(490.0f, -990.0f, 150.0f);
	FRotator rot(0.0f, 0.0f, 0.0f);
	GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
	if (GameInstance)
	{
		if (GameInstance->WebSocket->IsConnected())
		{
			TSharedPtr<FJsonObject> MyJson = MakeShareable(new FJsonObject);
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(GameInstance->jsonstring);
			if (FJsonSerializer::Deserialize(Reader, MyJson)) {
				/*GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "lab No: " + MyJson->GetStringField("lab"));
				GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Cyan, "No of system: " + MyJson->GetStringField("sys"));*/
				if (MyJson->TryGetField("lab")) {
					lab = FCString::Atoi(*MyJson->GetStringField("lab"));
					sys = FCString::Atoi(*MyJson->GetStringField("sys"));
				}
				/*else if (MyJson->TryGetField("MAC")) {
					if (!mactono.Contains(MyJson->GetStringField("MAC"))) {
						mactono.Add(MyJson->GetStringField("MAC"), c);
						c++;
					}
				}*/
			}
		}

	}
	while(i<=sys) {
		if (i % 10 == 0) {
			loc.Y = -990.0f;
			loc.X -= 70 + 100.0f;
		}
		loc.Y += 70 + 100.0f;
		a = GetWorld()->SpawnActor<AActor>(Actortospawn, loc, rot);
		actortono.Add(a->GetName(), i);
		//UE_LOG(LogTemp, Warning, TEXT("i: %s"), *a->GetName());
		i++;
	}
}

