#pragma once
#include <iostream>
#include <string>
namespace garage_controller
{
	class StateContext {
		public:
			StateContext ()	{ /*TODO: Implement */ }
			
			void pushButton() {/*TODO: Implement */}
			void motorStopped() { /*TODO: Implement */ }
			bool tripSensor() { /*TODO: Implement */ return false;}
			
			std::string getStateAsText() const{return aState->toString();}
		private:

			class GarageDoorControllerState
			{
				public:
					virtual void pushButton( StateContext& pStateContext )=0;
					virtual void motorStopped( StateContext& pStateContext )=0;
					virtual bool tripSensor( StateContext& pStateContext )=0;
			
					virtual std::string toString() const =0;
			};

			void setState( GarageDoorControllerState* pState ) { aState = pState;}
			
			GarageDoorControllerState* aState;

	} ;
}