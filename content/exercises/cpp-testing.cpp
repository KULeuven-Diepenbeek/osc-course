
#include <iostream>
#include <stdlib.h>
#include "gtest/gtest.h"

struct date {
	int day;
	int month;
	int year;
};
typedef struct date date;
struct period {
	date from;
	date to;
};
typedef struct period period;

int isInPeriod(period* p, date date) {
	return 0;
}

TEST(PeriodTest, GoodLuckWithThat) {
	EXPECT_EQ(0, 1) << "Add as many TEST cases as you can think of and complete isInPeriod()!";
}

/*
UNCOMMENT this to test the above code without using Google Test.
Remember, a main() function should be provided in a separate file called 'gtest-main.cpp', see lab notes.

int main() {
	date beginFeb = { 01, 01, 2020 };
	date endFeb = { 28, 01, 2020 };
	period* p = (period*) malloc(sizeof(period));
	p->from = beginFeb;
	p->to = endFeb;

	date testDate = { 02, 02, 2020 };
	int inPeriod = isInPeriod(p, testDate);

	printf("Is in period? %d/%d/%d in [%d/%d/%d, %d/%d/%d] -- %s \n", testDate.day, testDate.month, testDate.year,
		p->from.day, p->from.month, p->from.year, p->to.day, p->to.month, p->to.year, inPeriod == 0 ? "no" : "yes");

	return 0;
}
*/