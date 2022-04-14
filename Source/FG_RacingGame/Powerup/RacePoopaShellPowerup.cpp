#include "RacePoopaShellPowerup.h"
#include "RacePoopaShell.h"

void URacePoopaShellPowerup::OnPowerupActivated_Implementation()
{
	FTransform SpawnTransform = GetOwner()->GetActorTransform();
	SpawnTransform.AddToTranslation(GetOwner()->GetActorForwardVector() * SpawnOffset);

	GetWorld()->SpawnActor(PoopaClass, &SpawnTransform);
}
