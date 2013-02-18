/*
	STimePeriod.cpp
	Sergey Aksenov, 2013
*/

#include "STimePeriod.h"


STimePeriod::STimePeriod()
{
	Default();
}

STimePeriod::~STimePeriod()
{
	// empty
}

void STimePeriod::Default()
{
	BeginDate = ptime(neg_infin);
	EndDate = ptime(neg_infin);
}

bool STimePeriod::IsEmpty() const
{
	return ((BeginDate > EndDate) || BeginDate.is_infinity() || BeginDate.is_infinity());
}

bool STimePeriod::Contans( ptime d ) const
{
	if(IsEmpty()) return false;

	return (BeginDate <= d) && (EndDate >= d);
}

bool STimePeriod::Contans( time_t d ) const
{
	ptime _time = from_time_t(d);
	return Contans(_time);
}