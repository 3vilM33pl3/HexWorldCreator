// Fill out your copyright notice in the Description page of Project Settings.


#include "FHexWorldRunnable.h"

uint64 FHexWorldRunnable::ThreadNumber = 0;

FHexWorldRunnable::FHexWorldRunnable(TFunction< void()> InFunction)
{
    FunctionPointer = InFunction;
    Finished = false;
    Number = ThreadNumber;

    const FString ThreadName = FString::Printf(TEXT("HexWorld Back End Communication Thread %d"), ThreadNumber);
    Thread = FRunnableThread::Create(this, *ThreadName, 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
    ThreadNumber++;
}

FHexWorldRunnable::~FHexWorldRunnable()
{
    delete Thread;
    Thread = nullptr;
}


bool FHexWorldRunnable::Init()
{
    return true;
}

uint32 FHexWorldRunnable::Run()
{
    if(FunctionPointer)
    {
        FunctionPointer();
    }
    return 0;
}

void FHexWorldRunnable::Stop()
{
    Finished = true;
}

void FHexWorldRunnable::Exit()
{
    Finished = true;
    delete this;
}

FHexWorldRunnable* FHexWorldRunnable::RunLambdaOnBackgroundThread(TFunction<void()> InFunction)
{
    if(FPlatformProcess::SupportsMultithreading())
    {
        return new FHexWorldRunnable(InFunction);
    }
    else
    {
        return nullptr;
    }
    
}
