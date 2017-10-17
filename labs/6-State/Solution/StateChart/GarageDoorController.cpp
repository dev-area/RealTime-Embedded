#include "GarageDoorController.h"

namespace garage_controller
{
	StateContext::Closed StateContext::_closedState;
	StateContext::Closing StateContext::_closingState;
	StateContext::Open StateContext::_openState;
	StateContext::Opening StateContext::_openingState;


	void StateContext::Closed::pushButton( StateContext& pStateContext ) 
	{
		pStateContext.setState(&StateContext::_openingState);
	}

	void StateContext::Opening::pushButton( StateContext& pStateContext )
	{
		pStateContext.setState(&StateContext::_closingState);
	}
	void StateContext::Opening::motorStopped( StateContext& pStateContext )
	{
		pStateContext.setState(&StateContext::_openState);
	}
	void StateContext::Open::pushButton( StateContext& pStateContext )
	{
		pStateContext.setState(&StateContext::_closingState);
	}

	void StateContext::Closing::pushButton( StateContext& pStateContext )
	{
		pStateContext.setState(&StateContext::_openingState);
	}
	void StateContext::Closing::motorStopped( StateContext& pStateContext )
	{
		pStateContext.setState(&StateContext::_closedState);
	}
	bool StateContext::Closing::tripSensor( StateContext& pStateContext )
	{
		pStateContext.setState(&StateContext::_openingState);
		return true;
	}
}