#pragma once

#include <string>
#include <vector>
#include <iostream>

typedef enum {
    eUNIT_KG = 0,
    eUNIT_LBS = 1
} UNIT;

typedef enum {
    eExercise_Type_Unassigned = -1,
    eExercise_Type_Squat = 0,
    eExercise_Type_Snatch = 1,
    eExercise_Type_Clean = 2,
    eExercise_Type_Jerk = 3,
    eExercise_Type_Front = 4
    
} Exercise_Type;

typedef enum {
    eProgression_Protocol_Regular = 0,
    eProgression_Protocol_Aggressive = 1,
    eProgression_Protocol_User_Input = 2
} Progression_Protocol;





