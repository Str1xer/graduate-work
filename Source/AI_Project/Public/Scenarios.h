#pragma once

#include "CoreMinimal.h"

class AAIC_Agent;

namespace SCR_Harvest
{
	void addActions(AAIC_Agent* ref, AActor* Harvest);
	bool validate();
}

namespace SCR_Attack
{
	void addActions(AAIC_Agent* ref, AActor* Enemy);
	bool validate();
}