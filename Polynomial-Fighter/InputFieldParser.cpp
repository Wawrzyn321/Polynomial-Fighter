#include "InputFieldParser.h"
#include <cassert>
#include "RequestHandlers.h"
#include "StringSubprocessor.h"
#include "Debug.h"

RequestValue InputFieldParser::parse(const std::string& input)
{
	//preprocess input
	std::string unraw = RequestSubprocessor::removePeriods(input);
	unraw = RequestSubprocessor::removeTrailingSpaces(unraw);

	//create chain
	RequestHandler* chain =
		new EmptyStringHandler(
			new SingleNumberStringHandler(
				new LHSInequalityStringHandler(
					new RHSInequalityStringHandler(
						new ListStringHandler(
							new DivisorStringHandler(
								nullptr))))));

	//handle the input
	RequestValue r = chain->handle(unraw);
	/*
	if (r.isValid())
	{
		//display the result
		for (int result : r.result)
		{
			std::cout << result << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		//show error message
		//Debug::PrintErrorFormatted("InputFieldParser::parse: %", r.message);
	}
	std::cout << std::endl;
	*/
	delete chain;
	return r;
}

void InputFieldParser::runTests()
{
	RequestHandler* chain =
		new EmptyStringHandler(
			new SingleNumberStringHandler(
				new LHSInequalityStringHandler(
					new RHSInequalityStringHandler(
						new ListStringHandler(
							new DivisorStringHandler(
								nullptr))))));

	//empty
	RequestValue r = chain->handle("");
	assert(r.isValid() && r.message == RH_Codes::EMPTY);

	//single
	r = chain->handle("-0");
	assert(r.isValid() && r.result[0] == 0);
	r = chain->handle("7");
	assert(r.isValid() && r.result[0] == 7);
	r = chain->handle("8");
	assert(!r.isValid() && r.message == RH_Codes::OUT_OF_RANGE);
	r = chain->handle("-7");
	assert(r.isValid() && r.result[0] == -7);
	r = chain->handle("-8");
	assert(!r.isValid() && r.message == RH_Codes::OUT_OF_RANGE);
	r = chain->handle("9");
	assert(!r.isValid() && r.message == RH_Codes::OUT_OF_RANGE);
	r = chain->handle("-9");
	assert(!r.isValid() && r.message == RH_Codes::OUT_OF_RANGE);

	//LHS
	r = chain->handle("<2");
	assert(r.isValid() && r.result.size() == 9 && r.result[1] == -6);
	r = chain->handle("<-6");
	assert(r.isValid() && r.result.size() == 1 && r.result[0] == -7);
	r = chain->handle(">6");
	assert(r.isValid() && r.result.size() == 1 && r.result[0] == 7);
	r = chain->handle(">7");
	assert(r.isValid() && r.result.empty());
	r = chain->handle("<-7");
	assert(r.isValid() && r.result.empty());
	r = chain->handle("<<2");
	assert(!r.isValid());
	r = chain->handle(RequestSubprocessor::removeTrailingSpaces("     <    -2 2     2    "));
	assert(!r.isValid());

	//RHS
	r = chain->handle("2<");
	assert(r.isValid() && r.result[1] == 4);
	r = chain->handle("2><");
	assert(!r.isValid());
	r = chain->handle(RequestSubprocessor::removeTrailingSpaces("         -     2    >"));
	assert(!r.isValid());
	r = chain->handle(RequestSubprocessor::removeTrailingSpaces("         -2     2    >"));
	assert(!r.isValid());
	r = chain->handle("6<");
	assert(r.isValid() && r.result.size() == 1 && r.result[0] == 7);
	r = chain->handle("-6>");
	assert(r.isValid() && r.result.size() == 1 && r.result[0] == -7);
	r = chain->handle("7<");
	assert(r.isValid() && r.result.empty());
	r = chain->handle("-7>");
	assert(r.isValid() && r.result.empty());

	//LHS & RHS, generally all input with more than one '<' or '>' is incorrect
	//the same for '-'... or '8'... or '9'...
	r = chain->handle("><");
	assert(!r.isValid());
	r = chain->handle("<2<");
	assert(!r.isValid());
	r = chain->handle("<>2<>");
	assert(!r.isValid());

	//list
	r = chain->handle("1 2");
	assert(r.isValid() && r.result.size() == 2);
	r = chain->handle("-1 -2 -4");
	assert(r.isValid() && r.result.size() == 3&& r.result[2] == -1);
	r = chain->handle("-2 -2 -2 -3 -4 1 2 2");
	assert(r.isValid() && r.result.size() == 5);

	//divisor
	r = chain->handle("/-1");
	assert(r.isValid() && r.result[0] == -1 && r.message == RH_Codes::DIVISOR);
	r = chain->handle("/");
	assert(!r.isValid());
	r = chain->handle("/2-");
	assert(!r.isValid());
	r = chain->handle("/0");
	assert(!r.isValid() && r.message == RH_Codes::DIVISION_BY_ZERO);

	delete chain;
}
