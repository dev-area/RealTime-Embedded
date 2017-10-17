#pragma once
#include <iostream>
#include <string>
namespace garage_controller
{
	class StateContext {
		friend class Closing;
		friend class Closed;
		friend class Opening;
		friend class Open;
		public:
			StateContext () { aState = &_closedState;}
			std::string getStateAsText() const{return aState->toString();}
			void pushButton() { aState->pushButton( *this ); }
			void motorStopped() { aState->motorStopped( *this ); }
			bool tripSensor() { return( aState->tripSensor( *this ) ); }
		private:
			class GarageDoorControllerState
			{
				public:
					virtual void pushButton( StateContext& pStateContext )=0;
					virtual void motorStopped( StateContext& pStateContext )=0;
					virtual bool tripSensor( StateContext& pStateContext )=0;
					virtual std::string toString() const =0;
			};

			class Closed : public GarageDoorControllerState {
				public:
					void pushButton( StateContext& pStateContext ) ;
					void motorStopped( StateContext& pStateContext ) { }            
					bool tripSensor( StateContext& pStateContext ) { return false ; }
            
					std::string toString() const {return "Closed";}
			};

			class Opening : public GarageDoorControllerState {
				public:
					void pushButton( StateContext& pStateContext );
					void motorStopped( StateContext& pStateContext );
					bool tripSensor( StateContext& pStateContext ) { return false; }
					std::string toString() const {return "Opening";	}
			};

			class Open : public GarageDoorControllerState {
				public:
					void pushButton( StateContext& pStateContext );
					void motorStopped( StateContext& pStateContext ){}
					bool tripSensor( StateContext& pStateContext ) { return false; }
					std::string toString()const {return "Open";	}
			};

			class Closing : public GarageDoorControllerState {
				public:
					void pushButton( StateContext& pStateContext );
					void motorStopped( StateContext& pStateContext );
					bool tripSensor( StateContext& pStateContext );
					std::string toString()const {return "Closing";	}
			};

			GarageDoorControllerState* aState;
			
			void setState( GarageDoorControllerState* pState ) { aState = pState;}
			
			static Closed _closedState;
			static Closing _closingState;
			static Open _openState;
			static Opening _openingState;
	} ;
}