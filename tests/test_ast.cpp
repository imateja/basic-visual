//#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ast.hpp>
#include <interpret.hpp>
#include <state.hpp>

TEST_CASE("ValueExprAST testing constructor with different values", "[class][constructor]")
{
    SECTION("Instance of ValueExprAST constructed with argument type 'double' will return that value when getValue() is called")
    {
            double input = 5.5;
            ValueExprAST value(input);
            double expected = 5.5;
            REQUIRE(value.getValue() == expected);

    }


    SECTION("Border case, Instance of ValueExprAST constructed with argument double max will return double max when getValue() is called")
    {
        ValueExprAST value(std::numeric_limits<double>::max());
        double expected = std::numeric_limits<double>::max();
        REQUIRE(value.getValue() == expected);

    }
    SECTION("Stringify method will for string of value that it is in instance of ValueExprAST"){
        ValueExprAST value(0);
        QString expected = "0";
        REQUIRE(value.stringify() == expected);
    }
    SECTION("Interpreting ValueExprAST should return the same value as ValueExprAST getValue()"){

        ValueExprAST *input = new ValueExprAST(6.25);
        double expectedResult = 6.25;
        Interpret *i = new Interpret(input);

        REQUIRE(i->getValueTest().toDouble() == 6.25);
    }
}

TEST_CASE("VariableExprAST", "[VariableExprAST][Constructor]")
{
    SECTION("Instance of VariableExprAST constructed with argument type 'string' will return that value when getName() is called")
    {
        QString input = "x";
        QString expected = "x";
        VariableExprAST variable(input);
        REQUIRE(variable.getName() == expected);
    }

    SECTION("Testing getName() method for empty string")
    {
        QString input = "";
        QString expected = "";
        VariableExprAST variable(input);
        REQUIRE(variable.getName() == expected);
    }

    SECTION("Testing Stringify metod for argument string should return exact string"){
        QString input = "string";
        QString expected = "string";
        VariableExprAST variable(input);
        REQUIRE(variable.stringify() == expected);
    }
    SECTION("Interpreting ValueExprAST should return the same value as ValueExprAST getValue()"){
        State::Domains().createNewDomain();

        VariableExprAST *input = new VariableExprAST(QString("x"));
        QVariant variableValue(6.25);
        State::Domains().assignValue(input->getName(),variableValue);
        double expectedResult = 6.25;
        Interpret *i = new Interpret(input);

        REQUIRE(i->getValueTest().toDouble() == 6.25);
    }
}

TEST_CASE("Testing PlaceholderExprAST constructor","[PlaceholderExprAST][constructor]")
{
    SECTION("For PlaceholderExprAST empty constructor expr_ should be nullptr")
    {
        PlaceholderExprAST placeholder = PlaceholderExprAST();
        REQUIRE(placeholder.expr_ == nullptr);
    }

    SECTION("For empty PlaceholderExprAST stringify method should return []")
    {
        QString expected = "[]";
        PlaceholderExprAST placeholder = PlaceholderExprAST();
        REQUIRE(placeholder.stringify() == expected);

    }

    SECTION("For not empty Placeholder stringfy method should return expr_ stringfy")
    {

    //TODO: Once ExprAST is tested
    }
}

TEST_CASE("MulExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, MulExprAST will multiply them and Interpret will hold their product")
    {
        ValueExprAST *tmp1 = new ValueExprAST(5.0);
        ValueExprAST *tmp2 = new ValueExprAST(6.0);
        MulExprAST *input = new MulExprAST(tmp1,tmp2);
        double expectedResult = 30.0;
        auto result = Interpret(input).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, MulExprAST will multiply them and Interpret will hold their product")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        MulExprAST inputMul(input1,input2);

        double expectedResult = 30.0;
        auto result = Interpret(&inputMul).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, MulExprAST will multiply them and Interpret will hold their product")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        ValueExprAST *input2 = new ValueExprAST(5.0);
        QVariant variableValue(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        MulExprAST inputMul(input1,input2);

        double expectedResult = 30.0;
        auto result = Interpret(&inputMul).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("DivExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, DivExprAST will divide them and Interpret will hold their quotient")
    {
        ValueExprAST *tmp1 = new ValueExprAST(5.0);
        ValueExprAST *tmp2 = new ValueExprAST(6.0);
        DivExprAST *input = new DivExprAST(tmp1,tmp2);
        double expectedResult = 5.0/6.0;
        auto result = Interpret(input).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, DivExprAST will divide them and Interpret will hold their quotient")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        DivExprAST inputDiv(input1,input2);

        double expectedResult = 6.0/5.0;
        auto result = Interpret(&inputDiv).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, DivExprAST will divide them and Interpret will hold their quotient")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        ValueExprAST *input2 = new ValueExprAST(5.0);
        QVariant variableValue(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        DivExprAST inputDiv(input1,input2);

        double expectedResult = 6.0/5.0;
        auto result = Interpret(&inputDiv).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("AddExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, AddExprAST will add them and Interpret will hold their sum")
    {
        ValueExprAST *tmp1 = new ValueExprAST(5.0);
        ValueExprAST *tmp2 = new ValueExprAST(6.0);
        MulExprAST *input = new MulExprAST(tmp1,tmp2);
        double expectedResult = 30.0;
        auto result = Interpret(input).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, AddExprAST will add them and Interpret will hold their sum")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        AddExprAST inputAdd(input1,input2);

        double expectedResult = 6.0+5.0;
        auto result = Interpret(&inputAdd).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, AddExprAST will add them and Interpret will hold their sum")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        ValueExprAST *input2 = new ValueExprAST(5.0);
        QVariant variableValue(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        AddExprAST inputAdd(input1,input2);

        double expectedResult = 6.0+5.0;
        auto result = Interpret(&inputAdd).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("SubExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, SubExprAST will subtract them and Interpret will hold their difference")
    {
        ValueExprAST *tmp1 = new ValueExprAST(5.0);
        ValueExprAST *tmp2 = new ValueExprAST(6.0);
        SubExprAST *input = new SubExprAST(tmp1,tmp2);
        double expectedResult = 5.0-6.0;
        auto result = Interpret(input).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, SubExprAST will subtract them and Interpret will hold their difference")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        SubExprAST inputSub(input1,input2);

        double expectedResult = 6.0-5.0;
        auto result = Interpret(&inputSub).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, SubExprAST will subtract them and Interpret will hold their difference")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        ValueExprAST *input2 = new ValueExprAST(5.0);
        QVariant variableValue(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        SubExprAST inputSub(input1,input2);
        double expectedResult = 6.0-5.0;

        auto result = Interpret(&inputSub).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("LtExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, LtExprAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {
        ValueExprAST *tmp1 = new ValueExprAST(5.0);
        ValueExprAST *tmp2 = new ValueExprAST(6.0);
        LtExprAST *input = new LtExprAST(tmp1,tmp2);
        bool expectedResult = 5.0 < 6.0 ? true : false;

        auto result = Interpret(input).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, LtExprAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(5.0);
        QVariant variableValue2(6.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        LtExprAST inputLt(input1,input2);
        bool expectedResult = 5.0 < 6.0 ? true : false;

        auto result  = Interpret(&inputLt).getValueTest().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, LtExprAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        ValueExprAST *input2 = new ValueExprAST(6.0);
        QVariant variableValue(5.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        LtExprAST inputLt(input1,input2);
        bool expectedResult = 5.0 < 6.0 ? true : false;

        auto result = Interpret(&inputLt).getValueTest().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("GtExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, GtExprAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        GtExprAST *input = new GtExprAST(tmp1,tmp2);
        bool expectedResult = 6.0 > 5.0 ? true : false;

        auto result = Interpret(input).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, GtExprAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {   State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        GtExprAST inputGt(input1,input2);
        bool expectedResult = 6.0 > 5.0 ? true : false;

        auto result = Interpret(&inputGt).getValueTest().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, GtExprAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        QVariant variableValue(6.0);
        ValueExprAST *input2 = new ValueExprAST(5.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        GtExprAST inputGt(input1,input2);
        bool expectedResult = 6.0 > 5.0 ? true : false;

        auto result = Interpret(&inputGt).getValueTest().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("LeqExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, LegExprAST will compare them and Interpret will hold true if first is less or equal than second, false otherwise")
    {
        ValueExprAST *tmp1 = new ValueExprAST(5.0);
        ValueExprAST *tmp2 = new ValueExprAST(6.0);
        LeqExprAST *input = new LeqExprAST(tmp1,tmp2);
        bool expectedResult = 5.0 <= 6.0 ? true : false;

        auto result = Interpret(input).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, LegExprAST will compare them and Interpret will hold true if first is less or equal than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(5.0);
        QVariant variableValue2(6.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        LeqExprAST inputLeq(input1,input2);
        bool expectedResult = 5.0 <= 6.0 ? true : false;

        auto result = Interpret(&inputLeq).getValueTest().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, LeqExprAST will compare them and Interpret will hold true if first is less or equal than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        QVariant variableValue(5.0);
        ValueExprAST *input2 = new ValueExprAST(6.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        LeqExprAST inputLeq(input1,input2);

        bool expectedResult = 5.0 <= 6.0 ? true : false;
        auto result =Interpret(&inputLeq).getValueTest().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("GeqExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, GeqExprAST will compare them and Interpret will hold true if first is greater or equal than second, false otherwise")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        GeqExprAST *input = new GeqExprAST(tmp1,tmp2);
        bool expectedResult = 6.0 >= 5.0 ? true : false;

        auto result = Interpret(input).getValueTest().toDouble();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, GeqExprAST will compare them and Interpret will hold true if first is greater or equal than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        GeqExprAST inputGeq(input1,input2);
        bool expectedResult = 6.0 >= 5.0 ? true : false;

        auto result  =Interpret(&inputGeq).getValueTest().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, GeqExprAST will compare them and Interpret will hold true if first is greater or equal than second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        QVariant variableValue(6.0);
        ValueExprAST *input2 = new ValueExprAST(5.0);

        State::Domains().assignValue(input1->getName(),variableValue);
        GeqExprAST inputGeq(input1,input2);

        bool expectedResult = 6.0 >= 5.0 ? true : false;
        auto result = Interpret(&inputGeq).getValueTest().toDouble();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("EqExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, EqExprAST will compare them and Interpret will hold true if first is equal to second, false otherwise")
    {
        ValueExprAST *tmp1 = new ValueExprAST(5.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        EqExprAST *input = new EqExprAST(tmp1,tmp2);
        bool expectedResult = 5.0 == 5.0 ? true : false;

        auto result = Interpret(input).getValueTest().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, EqExprAST will compare them and Interpret will hold true if first is equal to second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(5.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        EqExprAST inputEq(input1,input2);

        bool expectedResult = 5.0 == 5.0 ? true : false;
        auto result = Interpret(&inputEq).getValueTest().toBool();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, EqExprAST will compare them and Interpret will hold true if first is equal to second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        QVariant variableValue(5.0);
        ValueExprAST *input2 = new ValueExprAST(5.0);
        State::Domains().assignValue(input1->getName(),variableValue);
        EqExprAST inputEq(input1,input2);
        bool expectedResult = 5.0 == 5.0 ? true : false;

        auto result = Interpret(&inputEq).getValueTest().toBool();

        REQUIRE(result == expectedResult);

        State::Domains().clear();
    }
}

TEST_CASE("NeqExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, NeqExprAST will compare them and Interpret will hold true if first is not equal to second, false otherwise")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        NeqExprAST *input = new NeqExprAST(tmp1,tmp2);
        bool expectedResult = 6.0 != 5.0 ? true : false;

        auto result = Interpret(input).getValueTest().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, NeqExprAST will compare them and Interpret will hold true if first is not equal to second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        VariableExprAST *input2 = new VariableExprAST(QString("y"));
        QVariant variableValue1(6.0);
        QVariant variableValue2(5.0);
        State::Domains().assignValue(input1->getName(),variableValue1);
        State::Domains().assignValue(input2->getName(),variableValue2);
        NeqExprAST inputNeq(input1,input2);

        bool expectedResult = 6.0 != 5.0 ? true : false;
        auto result = Interpret(&inputNeq).getValueTest().toBool();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, NeqExprAST will compare them and Interpret will hold true if first is not equal to second, false otherwise")
    {
        State::Domains().createNewDomain();
        VariableExprAST *input1 = new VariableExprAST(QString("x"));
        QVariant variableValue(6.0);
        ValueExprAST *input2 = new ValueExprAST(5.0);

        State::Domains().assignValue(input1->getName(),variableValue);
        NeqExprAST inputNeq(input1,input2);

        bool expectedResult = 6.0 != 5.0 ? true : false;
        auto result = Interpret(&inputNeq).getValueTest().toBool();

        REQUIRE(result == expectedResult);
        State::Domains().clear();
    }
}

TEST_CASE("AndExprAST", "[class][ValueExprAST][VariableExprAST][State]"){
    SECTION("For two type ExprAST that return bool values, AndExprAST will add them and Interpret will hold true if both values are true")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        ValueExprAST *tmp3 = new ValueExprAST(6.0);
        ValueExprAST *tmp4 = new ValueExprAST(5.0);
        NeqExprAST *input1 = new NeqExprAST(tmp1,tmp2);
        NeqExprAST *input2 = new NeqExprAST(tmp3,tmp4);
        bool expectedResult = true;

        AndExprAST inputAnd(input1,input2);
        auto result = Interpret(&inputAnd).getValueTest().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two type ExprAST that return bool values, AndExprAST will add them and Interpret will hold false if one is true and other is false")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        ValueExprAST *tmp3 = new ValueExprAST(6.0);
        ValueExprAST *tmp4 = new ValueExprAST(5.0);
        EqExprAST *input1 = new EqExprAST(tmp1,tmp2);
        NeqExprAST *input2 = new NeqExprAST(tmp3,tmp4);
        bool expectedResult = false;

        AndExprAST inputAnd(input1,input2);
        auto resault = Interpret(&inputAnd).getValueTest().toBool();

        REQUIRE(resault == expectedResult);
    }

    SECTION("For two type ExprAST that return bool values, AndExprAST will add them and Interpret will hold false if both are false")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        ValueExprAST *tmp3 = new ValueExprAST(6.0);
        ValueExprAST *tmp4 = new ValueExprAST(5.0);
        EqExprAST *input1 = new EqExprAST(tmp1,tmp2);
        EqExprAST *input2 = new EqExprAST(tmp3,tmp4);
        bool expectedResult = false;

        AndExprAST inputAnd(input1,input2);
        auto result = Interpret(&inputAnd).getValueTest().toBool();

        REQUIRE(result== expectedResult);
    }
}

TEST_CASE("OrExprAST", "[class][ValueExprAST][VariableExprAST][State]"){
    SECTION("For two type ExprAST that return bool values, OrExprAST will or them and Interpret will hold true if both values are true")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        ValueExprAST *tmp3 = new ValueExprAST(6.0);
        ValueExprAST *tmp4 = new ValueExprAST(5.0);
        NeqExprAST *input1 = new NeqExprAST(tmp1,tmp2);
        NeqExprAST *input2 = new NeqExprAST(tmp3,tmp4);
        bool expectedResult = true;

        OrExprAST inputOr(input1,input2);
        auto result = Interpret(&inputOr).getValueTest().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two type ExprAST that return bool values, OrExprAST will add them and Interpret will hold true if one is true and other is false")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        ValueExprAST *tmp3 = new ValueExprAST(6.0);
        ValueExprAST *tmp4 = new ValueExprAST(5.0);
        EqExprAST *input1 = new EqExprAST(tmp1,tmp2);
        NeqExprAST *input2 = new NeqExprAST(tmp3,tmp4);
        bool expectedResult = true;

        OrExprAST inputOr(input1,input2);
        auto result= Interpret(&inputOr).getValueTest().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For two type ExprAST that return bool values, OrExprAST will add them and Interpret will hold false if both are false")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        ValueExprAST *tmp3 = new ValueExprAST(6.0);
        ValueExprAST *tmp4 = new ValueExprAST(5.0);
        EqExprAST *input1 = new EqExprAST(tmp1,tmp2);
        EqExprAST *input2 = new EqExprAST(tmp3,tmp4);
        bool expectedResult = false;
        OrExprAST inputOr(input1,input2);
        auto result = Interpret(&inputOr).getValueTest().toBool();

        REQUIRE(result == expectedResult);
    }
    SECTION("For two type ExprAST that return bool values, OrExprAST will or them and Interpret will hold true if first is true and other is false")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        ValueExprAST *tmp3 = new ValueExprAST(6.0);
        ValueExprAST *tmp4 = new ValueExprAST(5.0);
        NeqExprAST *input1 = new NeqExprAST(tmp1,tmp2);
        EqExprAST *input2 = new EqExprAST(tmp3,tmp4);
        bool expectedResult = true;

        OrExprAST inputOr(input1,input2);
       auto resault = Interpret(&inputOr).getValueTest().toBool();

        REQUIRE(resault == expectedResult);
    }
}

TEST_CASE("NotExprAST", "[class][ValueExprAST][VariableExprAST][State]"){
    SECTION("For type ExprAST that return bool value, NotExprAST will not it and Interpret will hold true if value is false")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        NeqExprAST *input1 = new NeqExprAST(tmp1,tmp2);
        bool expectedResult = false;
        NotExprAST inputNot(input1);
        auto result = Interpret(&inputNot).getValueTest().toBool();

        REQUIRE(result == expectedResult);
    }

    SECTION("For type ExprAST that return bool value, NotExprAST will  not it and Interpret will hold false if value is true")
    {
        ValueExprAST *tmp1 = new ValueExprAST(6.0);
        ValueExprAST *tmp2 = new ValueExprAST(5.0);
        EqExprAST *input1 = new EqExprAST(tmp1,tmp2);
        bool expectedResult = true;

        NotExprAST inputNot(input1);
        auto result = Interpret(&inputNot).getValueTest().toBool();

        REQUIRE(result == expectedResult);


    }

}

TEST_CASE("AssignExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    /* FIX: DOUBLE FREE */
    /*
    SECTION("Interpreting a valid AssignExprAST created with a non-existing name and a ValueExprAST will result in creating a variable in scope")
    {
        QString name = "testing";
        AssignExprAST expr {name, new ValueExprAST(10.0)};
        double expectedResult = 10.0;

        Interpret {&expr};
        double result = static_cast<double>(Interpret {State::Domains().getValue(name)});

        REQUIRE(result == expectedResult);
    }
    */


    /* FIX: DOUBLE FREE */
    /*
    SECTION("Interpreting a valid AssignExprAST created with an existing name and ValueExprAST will result in updating an existing variable in scope")
    {
        QString oldName = "testing";
        State::Domains().assignValue(oldName, new ValueExprAST(5.0));
        AssignExprAST expr {oldName, new ValueExprAST(10.0)};
        double expectedResult = 10.0;

        Interpret {&expr};
        double result = static_cast<double>(Interpret {State::Domains().getValue(oldName)});

        REQUIRE(result == expectedResult);
    }
    */


    /* TODO:
       idea: Implement getValue() method in VariableExprAST class
       The method would try and get ValueExprAST linked with the name_ from State object

       Then fix visitVariableExprAST:
       State::Domains().assignValue(obj.getName(), obj.getExpr()->getValue());
    */

    /*
    SECTION("Interpreting a valid AssignExprAST created with VariableExprAST will result in creating a variable in scope")
    {
        QString newVarName = "testing";
        VariableExprAST* varExpr = new VariableExprAST("oldVarName");
        State::Domains().assignValue(varExpr->getName(), new ValueExprAST(10.0));
        AssignExprAST assignExpr {newVarName, varExpr};
        double expectedResult = 10.0;

        Interpret {&assignExpr};
        double result = static_cast<double>(Interpret {State::Domains().getValue(newVarName)});

        REQUIRE(result == expectedResult);
    }
    */
}

TEST_CASE("BlockExprAST", "[class][ValueExprAST]"){
    SECTION("Given empty BlockExprAST instance, push_back will append an ExprAST at the end of the collection")
    {

    }

    SECTION("Given BlockExprAST instance, insert will insert an ExprAST at the specified position in the collection")
    {



    /* TODO
    SECTION("Given BlockExprAST instance with one AssignExprAST inside, interpreting that block will result in creating of variable in scope")
    {

    }
    */


    /* TODO
    SECTION("Given BlockExprAST instance with more than one instruction, interpreting that block will result in completing every instruction inside")
    {

    }
    */
}
}
