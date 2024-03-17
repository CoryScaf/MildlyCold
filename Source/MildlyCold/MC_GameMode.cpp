// Fill out your copyright notice in the Description page of Project Settings.


#include "MC_GameMode.h"
#include "CustomGameState.h"
#include "MildlyCold/MainCharacter.h"


AMC_GameMode::AMC_GameMode() {
    GameStateClass = ACustomGameState::StaticClass();
    DefaultPawnClass = AMainCharacter::StaticClass();
}
