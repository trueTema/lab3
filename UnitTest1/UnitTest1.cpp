#include "pch.h"
#include "CppUnitTest.h"
#include "..\umschool\AVLTree.h"
#include "..\umschool\Set.h"
#include "..\umschool\Tree.h"
#include "..\umschool\complex.h"
#include "..\umschool\complex.cpp"
#include "..\umschool\Person.h"
#include "..\umschool\Person.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(NTreeTest)
		{
			//test1
			Tree<int> test1_a1(3);
			test1_a1.pushItem("", 1);
			test1_a1.pushItem("(1)", 5);
			test1_a1.pushItem("(2)", 3);
			test1_a1.pushItem("(2)(1)", 8);
			test1_a1.pushItem("(2)(2)", 9);
			test1_a1.pushItem("(1)(2)", 15);
			test1_a1.pushItem("(1)(2)(3)", 7);
			test1_a1.pushItem("(2)(2)(3)", 17);
			test1_a1.pushItem("(1)(1)", 0);
			Tree<int> check_0 = test1_a1.GetSubTree("(1)(2)");
			bool check_1 = test1_a1.IsSubTree(check_0);
			vector<Tree<int>*> check_2 = test1_a1.travelsal();
			int check_3 = test1_a1.findItem("");
			
			Tree<int> expected0("f()()(f)", { 15,7 }, 3);
			bool expected1 = true;
			vector<int> expected2 = { 1,5,0,15,7,3,8,9,17 };
			int expected3 = 1;
			//test1
			Assert::IsTrue((check_0 == expected0), L"Ntree: wrong answer, test 1");

			//test2
			Assert::IsTrue((check_1 == expected1), L"Ntree: wrong answer, test 2");

			//test3
			bool f = true;
			for (int i = 0; i < expected2.size(); i++) {
				f = f && (expected2[i] == check_2[i]->findItem(check_2[i], ""));
			}
			Assert::IsTrue(f, L"Ntree: wrong answer, test 3");
			test1_a1.erase(3);
			test1_a1.erase(0);
			string check_4 = test1_a1.to_str("К(1)(2)(3)");
			string expected4 = "1(5(15(7)))(17(8)(9))";

			//test4

			Assert::IsTrue(check_3==expected3, L"Ntree: wrong answe, test 4");

			//test5
			Assert::IsTrue(check_4 == expected4, L"Ntree: wrong answer, test 5");
		}

		TEST_METHOD(AVLTreeTest)
		{
			//test1
			AVLTree<double> avl;
			avl.push(0.55);
			avl.push(-56.709);
			avl.push(16.79);
			avl.push(30.42);
			avl.push(5.43);
			avl.push(1.789);
			bool check_1 = avl.find(1);
			bool expected_1 = false;
			avl.erase(-56.709);
			bool check_2 = avl.find(-56.709);
			bool expected_2 = false;
			vector<double> check_3 = *(avl.to_array());
			vector<double> expected_3 = { 0.55, 1.789, 5.43, 16.79, 30.42 };
			AVLTree<double> check_4 = *(avl.where([] (double x) { return x > 30; }));
			int expected_4_size = 1;
			bool expected_4_check = true;
			Assert::IsTrue((expected_1 == check_1), L"AVLTree: wrong answer, test 1");

			//test2
			Assert::IsTrue(check_2 == expected_2, L"AVLTree: wrong answer, test 2");

			//test3
			Assert::IsTrue(check_3==expected_3, L"stack: wrong answer, test 3");

			//test4
			Assert::IsTrue(check_4.size() == expected_4_size && check_4.find(30.42) == expected_4_check, L"AVLTree: wrong answer, test 4");
		}

		TEST_METHOD(SetTest) {
			set<complex> st;
			st.push(complex(1, 1));
			st.push(complex(1, 2));
			st.push(complex(17, -5));
			st.push(complex(1, 1));
			st.push(complex(4, 4));
			st.push(complex(0, 12));
			st.push(complex(0, 0));
			st.erase(complex(0, 0));
			Assert::IsTrue(st.size() == 5 && st.find(complex(0,0)) == false,L"Set: wrong answer, test 1");
		}
		TEST_METHOD(ComplexTest) {
			complex test1(3, 2);
			complex test2(-1, 3);//
			complex test3(4, 2);
			complex test4(7, 1);
			complex test5(-3, 3);
			complex exp1(6, (double)-1 / 3);
			test1 += test2;
			test1 -= test3;
			test1 *= test4;
			test1 /= test5;
			Assert::IsTrue(test1 == exp1, L"Complex: wrong answer, test 1");
		}
	};
}
