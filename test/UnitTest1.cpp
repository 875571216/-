#include "pch.h"
#include "CppUnitTest.h"
#include "..\line\Դ.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)

		{
			line l1(1, 0, 0, 1);
			line l2(0, 0, 2, 2);
			dot d = l1.lintersrctl(l2);
			Assert::AreEqual(d.x, 0.5);
			Assert::AreEqual(d.y, 0.5);
		}

		TEST_METHOD(TestMethod2)

		{
			line l1(1, 0, 0, 1);
			line l2(2, 0, 0, 2);
			bool interesect = l1._lintersrctl(l2);
			Assert::AreEqual(interesect, false);
		}

		TEST_METHOD(TestMethod3)

		{
			cycle c1(0, 0, 1);
			cycle c2(3, 0, 1);
			bool flag = c1.cintersectc(3, 0, 1);
			Assert::AreEqual(flag, false);
		}

		TEST_METHOD(TestMethod4)

		{
			cycle c1(0, 0, 1);
			cycle c2(2, 0, 1);
			dots.clear();
			c1.cintersectc(2, 0, 1);
			Assert::AreEqual((int)dots.size(), 1);
		}

		TEST_METHOD(TestMethod5)
		{
			cycle c1(0, 0, 1);
			cycle c2(1, 1, 1);
			dots.clear();
			c1.cintersectc(1, 1, 1);
			Assert::AreEqual((int)dots.size(), 2);
		}

		TEST_METHOD(TestMethod6)

		{
			cycle c1(0, 0, 2);
			cycle c2(1, 0, 1);
			dots.clear();
			c1.cintersectc(1, 0, 1);
			Assert::AreEqual((int)dots.size(), 1);
		}

		TEST_METHOD(TestMethod7)

		{
			cycle c1(0, 0, 2);
			cycle c2(0, 0, 1);
			dots.clear();
			c1.cintersectc(0, 0, 1);
			Assert::AreEqual((int)dots.size(), 0);
		}

		TEST_METHOD(TestMethod8)
		{
			cycle c(0, 0, 1);
			line l(2, 0, 2, 1);
			dots.clear();
			c.cintersectl(l);
			Assert::AreEqual((int)dots.size(), 0);
		}

		TEST_METHOD(TestMethod9)
		{
			cycle c(0, 0, 1);
			line l(0, 1, 1, 1);
			dots.clear();
			c.cintersectl(l);
			Assert::AreEqual((int)dots.size(), 1);
		}

		TEST_METHOD(TestMethod10)
		{
			cycle c(0, 0, 1);
			line l(1, 0, 0, 1);
			dots.clear();
			c.cintersectl(l);
			Assert::AreEqual((int)dots.size(), 2);
		}
	};
}
