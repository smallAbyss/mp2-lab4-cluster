#include "cl.h"
#include "gtest.h"
#include <typeinfo>

TEST(CL, can_create_cluster_with_correct_arguements)
{
	ASSERT_NO_THROW( CL c(42, 42, 42));
}

TEST(CL, cannot_create_cluster_with_incorrect_process_num)
{
	ASSERT_ANY_THROW(CL c(0, 42, 42));
}

TEST(CL, cannot_create_cluster_with_incorrect_maximum_tact)
{
	ASSERT_ANY_THROW(CL c(42, 0, 42));
}

TEST(CL, cannot_create_cluster_with_incorrect_chance_of_task_appearing)
{
	ASSERT_ANY_THROW(CL c(42, 42, 4200));
}

TEST(CL, can_simulate_with_random_generated_tasks__one_per_tact) {
	CL c(42, 42, 42);
	ASSERT_NO_THROW(c.Simulation(1));
}

TEST(CL, can_simulate_with_random_generated_tasks) {
	//srand(time(0));
	CL c(42, 42, 42);
	ASSERT_NO_THROW(c.Simulation(25));
}

TEST(CL, can_simulate_in_test_mode__no_tasks) {
	CL c(42, 42, 42);
	vector <Task> v{  };
	vector <Task>* t = &v;
	ASSERT_NO_THROW(c.Simulation(0, t));
}

TEST(CL, can_simulate_in_test_mode) {
	CL c(42, 42, 42);
	vector <Task> v{ {0, 0, 2, 1}, {0, 0, 5, 10} };
	vector <Task>* t = &v;
	ASSERT_NO_THROW(c.Simulation(0, t));
}

TEST(CL, too_many_processors_required) {
	CL c(42, 42, 42);
	vector <Task> v{ {0, 0, 424242, 100 }, {1, 0, 42, 1 } , {2, 0, 42, 1 } };
	vector <Task>* t = &v;
	ASSERT_ANY_THROW(c.Simulation(0, t));
}

TEST(CL, can_return_statistic) {
	CL c(42, 42, 42);
	EXPECT_TRUE((string(typeid(c.Simulation(25)).name()) == string("struct Statistic")));
}

TEST(CL, return_right_statistic_when_no_tasks) {
	CL c(42, 42, 42);
	vector <Task> v{ };
	vector <Task>* t = &v;
	Statistic st{ 0, 0, 0, 0 };
	EXPECT_TRUE(c.Simulation(0, t) == st);
}

TEST(CL, return_right_statistic_when_no_tasks_has_completed) {
	CL c(42, 42, 42);
	vector <Task> v{ {0, 0, 42, 100 }, {1, 0, 42, 1 } , {2, 0, 42, 1 } };
	vector <Task>* t = &v;
	Statistic st{ 3, 0, 1, 1 };
	EXPECT_TRUE(c.Simulation(0, t) == st);
}

TEST(CL, return_right_statistic_when_all_tasks_completed) {
	CL c(4, 4, 42);
	vector <Task> v{ {0, 0, 2, 2 }, {1, 0, 2, 1 } , {2, 0, 3, 2} };
	vector <Task>* t = &v;
	Statistic st{ 3, 3, 0, 0.75 };
	EXPECT_TRUE(c.Simulation(0, t) == st);
}

TEST(CL, return_right_statistic_when_some_tasks_completed) {
	CL c(6, 5, 0);
	vector <Task> v{ {0, 0, 3, 2 }, {1, 0, 5, 2 } , {2, 0, 6, 5 },  {3, 0, 2, 5 },  {3, 0, 6, 3 } }; 
	vector <Task>* t = &v;
	Statistic st{ 5, 2, 1, 0.733333 };
	EXPECT_TRUE(c.Simulation(0, t) == st);
}

// however, the fact tact cycle starts when t == Tmax, I think its it would be a mistake to say that tasks, started on the last  
// iteration, are "running", because they started a moment before the cluster ends its work (sorry for bad english)
TEST(CL, return_right_statistic_when_some_tasks_completed_no_running) {
	CL c(6, 5, 0);
	vector <Task> v{ {0, 0, 3, 2 }, {1, 0, 5, 3 } , {2, 0, 6, 5 },  {3, 0, 2, 5 },  {3, 0, 6, 3 } };
	//____________________________________~~~___here the differrence between this and previous
	vector <Task>* t = &v;
	Statistic st{ 5, 2, 0, 0.7 };
	//_________________~~~~~~~~~~~~____and here
	EXPECT_TRUE(c.Simulation(0, t) == st);
}


