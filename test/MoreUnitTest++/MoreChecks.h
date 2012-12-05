#ifndef MOREUNITTEST_CHECKS_H
#define MOREUNITTEST_CHECKS_H

#include <Checks.h>


namespace MoreUnitTest 
{
	template< typename Pointer >
	void CheckNull(UnitTest::TestResults& results, Pointer const& pointer, UnitTest::TestDetails const& details)
	{
		if (!(pointer == 0))
		{
			UnitTest::MemoryOutStream stream;
			stream << "Expected NULL pointer but was " << pointer;

			results.OnTestFailure(details, stream.GetText());
		}
	}


	template< typename Pointer >
	void CheckNotNull(UnitTest::TestResults& results, Pointer const& pointer, UnitTest::TestDetails const& details)
	{
		if (pointer == 0)
		{
			UnitTest::MemoryOutStream stream;
			stream << "Unexpected NULL pointer";

			results.OnTestFailure(details, stream.GetText());
		}
	}


	template< typename Unexpected, typename Actual >
	void CheckNotEqual(UnitTest::TestResults& results, Unexpected const& unexpected, Actual const& actual, UnitTest::TestDetails const& details)
	{
		if (unexpected == actual)
		{
			UnitTest::MemoryOutStream stream;
			stream << "Did not expect " << unexpected;

			results.OnTestFailure(details, stream.GetText());
		}
	}
}


#endif