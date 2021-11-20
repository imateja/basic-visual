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
        default:
            throw QString("Uknown Instruction");
    }
}
