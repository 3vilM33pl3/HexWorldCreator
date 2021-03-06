// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexagonActor.h"
#include "Containers/CircularQueue.h"

/**
 * 
 */
class HEXWORLDRUNTIME_API FHexWorldRunnable : FRunnable
{
private:
	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;
	uint64 Number;
	TFunction< void()> FunctionPointer;

	/** Use this thread-safe boolean to allow early exits for your threads */
	FThreadSafeBool Finished;

	static uint64 ThreadNumber;


public:
	FHexWorldRunnable(TCircularQueue<FHexagonCoordinates>* Data ,TFunction< void()> InFunction);
	~FHexWorldRunnable();


	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	static FHexWorldRunnable* RunLambdaOnBackgroundThread(TCircularQueue<FHexagonCoordinates>* Data ,TFunction<void()> InFunction);
	private:
	TCircularQueue<FHexagonCoordinates>* HexCoordData;
};
