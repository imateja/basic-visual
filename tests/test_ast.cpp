//#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ast.hpp>
#include <interpret.hpp>
#include <state.hpp>

TEST_CASE("ValueAST testing constructor with different values", "[class][constructor]")
{
    SECTION("Instance of ValueAST constructed with argument type 'double' will return that value when getValue() is called")
    {
            double input = 5.5;
            ValueAST value(input);
            double expected = 5.5;
            REQUIRE(value.getValue() == expected);

    }


    SECTION("Border case, Instance of ValueAST constructed with argument double max will return double max when getValue() is called")
    {
        ValueAST value(std::numeric_limits<double>::max());
        double expected = std::numeric_limits<double>::max();
        REQUIRE(value.getValue() == expected);

    }
    SECTION("Stringify method will for string of value that it is in instance of ValueAST"){
        ValueAST value(0);
        QString expected = "0";
        REQUIRE(value.stringify() == expected);
    }
    SECTION("Interpreting ValueAST should return the same value as ValueAST getValue()"){

        ValueAST *input = new ValueAST(6.25);
        double expectedResult = 6.25;
        Interpret *i = new Interpret(input);

        REQUIRE(i->getValue().toDouble() == 6.25);
    }
}

TEST_CASE("VariableAST", "[VariableAST][Constructor]")
{
    SECTION("Instance of VariableAST constructed with argument type 'string' will return that value when getName() is called")
    {
        QString input = "x";
        QString expected = "x";
        VariableAST variable(input);
        REQUIRE(variable.getName() == expected);
    }

    SECTION("Testing getName() method for empty string")
    {
        QString input = "";
        QString expected = "";
        VariableAST variable(input);
        REQUIRE(variable.getName() == expected);
    }

    SECTION("Testing Stringify metod for argument string should return exact string"){
        QString input = "string";
        QString expected = "string";
        VariableAST variable(input);
        REQUIRE(variable.stringify() == expected);
    }
    SECTION("Interpreting ValueAST should return the same value as ValueAST getValue()"){
        State::Domains().createNewDomain();

        VariableAST *input = new VariableAST(QString("x"));
        QVariant variableValue(6.25);
        State::Domains().assignValue(input->getName(),variableValue);
        double expectedResult = 6.25;
        Interpret *i = new Interpret(input);

        REQUIRE(i->getValue().toDouble() == 6.25);
    }
}

TEST_CASE("Testing PlaceholderAST constructor","[PlaceholderAST][constructor]")
{
    SECTION("For PlaceholderAST empty constructor expr_ should be nullptr")
    {
        PlaceholderAST placeholder = PlaceholderAST();
        REQUIRE(placeholder.expr_ == nullptr);
    }

    SECTION("For empty PlaceholderAST stringify method should return []")
    {
        QString expected = "[]";
        PlaceholderAST placeholder = PlaceholderAST();
        REQUIRE(placeholder.stringify() == expected);

    }

    SECTION("For not empty Placeholder stringfy method should return expr_ stringfy")
    {

    //TODO: Once AST is tested
    }
}

TEST_CASE("MulAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, MulAST will multiply them and Interpret will hold their product")
    {
        ValueAST *tmp1 = new ValueAST(5.0);
        ValueAST *tmp2 = new ValueAST(6.0);
        MulAST *input = new MulAST(tmp1,tmp2);
        double expectedResult = 30.0;
        auto result = Interpret(input).getValue().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, MulAST will multiply them and Interpret will hold their product")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        MulAST inputMul(input1,input2);

        double expectedResult = 30.0;
        auto result = Interpret(&inputMul).getValue().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, MulAST will multiply them and Interpret will hold their product")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        ValueAST *input2 = new ValueAST(5.0);
        QVariant variableValue(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        MulAST inputMul(input1,input2);

        double expectedResult = 30.0;
        auto result = Interpret(&inputMul).getValue().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("DivAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, DivAST will divide them and Interpret will hold their quotient")
    {
        ValueAST *tmp1 = new ValueAST(5.0);
        ValueAST *tmp2 = new ValueAST(6.0);
        DivAST *input = new DivAST(tmp1,tmp2);
        double expectedResult = 5.0/6.0;
        auto result = Interpret(input).getValue().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, DivAST will divide them and Interpret will hold their quotient")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        DivAST inputDiv(input1,input2);

        double expectedResult = 6.0/5.0;
        auto result = Interpret(&inputDiv).getValue().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, DivAST will divide them and Interpret will hold their quotient")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        ValueAST *input2 = new ValueAST(5.0);
        QVariant variableValue(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        DivAST inputDiv(input1,input2);

        double expectedResult = 6.0/5.0;
        auto result = Interpret(&inputDiv).getValue().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("AddAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, AddAST will add them and Interpret will hold their sum")
    {
        ValueAST *tmp1 = new ValueAST(5.0);
        ValueAST *tmp2 = new ValueAST(6.0);
        MulAST *input = new MulAST(tmp1,tmp2);
        double expectedResult = 30.0;
        auto result = Interpret(input).getValue().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, AddAST will add them and Interpret will hold their sum")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        AddAST inputAdd(input1,input2);

        double expectedResult = 6.0+5.0;
        auto result = Interpret(&inputAdd).getValue().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, AddAST will add them and Interpret will hold their sum")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        ValueAST *input2 = new ValueAST(5.0);
        QVariant variableValue(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        AddAST inputAdd(input1,input2);

        double expectedResult = 6.0+5.0;
        auto result = Interpret(&inputAdd).getValue().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("SubAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, SubAST will subtract them and Interpret will hold their difference")
    {
        ValueAST *tmp1 = new ValueAST(5.0);
        ValueAST *tmp2 = new ValueAST(6.0);
        SubAST *input = new SubAST(tmp1,tmp2);
        double expectedResult = 5.0-6.0;
        auto result = Interpret(input).getValue().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, SubAST will subtract them and Interpret will hold their difference")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        SubAST inputSub(input1,input2);

        double expectedResult = 6.0-5.0;
        auto result = Interpret(&inputSub).getValue().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, SubAST will subtract them and Interpret will hold their difference")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        ValueAST *input2 = new ValueAST(5.0);
        QVariant variableValue(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        SubAST inputSub(input1,input2);
        double expectedResult = 6.0-5.0;

        auto result = Interpret(&inputSub).getValue().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("LtAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, LtAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {
        ValueAST *tmp1 = new ValueAST(5.0);
        ValueAST *tmp2 = new ValueAST(6.0);
        LtAST *input = new LtAST(tmp1,tmp2);
        bool expectedResult = 5.0 < 6.0 ? true : false;

        auto result = Interpret(input).getValue().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, LtAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(5.0);
        QVariant variableValue2(6.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        LtAST inputLt(input1,input2);
        bool expectedResult = 5.0 < 6.0 ? true : false;

        auto result  = Interpret(&inputLt).getValue().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, LtAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        ValueAST *input2 = new ValueAST(6.0);
        QVariant variableValue(5.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        LtAST inputLt(input1,input2);
        bool expectedResult = 5.0 < 6.0 ? true : false;

        auto result = Interpret(&inputLt).getValue().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("GtAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, GtAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        GtAST *input = new GtAST(tmp1,tmp2);
        bool expectedResult = 6.0 > 5.0 ? true : false;

        auto result = Interpret(input).getValue().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, GtAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {   State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        GtAST inputGt(input1,input2);
        bool expectedResult = 6.0 > 5.0 ? true : false;

        auto result = Interpret(&inputGt).getValue().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, GtAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        QVariant variableValue(6.0);
        ValueAST *input2 = new ValueAST(5.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        GtAST inputGt(input1,input2);
        bool expectedResult = 6.0 > 5.0 ? true : false;

        auto result = Interpret(&inputGt).getValue().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("LeqAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, LegAST will compare them and Interpret will hold true if first is less or equal than second, false otherwise")
    {
        ValueAST *tmp1 = new ValueAST(5.0);
        ValueAST *tmp2 = new ValueAST(6.0);
        LeqAST *input = new LeqAST(tmp1,tmp2);
        bool expectedResult = 5.0 <= 6.0 ? true : false;

        auto result = Interpret(input).getValue().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, LegAST will compare them and Interpret will hold true if first is less or equal than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(5.0);
        QVariant variableValue2(6.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        LeqAST inputLeq(input1,input2);
        bool expectedResult = 5.0 <= 6.0 ? true : false;

        auto result = Interpret(&inputLeq).getValue().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, LeqAST will compare them and Interpret will hold true if first is less or equal than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        QVariant variableValue(5.0);
        ValueAST *input2 = new ValueAST(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        LeqAST inputLeq(input1,input2);

        bool expectedResult = 5.0 <= 6.0 ? true : false;
        auto result =Interpret(&inputLeq).getValue().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("GeqAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, GeqAST will compare them and Interpret will hold true if first is greater or equal than second, false otherwise")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        GeqAST *input = new GeqAST(tmp1,tmp2);
        bool expectedResult = 6.0 >= 5.0 ? true : false;

        auto result = Interpret(input).getValue().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, GeqAST will compare them and Interpret will hold true if first is greater or equal than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        GeqAST inputGeq(input1,input2);
        bool expectedResult = 6.0 >= 5.0 ? true : false;

        auto result  =Interpret(&inputGeq).getValue().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, GeqAST will compare them and Interpret will hold true if first is greater or equal than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        QVariant variableValue(6.0);
        ValueAST *input2 = new ValueAST(5.0);

        State::Domains().assignValue(input1->getName(),variableValue);
        GeqAST inputGeq(input1,input2);

        bool expectedResult = 6.0 >= 5.0 ? true : false;
        auto result = Interpret(&inputGeq).getValue().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("EqAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, EqAST will compare them and Interpret will hold true if first is equal to second, false otherwise")
    {
        ValueAST *tmp1 = new ValueAST(5.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        EqAST *input = new EqAST(tmp1,tmp2);
        bool expectedResult = 5.0 == 5.0 ? true : false;

        auto result = Interpret(input).getValue().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, EqAST will compare them and Interpret will hold true if first is equal to second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(5.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        EqAST inputEq(input1,input2);

        bool expectedResult = 5.0 == 5.0 ? true : false;
        auto result = Interpret(&inputEq).getValue().toBool();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, EqAST will compare them and Interpret will hold true if first is equal to second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        QVariant variableValue(5.0);
        ValueAST *input2 = new ValueAST(5.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        EqAST inputEq(input1,input2);
        bool expectedResult = 5.0 == 5.0 ? true : false;

        auto result = Interpret(&inputEq).getValue().toBool();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("NeqAST", "[class][ValueAST][VariableAST][State]")
{
    SECTION("For two type ValueAST operands, NeqAST will compare them and Interpret will hold true if first is not equal to second, false otherwise")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        NeqAST *input = new NeqAST(tmp1,tmp2);
        bool expectedResult = 6.0 != 5.0 ? true : false;

        auto result = Interpret(input).getValue().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableAST* operands, NeqAST will compare them and Interpret will hold true if first is not equal to second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        VariableAST *input2 = new VariableAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        NeqAST inputNeq(input1,input2);

        bool expectedResult = 6.0 != 5.0 ? true : false;
        auto result = Interpret(&inputNeq).getValue().toBool();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueAST* and one VariableAST* operands, NeqAST will compare them and Interpret will hold true if first is not equal to second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableAST *input1 = new VariableAST(QString("x"));
        QVariant variableValue(6.0);
        ValueAST *input2 = new ValueAST(5.0);

        State::Domains().assignValue(input1->getName(),variableValue);
        NeqAST inputNeq(input1,input2);

        bool expectedResult = 6.0 != 5.0 ? true : false;
        auto result = Interpret(&inputNeq).getValue().toBool();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("AndAST", "[class][ValueAST][VariableAST][State]"){
    SECTION("For two type AST that return bool values, AndAST will add them and Interpret will hold true if both values are true")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        ValueAST *tmp3 = new ValueAST(6.0);
        ValueAST *tmp4 = new ValueAST(5.0);
        NeqAST *input1 = new NeqAST(tmp1,tmp2);
        NeqAST *input2 = new NeqAST(tmp3,tmp4);
        bool expectedResult = true;

        AndAST inputAnd(input1,input2);
        auto result = Interpret(&inputAnd).getValue().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two type AST that return bool values, AndAST will add them and Interpret will hold false if one is true and other is false")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        ValueAST *tmp3 = new ValueAST(6.0);
        ValueAST *tmp4 = new ValueAST(5.0);
        EqAST *input1 = new EqAST(tmp1,tmp2);
        NeqAST *input2 = new NeqAST(tmp3,tmp4);
        bool expectedResult = false;

        AndAST inputAnd(input1,input2);
        auto resault = Interpret(&inputAnd).getValue().toBool();

        REQUIRE(resault == expectedResult);
    }

    SECTION("For two type AST that return bool values, AndAST will add them and Interpret will hold false if both are false")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        ValueAST *tmp3 = new ValueAST(6.0);
        ValueAST *tmp4 = new ValueAST(5.0);
        EqAST *input1 = new EqAST(tmp1,tmp2);
        EqAST *input2 = new EqAST(tmp3,tmp4);
        bool expectedResult = false;

        AndAST inputAnd(input1,input2);
        auto result = Interpret(&inputAnd).getValue().toBool();

        REQUIRE(result== expectedResult);
    }
}

TEST_CASE("OrAST", "[class][ValueAST][VariableAST][State]"){
    SECTION("For two type AST that return bool values, OrAST will or them and Interpret will hold true if both values are true")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        ValueAST *tmp3 = new ValueAST(6.0);
        ValueAST *tmp4 = new ValueAST(5.0);
        NeqAST *input1 = new NeqAST(tmp1,tmp2);
        NeqAST *input2 = new NeqAST(tmp3,tmp4);
        bool expectedResult = true;

        OrAST inputOr(input1,input2);
        auto result = Interpret(&inputOr).getValue().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two type AST that return bool values, OrAST will add them and Interpret will hold true if one is true and other is false")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        ValueAST *tmp3 = new ValueAST(6.0);
        ValueAST *tmp4 = new ValueAST(5.0);
        EqAST *input1 = new EqAST(tmp1,tmp2);
        NeqAST *input2 = new NeqAST(tmp3,tmp4);
        bool expectedResult = true;

        OrAST inputOr(input1,input2);
        auto result= Interpret(&inputOr).getValue().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two type AST that return bool values, OrAST will add them and Interpret will hold false if both are false")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        ValueAST *tmp3 = new ValueAST(6.0);
        ValueAST *tmp4 = new ValueAST(5.0);
        EqAST *input1 = new EqAST(tmp1,tmp2);
        EqAST *input2 = new EqAST(tmp3,tmp4);
        bool expectedResult = false;
        OrAST inputOr(input1,input2);
        auto result = Interpret(&inputOr).getValue().toBool();

        REQUIRE(result == expectedResult);
    }
    SECTION("For two type AST that return bool values, OrAST will or them and Interpret will hold true if first is true and other is false")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        ValueAST *tmp3 = new ValueAST(6.0);
        ValueAST *tmp4 = new ValueAST(5.0);
        NeqAST *input1 = new NeqAST(tmp1,tmp2);
        EqAST *input2 = new EqAST(tmp3,tmp4);
        bool expectedResult = true;

        OrAST inputOr(input1,input2);
       auto resault = Interpret(&inputOr).getValue().toBool();

        REQUIRE(resault == expectedResult);
    }
}

TEST_CASE("NotAST", "[class][ValueAST][VariableAST][State]"){
    SECTION("For type AST that return bool value, NotAST will not it and Interpret will hold true if value is false")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        NeqAST *input1 = new NeqAST(tmp1,tmp2);
        bool expectedResult = false;
        NotAST inputNot(input1);
        auto result = Interpret(&inputNot).getValue().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For type AST that return bool value, NotAST will  not it and Interpret will hold false if value is true")
    {
        ValueAST *tmp1 = new ValueAST(6.0);
        ValueAST *tmp2 = new ValueAST(5.0);
        EqAST *input1 = new EqAST(tmp1,tmp2);
        bool expectedResult = true;

        NotAST inputNot(input1);
        auto result = Interpret(&inputNot).getValue().toBool();

        REQUIRE(result == expectedResult);


    }

}

TEST_CASE("AssignAST", "[class][ValueAST][VariableAST][State]")
{

    SECTION("Interpreting a valid AssignAST created with a non-existing name and a ValueAST will result in creating a variable in scope")
    {
        State::Domains().createNewDomain();
        QString name = "testing";
        AssignAST * expr = new AssignAST(name, new ValueAST(10.0));
        double expectedResult = 10.0;

        Interpret i = Interpret{expr};
        VariableAST *var = new VariableAST(name);
        double result = Interpret{var}.getValue().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }


    SECTION("Interpreting a valid AssignAST created with an existing name and ValueAST will result in updating an existing variable in scope")
    {
        State::Domains().createNewDomain();
        QString name = "testing";
        AssignAST* expr = new AssignAST(name,new ValueAST(10.0));
        QVariant oldValue = QVariant(Interpret{expr}.getValue());

        State::Domains().assignValue(name,oldValue);
        QVariant newValue = QVariant(5.0);
        State::Domains().assignValue(name,newValue);
        double result = State::Domains().getValue(name).toDouble();

        double expectedResult = 5.0;

        REQUIRE(result == expectedResult);
        State::Domains().clear();

    }


    SECTION("Interpreting a valid AssignAST created with VariableAST will result in creating a variable in scope")
    {
        State::Domains().createNewDomain();
        QString newVarName = "testing";
        VariableAST* varExpr = new VariableAST(QString("oldVarName"));
        QVariant value = QVariant(10.0);
        State::Domains().assignValue(varExpr->getName(), value);
        double expectedResult = 10.0;

        double result = State::Domains().getValue(varExpr->getName()).toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();

    }
}
TEST_CASE("BlockAST", "[class][ValueAST]"){
    SECTION("Given empty BlockAST instance, insert will append an AST at the end of the collection")
    {
        QString name = "test";
        AssignAST* assign = new AssignAST(name,new ValueAST(10.0));
        BlockAST *block = new BlockAST();
        auto expected = assign;

        block->insert(assign);
        auto body = block->getBody();
        auto result = body[body.size()-1];

        REQUIRE(result == expected);



    }

    SECTION("Given BlockAST instance with more than one instruction, interpreting that block will result in empty QVariant");
    {
        QString name = "test";
        AssignAST* assign = new AssignAST(name,new ValueAST(10.0));
        BlockAST *block = new BlockAST();
        block->insert(assign);
        auto expected = QVariant();

        auto body = block->getBody();
        auto result = Interpret{block}.getValue();

        REQUIRE(result == expected);


    }

    SECTION("Given BlockAST instance with more than one instruction, interpreting that block will result in empty QVariant");
    {
        State::Domains().createNewDomain();
        QString name = "test";
        AssignAST* assign = new AssignAST(name,new VariableAST(QString("s")));
        BlockAST *block = new BlockAST();
        block->insert(assign);
        auto expected = QVariant();

        auto body = block->getBody();
        auto result = Interpret{block}.getValue();

        REQUIRE_FALSE(result == expected);

        State::Domains().clear();


    }

}
