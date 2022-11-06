/* * * * * * * * * * * * * *
 * Title : Calculator
 * Author: Mariia Ivanski
 * Reviewer: Alena :)
 * Review status: TBR
 * Date : 03/11/2022
 * * * * * * * * * * * * * */

#include <stdio.h>  /* printf, puts */
#include <assert.h> /* assert */

#include "calc.h"  /*function declarations*/
#include "tests.h" /*test macros*/

int main()
{
    double output = 0;
    status_t status;
    status = Calculate("1+1=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 2.0);

  

    status = Calculate("(-5)-(-2)=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, -3.0);

    status = Calculate(" 5-1 +10+15+0+6666 - 99=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 6596.0);

    status = Calculate("5*2=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 10.0);

    status = Calculate("3+5*2=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 13.0);

    status = Calculate("3+5/2=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 5.5);

    status = Calculate("3^2=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 9.0);

    status = Calculate("1+5-2*2^2+6/2=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 1.0);

   

    output = 0;
    status = Calculate("(-3)+5/0+6*23/0/0/0/10=", &output);
    TEST("TESTING Calculate", status, ILLEGAL_OPERATION);
    
    /*
    TEST_DOUBLE("TESTING Calculate", output, 0.0);
*/
    output = 0;
    status = Calculate("(-3)+5/(0^0)+6*23=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 140.0);

    status = Calculate("(3+2)*1=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 5.0);
    
    status = Calculate("(-1)*((-8)/2 - 1)=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 5.0);
    
    
    status = Calculate("((-3)+2)*(5-3*-(4/2 - 1))=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, -8.0);
/*
*/

    status = Calculate("1+5-2*2^2+6/2=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 1.0);

    status = Calculate("(-2)^(-6/2)=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, -0.125);

 

    status = Calculate("2^(2^3)=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 256.0);

    status = Calculate("(2^2)^3=", &output);
    TEST("TESTING Calculate", status, SUCCESS);
    TEST_DOUBLE("TESTING Calculate", output, 64.0);
    
    status = Calculate("(2^2)^3)=", &output);
    TEST("TESTING Calculate", status, SYNTAX_ERR);
    
    status = Calculate("1)*3=", &output);
    TEST("TESTING Calculate", status, SYNTAX_ERR);


    status = Calculate(")))))))", &output);
    TEST("TESTING Calculate", status, SYNTAX_ERR);


    PASS;
    puts("\033[33m");
    puts("|￣￣￣￣￣￣￣￣￣￣￣|\n| Hasta la vista, baby |\n|＿＿＿＿＿＿＿＿＿＿＿|\n(|__/) ||\n(•ㅅ•) ||\n/ 　 づ\n");
    puts("\033[0m");

    return 0;
}
