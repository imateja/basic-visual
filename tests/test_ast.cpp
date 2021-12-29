#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "inc/ast.h"
#include "inc/interpret.h"
#include "inc/state.h"

/* TODO: double comparison */
TEST_CASE("ValueExprAST", "[class]")
{
    SECTION("Instance of ValueExprAST constructed with argument type 'double' will return that value when getValue() is called")
    {
        ValueExprAST input{5.24};
        double expectedOutput = 5.24;

        double output = input.getValue();

        REQUIRE(output == expectedOutput);
    }

    SECTION("Deep copy of ValueExprAST instance will have different address compared to the original")
    {
        ValueExprAST* expr1 = new ValueExprAST(5.24);

        ValueExprAST* expr2 = static_cast<ValueExprAST*>(expr1->copy());

        REQUIRE_FALSE(expr1 == expr2);
    }

    SECTION("Interpreting a ValueExprAST instance will result in getting the value stored in that instance")
    {
        Interpret i;
        ValueExprAST* expr = new ValueExprAST(4.4);
        double expectedResult = 4.4;

        i.VisitValueExprAST(*expr);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }
}

TEST_CASE("VariableExprAST", "[class][State]")
{
    SECTION("Instance of VariableExprAST constructed with argument type 'string' will return that value when getValue() is called")
    {
        VariableExprAST input{"testing"};
        QString expectedOutput = "testing";

        QString output = input.getName();

        REQUIRE(output == expectedOutput);
    }

   SECTION("Deep copy of VariableExprAST instance will have different address compared to the original")
   {
        VariableExprAST* expr1 = new VariableExprAST("testing");

        VariableExprAST* expr2 = static_cast<VariableExprAST*>(expr1->copy());

        REQUIRE_FALSE(expr1 == expr2);
   }

    SECTION("Interpreting a VariableExprAST instance will result in getting the value stored by that name if that variable exists in scope")
    {
        Interpret i;
        VariableExprAST* variable = new VariableExprAST("testing");
        ValueExprAST* value = new ValueExprAST(4.4);
        State::Domains().assignValue(variable->getName(), value);
        double expectedResult = 4.4;

        i.VisitVariableExprAST(*variable);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }

    /*  TODO: error handling in State class

    SECTION("Interpreting VariableExprAST instance will result in getting nullptr if that variable does not exist in scope")
    {
        Interpret i;
        VariableExprAST* variable = new VariableExprAST("testing");

        REQUIRE_THROWS(i.VisitVariableExprAST(*variable));
    }
    */
}

TEST_CASE("AddExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two ValueExprAST* operands, AddExprAST will add them and Interpret will hold their sum")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(4.4);
        ValueExprAST* expr2 = new ValueExprAST(5.6);
        AddExprAST* result = new AddExprAST(expr1, expr2);
        double expectedResult = 10.0;

        i.VisitAddExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, AddExprAST will add them and Interpret will hold their sum")
    {
        Interpret i;
        VariableExprAST* expr1 = new VariableExprAST("first");
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr1->getName(), new ValueExprAST(4.4));
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(5.6));
        AddExprAST* result = new AddExprAST(expr1, expr2);
        double expectedResult = 10.0;

        i.VisitAddExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, AddExprAST will add them and Interpret will hold their sum")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(4.4);
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(5.6));
        AddExprAST* result = new AddExprAST(expr1, expr2);
        double expectedResult = 10.0;

        i.VisitAddExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }
}

TEST_CASE("SubExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two ValueExprAST* operands, SubExprAST will subtract them and Interpret will hold their difference")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(7.7);
        ValueExprAST* expr2 = new ValueExprAST(5.5);
        SubExprAST* result = new SubExprAST(expr1, expr2);
        double expectedResult = 2.2;

        i.VisitSubExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, SubExprAST will substract them and Interpret will hold their difference")
    {
        Interpret i;
        VariableExprAST* expr1 = new VariableExprAST("first");
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr1->getName(), new ValueExprAST(7.7));
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(5.5));
        SubExprAST* result = new SubExprAST(expr1, expr2);
        double expectedResult = 2.2;

        i.VisitSubExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, SubExprAST will substract them and Interpret will hold their difference")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(7.7);
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(5.5));
        SubExprAST* result = new SubExprAST(expr1, expr2);
        double expectedResult = 2.2;

        i.VisitSubExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }
}

TEST_CASE("MulExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, MulExprAST will multiply them and Interpret will hold their product")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(2.5);
        ValueExprAST* expr2 = new ValueExprAST(2.5);
        MulExprAST* result = new MulExprAST(expr1, expr2);
        double expectedResult = 6.25;

        i.VisitMulExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, MulExprAST will multiply them and Interpret will hold their product")
    {
        Interpret i;
        VariableExprAST* expr1 = new VariableExprAST("first");
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr1->getName(), new ValueExprAST(2.5));
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(2.5));
        MulExprAST* result = new MulExprAST(expr1, expr2);
        double expectedResult = 6.25;

        i.VisitMulExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, MulExprAST will multiply them and Interpret will hold their product")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(2.5);
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(2.5));
        MulExprAST* result = new MulExprAST(expr1, expr2);
        double expectedResult = 6.25;

        i.VisitMulExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }
}

TEST_CASE("DivExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, DivExprAST will divide them and Interpret will hold their quotient")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(6.7);
        ValueExprAST* expr2 = new ValueExprAST(3.2);
        DivExprAST* result = new DivExprAST(expr1, expr2);
        double expectedResult = 2.09375;

        i.VisitDivExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, DivExprAST will divide them and Interpret will hold their quotient")
    {
        Interpret i;
        VariableExprAST* expr1 = new VariableExprAST("first");
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr1->getName(), new ValueExprAST(6.7));
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(3.2));
        DivExprAST* result = new DivExprAST(expr1, expr2);
        double expectedResult = 2.09375;

        i.VisitDivExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, DivExprAST will divide them and Interpret will hold their quotient")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(6.7);
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(3.2));
        DivExprAST* result = new DivExprAST(expr1, expr2);
        double expectedResult = 2.09375;

        i.VisitDivExprAST(*result);

        REQUIRE(static_cast<double>(i) == expectedResult);
    }
}

TEST_CASE("LtExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, LtExprAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(3.2);
        ValueExprAST* expr2 = new ValueExprAST(3.3);
        LtExprAST* result = new LtExprAST(expr1, expr2);
        bool expectedResult = true;

        i.VisitLtExprAST(*result);

        REQUIRE(static_cast<bool>(i) == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, LtExprAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {
        Interpret i;
        VariableExprAST* expr1 = new VariableExprAST("first");
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr1->getName(), new ValueExprAST(3.2));
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(3.3));
        LtExprAST* result = new LtExprAST(expr1, expr2);
        bool expectedResult = true;

        i.VisitLtExprAST(*result);

        REQUIRE(static_cast<bool>(i) == expectedResult);
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, LtExprAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(3.2);
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(3.3));
        LtExprAST* result = new LtExprAST(expr1, expr2);
        bool expectedResult = true;

        i.VisitLtExprAST(*result);

        REQUIRE(static_cast<bool>(i) == expectedResult);
    }
}

TEST_CASE("GtExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, GtExprAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(7.7);
        ValueExprAST* expr2 = new ValueExprAST(5.5);
        GtExprAST* result = new GtExprAST(expr1, expr2);
        bool expectedResult = true;

        i.VisitGtExprAST(*result);

        REQUIRE(static_cast<bool>(i) == expectedResult);
    }

    SECTION("For two VariableExprAST* operands, GtExprAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {
        Interpret i;
        VariableExprAST* expr1 = new VariableExprAST("first");
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr1->getName(), new ValueExprAST(7.7));
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(5.5));
        GtExprAST* result = new GtExprAST(expr1, expr2);
        bool expectedResult = true;

        i.VisitGtExprAST(*result);

        REQUIRE(static_cast<bool>(i) == expectedResult);
    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, GtExprAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(7.7);
        VariableExprAST* expr2 = new VariableExprAST("second");
        State::Domains().assignValue(expr2->getName(), new ValueExprAST(5.5));
        GtExprAST* result = new GtExprAST(expr1, expr2);
        bool expectedResult = true;

        i.VisitGtExprAST(*result);

        REQUIRE(static_cast<bool>(i) == expectedResult);
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
        ValueExprAST* expr1 = new ValueExprAST(5.0);
        QVector<ExprAST*> emptyVector;
        BlockExprAST outputBlock(emptyVector);

        outputBlock.push_back(expr1);

        REQUIRE(outputBlock.size() == 1);
    }

    SECTION("Given BlockExprAST instance, insert will insert an ExprAST at the specified position in the collection")
    {
        ValueExprAST* expr1 = new ValueExprAST(5.0);
        ValueExprAST* expr2 = new ValueExprAST(6.4);
        ValueExprAST* expr3 = new ValueExprAST(18.7);
        ValueExprAST* expr4 = new ValueExprAST(7.0);
        QVector<ExprAST*> Vector{expr1, expr2, expr3};
        BlockExprAST outputBlock(Vector);

        outputBlock.insert(expr4, 0);

        REQUIRE(outputBlock.at(0) == expr4);
        REQUIRE(outputBlock.at(1) == expr1);
        REQUIRE(outputBlock.at(2) == expr2);
        REQUIRE(outputBlock.at(3) == expr3);
    }

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
