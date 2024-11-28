#include "gtest.h"
#include "queue.h"

TEST(TStackQueue, can_create_queue)
{
	ASSERT_NO_THROW(TStackQueue<int> q);
}

TEST(TStackQueue, get_size_works_correct)
{
	TStackQueue<int> q;
	q.Push(42);
	q.Push(4242);
	ASSERT_EQ(2, q.size());
}

TEST(TStackQueue, top_works_correct) {
	TStackQueue<int> q;
	q.Push(42);
	q.Push(4242);
	q.Push(424242);
	EXPECT_EQ(q.Top(), 42);
}

TEST(TStackQueue, cannot_pop_from_empty_queue)
{
	TStackQueue<int> q;
	q.Push(42);
	q.Pop();
	ASSERT_ANY_THROW(q.Pop());
}

TEST(TStackQueue, cannot_top_from_empty_queue)
{
	TStackQueue<int> q;
	q.Push(42);
	q.Pop();
	ASSERT_ANY_THROW(q.Top());
}

TEST(TStackQueue, IsEmpty_works_correct)
{
TStackQueue<int> q;
	bool q0 = q.IsEmpty();
	q.Push(42);
	bool q1 = q.IsEmpty();
	q.Pop();
	bool q2 = q.IsEmpty();
	ASSERT_TRUE((q0 == 1) && (q1 == 0) && (q2 == 1));
}

TEST(TStackQueue, TStackQueue_can_work_with_user_types)
{
	class MyClass {
		int a;
		char b;
	public:
		MyClass(int a_ = 0, char b_ = ' ') : a(a_), b(b_) {}

		MyClass(const MyClass& obj) : a(obj.a), b(obj.b) {}

		bool operator==(const MyClass& rh) {
			return ((a == rh.a) && (b == rh.b));
		}

		bool operator!=(const MyClass& rh) {
			return !(this->operator==(rh));
		}
	};
	TStackQueue<MyClass> q;
	MyClass obj1(5, 'o'), obj2(15, 'm');
	q.Push(obj1);
	q.Push(obj2);

	MyClass obj3(q.Top());
	q.Pop();
	ASSERT_TRUE((obj3 == obj1) && (q.Top() == obj2));
}