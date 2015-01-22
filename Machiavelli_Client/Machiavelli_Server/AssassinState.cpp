#include "AssassinState.h"
#include "GameManager.h"
#include "GameRunningState.h"
#include "ThiefState.h"

AssassinState::AssassinState()
{
	printf("Assassin State\n");
}
void AssassinState::Handle(GameRunningState& context, GameManager& gm)
{
	IRoundState::Handle(context, gm);

	if (m_CurrentPlayer.get() == nullptr) 
	{
		context.setState(unique_ptr < IRoundState > {new ThiefState});
		return;
	}

	vector<string> answers = {"Thief", "Magician", "King", "Bishop", "Merchant", "Architect", "Warlord" };
	int result = m_CurrentPlayer->RequestInput("Please select a character to murder.", answers);

	// Since "Assassin" was not on our chacter list, the enum we need is answer + 1
	gm.setKilled(eCharacterCard(result + 1));

	m_CurrentPlayer->Send("The " + answers.at(result) + " was killed\n.");
	gm.GetPlayerList()->SendAllBut(m_CurrentPlayer, "The " + answers.at(result) + " has been killed by the Assassin!\n");

	gm.GetPlayerList()->SendAll("The " + gm.GetCardManager()->CharacterEnumToString(currentRole()) + "'s turn is over!\n");
	context.setState(unique_ptr<IRoundState> {new ThiefState});
}



