// Fill out your copyright notice in the Description page of Project Settings.


#include "ABStatModifierInterface.h"

// Add default functionality here for any IABStatModifierInterface functions that are not pure virtual.

bool IABStatModifierInterface::operator<(const IABStatModifierInterface* right) const {
	return GetPriority() < right->GetPriority();
}
