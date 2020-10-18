// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactive.generated.h"


UINTERFACE(MinimalAPI)
class UInteractive : public UInterface
{
    GENERATED_BODY()
};

class AHRIANDBEAR_API IInteractive
{
    GENERATED_BODY()
public:
    virtual bool CanInteractive();
    virtual void Interact();
};
