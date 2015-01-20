#include "ThiefState.h"
#include "GameManager.h"
#include "GameRunningState.h"
#include "MagicianState.h"
ThiefState::ThiefState()
{
	printf("Thief State\n");
}

void ThiefState::Handle(GameRunningState& context, GameManager& gm){
	IRoundState::Handle(context, gm);

	if (m_CurrentPlayer.get() == nullptr || gm.isKilled(currentRole())) {
		context.setState(unique_ptr < IRoundState > {new MagicianState});
		return;
	}

	vector<string> answers = { "Magican", "King", "Bishop", "Merchant", "Architect", "Warlord" };
	int result = m_CurrentPlayer->RequestInput("Which character would you like to rob?", answers);

	gm.setRobbed(eCharacterCard(result + 2));

	m_CurrentPlayer->Send("You robbed the " + answers.at(result) + "\n");

	context.setState(unique_ptr < IRoundState > {new MagicianState});
}

ThiefState::~ThiefState()
{
}

eCharacterCard ThiefState::currentRole() {
	return Thief;
}

