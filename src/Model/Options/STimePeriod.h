/*
	STimePeriod.h
	Sergey Aksenov, 2013
*/

#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

struct STimePeriod
{
public:
	STimePeriod();
	~STimePeriod();

	void Default();

	bool IsEmpty() const;

	bool Contans(ptime d) const;
	bool Contans(time_t d) const;

public:
	ptime BeginDate;
	ptime EndDate;
};