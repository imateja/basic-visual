//#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ast.hpp>
#include <interpret.hpp>
#include <state.hpp>


//Jovan START

/* TODO: double comparison */
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

TEST_CASE("Testing Interpret" "[ExprAST][Constructors]")
{
    SECTION("MulExprAST empty constructor should construct two empty Placeholders")
    {
        QString expectedLeft = "[]";
        QString expectedRight = "[]";
        MulExprAST mul = MulExprAST();


    }

    SECTION("For two VariableExprAST* operands, SubExprAST will substract them and Interpret will hold their difference")
    {

    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, SubExprAST will substract them and Interpret will hold their difference")
    {

    }
}

TEST_CASE("MulExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, MulExprAST will multiply them and Interpret will hold their product")
    {

    }

    SECTION("For two VariableExprAST* operands, MulExprAST will multiply them and Interpret will hold their product")
    {

    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, MulExprAST will multiply them and Interpret will hold their product")
    {

    }
}

TEST_CASE("DivExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, DivExprAST will divide them and Interpret will hold their quotient")
    {

    }

    SECTION("For two VariableExprAST* operands, DivExprAST will divide them and Interpret will hold their quotient")
    {

    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, DivExprAST will divide them and Interpret will hold their quotient")
    {

    }
}

TEST_CASE("LtExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, LtExprAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {

    }

    SECTION("For two VariableExprAST* operands, LtExprAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {

    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, LtExprAST will compare them and Interpret will hold true if first is lower than second, false otherwise")
    {

    }
}

TEST_CASE("GtExprAST", "[class][ValueExprAST][VariableExprAST][State]")
{
    SECTION("For two type ValueExprAST operands, GtExprAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {

    }

    SECTION("For two VariableExprAST* operands, GtExprAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {

    }

    SECTION("For one ValueExprAST* and one VariableExprAST* operands, GtExprAST will compare them and Interpret will hold true if first is greater than second, false otherwise")
    {

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
