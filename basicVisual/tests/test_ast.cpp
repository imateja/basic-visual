#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "inc/ast.h"

/* TODO: double comparison */
TEST_CASE("ValueExprAST", "[class]")
{
    SECTION("Za ValueExprAST inicijalizovan double-om value, getValue() vraca value")
    {
        ValueExprAST input{5.24};
        double expectedOutput = 5.24;

        double output = input.getValue();

        REQUIRE(output == expectedOutput);
    }

   SECTION("Duboko kopirani ValueExprAST ce imati drugaciju adresu od originala")
   {
        ValueExprAST* expr1 = new ValueExprAST(5.24);

        ValueExprAST* expr2 = static_cast<ValueExprAST*>(expr1->copy());

        REQUIRE_FALSE(expr1 == expr2);
   }
}
