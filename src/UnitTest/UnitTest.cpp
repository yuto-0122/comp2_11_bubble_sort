#include "pch.h"
#include "CppUnitTest.h"
#include "../include/lib_func.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(基本確認)
	{
	public:
		
		TEST_METHOD(一要素はそのまま)
		{
			item items[1] = { {1, "Hello world!"} };
			Assert::IsTrue(bubble_sort(items, items + sizeof(items)/sizeof(item)));
			Assert::AreEqual("Hello world!", items[0].value);

		}

		TEST_METHOD(２要素でそのまま)
		{
			item items[2] = {
				{2, "Hello"},
				{4, "world!"},
			};
			Assert::IsTrue(bubble_sort(items, items + sizeof(items) / sizeof(item)));
			Assert::AreEqual("Hello", items[0].value);
			Assert::AreEqual("world!", items[1].value);
		}

		TEST_METHOD(２要素で入れ替え)
		{
			item items[2] = {
				{9, "world!"},
				{7, "Hello"},
			};
			Assert::IsTrue(bubble_sort(items, items + sizeof(items) / sizeof(item)));
			Assert::AreEqual("Hello", items[0].value);
			Assert::AreEqual("world!", items[1].value);
		}
	};

	TEST_CLASS(品質確認)
	{
	public:

		TEST_METHOD(NULLは帰り値がfalse)
		{
			item items[1];
			Assert::IsFalse(bubble_sort(NULL, items));
			Assert::IsFalse(bubble_sort(items, NULL));
		}

		TEST_METHOD(endのアドレスが小さいのはダメ)
		{
			item items[1];
			Assert::IsFalse(bubble_sort(items + sizeof(items) / sizeof(item), items));
		}

		TEST_METHOD(半端なbeginアドレスはダメ)
		{
			item dummy[2] = {{2, "Hello"},{4, "world!"}};
			char* p = (char*)dummy;
			p++;// アドレスをあえてずらす
			item* items = (item *)p;
			Assert::IsFalse(bubble_sort(items, items + 1));
		}

		TEST_METHOD(半端なendアドレスはダメ)
		{
			item items[2] = { {2, "Hello"},{4, "world!"} };
			char* p = (char*)&items[1];
			p++;// アドレスをあえてずらす
			item* items1 = (item*)p;
			Assert::IsFalse(bubble_sort(items, items1));
		}

		TEST_METHOD(たくさんの要素を入れ替え)
		{
			const int NUM = 100000;
			item *items = (item*)malloc(sizeof(item) * NUM);
			if (NULL == items) { Assert::Fail(); return; }

			for (int i = 0; i < NUM; i++) {
				items[i].key = NUM - i;
				sprintf_s(items[i].value, 256, "%d", i);
			}

			Assert::IsTrue(bubble_sort(items, items + NUM));

			for (int i = 0; i < NUM; i++) {
				char buf[256];
				sprintf_s(buf, 256, "%d", NUM - i - 1);
				Assert::AreEqual(buf, items[i].value);
			}

			free(items);
		}
	};
}
