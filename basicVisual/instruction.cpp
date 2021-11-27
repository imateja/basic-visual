//Probably soon redundant class when we merge AST classes with the ui
//Should do a major overhaul of this class with abstract methods for AST classes

#include "instruction.h"

Instruction::Instruction(QString instructionText, TypeOfInstruction type)
    :_instructionText(instructionText)
    ,_typeOfInstruction(type)
{

}

//Add more specific instructions to this "toString" so we can put what type of the instruction out instruction is
QString Instruction::TypeOfInstructionToString()
{
    switch(_typeOfInstruction){
        case TypeOfInstruction::ASSIGN:
            return QString("Assign");
        case TypeOfInstruction::WHILE:
            return QString("While");
        case TypeOfInstruction::IF:
            return QString("If");
        case TypeOfInstruction::FOR:
            return QString("For");
        default:
            throw QString("Uknown Instruction");
    }
}
