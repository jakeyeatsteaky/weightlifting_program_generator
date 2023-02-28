#include "program_elements.hpp"

void Exercise::printExercise(){
    const char* unit;
    const char* name = getName().c_str();
    if(m_units)
        unit = "lbs";
    else
        unit = "kg";
    if(getExerciseType() == eExercise_Type_Unassigned)
        std::cout << "\t" << getName() << ": " << getSets() << " x " << getReps() << " @ " << getPercentage() << "%\n";
    else   
        std::cout << "\t" << getName() << ": " << getSets() << " x " << getReps() << " @ " << getWeight()  << unit << " (" << getPercentage() << "%)\n";
}

void Day::printDay(){
    
    std::cout << "Day: " << getIdx() << std::endl;
    for(Exercise* ex : m_exercises){
        std::cout << "\t\t";
        ex->printExercise();
    }
}

void Week::printWeek(){
    std::cout << "Week: " << getIdx() << std::endl;
    for(Day* day : m_trainingDays){
        std::cout << "\t\t";
        day->printDay();
    }
}

void Program::printProgram(){
    const char* name = getName().c_str();
    std::cout << name << " Program: " << std::endl;
    for(Week* week : m_weeks){
        std::cout << "\t";
        week->printWeek();
    }
}

void destroyProgram(Program* program, Athlete* athlete){
    for(Week* week : program->getWeeks()){
        for(Day* day : week->getDays()) {
            for(Exercise* ex : day->getExercises()) {
                delete ex;
            }
            delete day;
        }
        delete week;
    }
    delete program;
    delete athlete;

}