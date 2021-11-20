#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <QString>

class Instruction
{
public:
    //Add al the classes we need here although since every instruction will be the subclass of class instruction this implementation should be fixed
    //we should check not Enum but if the instruction we are drawing is the instance of which class, this is just to check if something like this works;
    //FIX
    enum class TypeOfInstruction{
        ASSIGN
    };

    Instruction(QString instructionText, TypeOfInstruction type);

    inline QString getInstructionText() const
    {
        return _instructionText;
    }

    inline TypeOfInstruction getInstructionType() const
    {
        return _typeOfInstruction;
    }

    QString TypeOfInstructionToString();
private:
    QString _instructionText;
    TypeOfInstruction _typeOfInstruction;
};

#endif // INSTRUCTION_H
