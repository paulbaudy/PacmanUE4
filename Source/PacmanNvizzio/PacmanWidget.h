// Paul BAUDY for Nvizzio Creations Inc

#pragma once

#include "Blueprint/UserWidget.h"
#include "PacmanWidget.generated.h"

/**
 * 
 */
UCLASS()
class PACMANNVIZZIO_API UPacmanWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, DisplayName = triggerWinEvent)
	void triggerWinEvent(bool win);
	
};
