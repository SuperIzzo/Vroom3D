#include <UnitTest++.h>
#include <cstdio>


int main(int argc, char* args[])
{
	if ( argc > 1   &&   strcmp("-test", args[1])==0 )
	{
		int result = 0;

		printf("\n--=-=-=-=== = Test = ===-=-=-=--\n");
		result = UnitTest::RunAllTests();
		printf(  "--=-=-=-== == ==== == ==-=-=-=--\n\n");

		return result;
	}
	else
	{
		return 0;
	}
}