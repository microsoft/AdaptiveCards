#include "stdafx.h"
#include "CppUnitTest.h"
#include "TextBlock.h"
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AdaptiveCards;
using namespace std;

namespace AdaptiveCardsSharedModelUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(ISO8601TransformTest)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
            blck->SetText("{{DATE(2017-02-13T20:46:30Z, Short)}}");
			Assert::AreEqual<string>("02/13/2017",  blck->GetText());
			delete blck;
		}
		TEST_METHOD(ISO8601TransformTestLong)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{{DATE(2017-02-13T20:46:30Z, Long)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("Monday, February 13, 2017", blck->GetText());
			delete blck;
		}
		TEST_METHOD(ISO8601TransformTestDefault)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{{DATE(2017-02-13T20:46:30Z)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("02/13/2017", blck->GetText());
			delete blck;
		}

		TEST_METHOD(ISO8601TransformBadInputTest)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{a{DATE(2017-02-13T20:46:30Z, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("{a{DATE(2017-02-13T20:46:30Z, Short)}}", blck->GetText());
			delete blck;
		}

		TEST_METHOD(ISO8601TransformBadInputTest2)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{{DATE(2017-02-13T20:46:30Z, Short)}";
			blck->SetText(testString);
			Assert::AreEqual<string>("{{DATE(2017-02-13T20:46:30Z, Short)}", blck->GetText());
			delete blck;
		}

		TEST_METHOD(ISO8601TransformBadInputTest3)
		{
			TextBlock* blck = new TextBlock();
			Assert::IsNotNull(blck);
			string testString = "{{DATE(2017a02-13T20:46:30Z, Short)}";
			blck->SetText(testString);
			Assert::AreEqual<string>("{{DATE(2017a02-13T20:46:30Z, Short)}", blck->GetText());
			delete blck;
		}

		TEST_METHOD(TransformToDateTest1)
		{
			TextBlock* blck = new TextBlock();
			string testString = "{{DATE(2017-02-13T20:46:30Z, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("02/13/2017", blck->GetText());
			delete blck;
		}

		TEST_METHOD(TransformToDateTest2)
		{
			TextBlock* blck = new TextBlock();
			string testString = "{{TIME(2017-10-27T18:19:09Z, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("11:19 AM", blck->GetText());
			delete blck;
		}
		TEST_METHOD(TransformToDateTest3)
		{
			TextBlock* blck = new TextBlock();
			string testString = "{{DATE(2017-10-28T01:47:00Z, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("10/27/2017", blck->GetText());
			delete blck;
		}
		TEST_METHOD(TransformToTimeTest)
		{
			TextBlock* blck = new TextBlock();
			string testString = "{{Time(2017-10-28T02:17:00Z, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("07:17 PM", blck->GetText());
			delete blck;
		}
		TEST_METHOD(TransformToDateTest4)
		{
			TextBlock* blck = new TextBlock();
			string testString = "{{Date(2017-10-28T02:17:00Z, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("10/27/2017", blck->GetText());
			delete blck;
		}
		TEST_METHOD(TransformToTimeTest1)
		{
			TextBlock* blck = new TextBlock();
			// paris
			string testString = "{{Time(2017-10-28T04:20:00+02:00, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("07:20 PM", blck->GetText());
			delete blck;
		}
		TEST_METHOD(TransformToDateTest5)
		{
			TextBlock* blck = new TextBlock();
			// paris
			string testString = "{{DATE(2017-10-28T04:20:00+02:00, Short)}}";
			Assert::AreEqual<string>("10/27/2017", blck->parseISO8601(testString.begin(), testString.end()));
			delete blck;
		}

		TEST_METHOD(TransformToTimeTest3)
		{
			TextBlock* blck = new TextBlock();
			// seoul 
			string testString = "{{Time(2017-10-28T11:25:00+09:00, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("07:25 PM", blck->GetText());
			delete blck;
		}

		TEST_METHOD(TransformToDateTest6)
		{
			TextBlock* blck = new TextBlock();
			// seoul 
			string testString = "{{DATE(2017-10-28T11:25:00+09:00, Long)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("Friday, October 27, 2017", blck->GetText());
			delete blck;
		}

		TEST_METHOD(TransformToTimeTest4)
		{
			TextBlock* blck = new TextBlock();
			// New York 
			string testString = "{{TIME(2017-10-27T22:27:00-04:00, Short)}}"; 
			blck->SetText(testString);
			Assert::AreEqual<string>("07:27 PM", blck->GetText());
			delete blck;
		}
		TEST_METHOD(TransformToDateTest7)
		{
			TextBlock* blck = new TextBlock();
			// New York 
			string testString = "{{DATE(2017-10-27T22:27:00-04:00, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("10/27/2017", blck->GetText());
			delete blck;
		}
		TEST_METHOD(mallformedinputTest1)
		{
			TextBlock* blck = new TextBlock();
			// New York 
			string testString = "{{TIME(2017-10-27T22:7:00-04:00, Short)}}"; 
			blck->SetText(testString);
			Assert::AreEqual<string>("{{TIME(2017-10-27T22:7:00-04:00, Short)}}", blck->GetText());
			delete blck;
		}
		TEST_METHOD(mallformedinputTest2)
		{
			TextBlock* blck = new TextBlock();
			// New York 
			string testString = "{{TIME(2017-10-27T2:7:00Q04:00, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("{{TIME(2017-10-27T2:7:00Q04:00, Short)}}", blck->GetText());
			delete blck;
		}
		TEST_METHOD(ISO8601WithText)
		{
			TextBlock* blck = new TextBlock();
			// New York 
			string testString = "You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("You have arrived in New York on 10/27/2017", blck->GetText());
			delete blck;
		}

		TEST_METHOD(TwoISO8601WithText)
		{
			TextBlock* blck = new TextBlock();
			// New York 
			string testString = "You have arrived in New York on {{DATE(2017-10-27T22:27:00-04:00, Short)}} at {{TIME(2017-10-27T22:27:00-04:00, Short)}}";
			blck->SetText(testString);
			Assert::AreEqual<string>("You have arrived in New York on 10/27/2017 at 07:27 PM", blck->GetText());
			delete blck;
		}
	};
}
