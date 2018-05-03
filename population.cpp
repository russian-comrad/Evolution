#include "population.h"

//--------------------------------------------------------------------------------
// Action implementation
//--------------------------------------------------------------------------------

Population::Population() :
	mMutateTemplate({ 0, 0, 0, 0, 1, 2, 3, 4 })
{
	mOrganisms.resize(64);
	mCurentOrganism = mOrganisms.begin();
}
//--------------------------------------------------------------------------------
Population::~Population()
{}
//--------------------------------------------------------------------------------
LifeStatus
Population::status()
{
	LifeStatus result;
	if (mOrganisms.size() > mOrganismsMinCount)
	{
		result = LifeStatus::NaturalSelection;
	}
	else
	{
		result = LifeStatus::RequiresEvolution;
	}
	return result;
}
//--------------------------------------------------------------------------------
void
Population::evolve()
{
	for (std::list<Creature> ::iterator it = mOrganisms.begin();
		it != mOrganisms.end(); ++it)
	{
		for (uint_16 j = 0; j < mOrganismsChildCount; ++j)
		{
			mOrganisms.push_back(*it);
		}
	}

	for (std::list<Creature> ::iterator it = mOrganisms.begin();
		it != mOrganisms.end(); ++it)
	{
		it->mutate(mMutateTemplate.front());
		it->reset();


		mMutateTemplate.push(mMutateTemplate.front());
		mMutateTemplate.pop();
	}
}
//--------------------------------------------------------------------------------
void
Population::savePopulation(std::stringstream ss)
{

}
//--------------------------------------------------------------------------------
void 
Population::loadPopulation(std::stringstream ss)
{

}
//--------------------------------------------------------------------------------
Action* 
Population::getNextAction()
{
	Action* action = mCurentOrganism->getAction();
	if (action->isCompletAction())
	{
		mCurentOrganism->step();
		++mCurentOrganism;
	}
	return action;
}
//--------------------------------------------------------------------------------
void 
Population::giveResponse(Response* aResponse)
{
	mCurentOrganism->processResponses(aResponse);
}
//--------------------------------------------------------------------------------