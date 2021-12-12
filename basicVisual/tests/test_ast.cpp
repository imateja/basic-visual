#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "inc/ast.h"
#include "inc/interpret.h"

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
}

TEST_CASE("AddExprAST", "[class][ValueExprAST]")
{
    SECTION("For two type 'double' values, AddExprAST will add them and Interpret will return their sum")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(4.4);
        ValueExprAST* expr2 = new ValueExprAST(5.6);
        AddExprAST* result = new AddExprAST(expr1, expr2);
        double expectedResult = 10.0;

        i.VisitAddExprAST(*result);

        REQUIRE((double)i == expectedResult);
    }
}

TEST_CASE("SubExprAST", "[class][ValueExprAST]")
{
    SECTION("For two type 'double' values, SubExprAST will subtract them and Interpret will return their difference")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(7.7);
        ValueExprAST* expr2 = new ValueExprAST(5.5);
        SubExprAST* result = new SubExprAST(expr1, expr2);
        double expectedResult = 2.2;

        i.VisitSubExprAST(*result);

        REQUIRE((double)i == expectedResult);
    }
}

TEST_CASE("MulExprAST", "[class][ValueExprAST]")
{
    SECTION("For two type 'double' values, MulExprAST will multiply them and Interpret will return their product")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(2.5);
        ValueExprAST* expr2 = new ValueExprAST(2.5);
        MulExprAST* result = new MulExprAST(expr1, expr2);
        double expectedResult = 6.25;

        i.VisitMulExprAST(*result);

        REQUIRE((double)i == expectedResult);
    }
}

TEST_CASE("DivExprAST", "[class][ValueExprAST]")
{
    SECTION("For two type 'double' values, DivExprAST will divide them and Interpret will return their quotient")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(6.7);
        ValueExprAST* expr2 = new ValueExprAST(3.2);
        DivExprAST* result = new DivExprAST(expr1, expr2);
        double expectedResult = 2.09375;

        i.VisitDivExprAST(*result);

        REQUIRE((double)i == expectedResult);
    }
}

TEST_CASE("LtExprAST", "[class][ValueExprAST]")
{
    SECTION("For two type 'double' values, LtExprAST will compare them and Interpret will return true if first is lower than second")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(3.2);
        ValueExprAST* expr2 = new ValueExprAST(3.3);
        LtExprAST* result = new LtExprAST(expr1, expr2);
        double expectedResult = 2.2;

        i.VisitLtExprAST(*result);

        REQUIRE((bool)i);
    }
}

TEST_CASE("GtExprAST", "[class][ValueExprAST]")
{
    SECTION("For two type 'double' values, GtExprAST will compare them and Interpret will return true if first is greater than second")
    {
        Interpret i;
        ValueExprAST* expr1 = new ValueExprAST(7.7);
        ValueExprAST* expr2 = new ValueExprAST(5.5);
        GtExprAST* result = new GtExprAST(expr1, expr2);
        double expectedResult = 2.2;

        i.VisitGtExprAST(*result);

        REQUIRE((bool)i);
    }
}

TEST_CASE("BlockExprAST", "[class][ValueExprAST]")
{
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
    }
}
