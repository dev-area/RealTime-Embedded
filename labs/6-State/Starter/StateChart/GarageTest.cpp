#include <iostream>
#include "GarageDoorController.h"

using namespace std;

garage_controller::StateContext garageFSM;

void pushButtonFullOpeartionTest()
{
	cout << garageFSM.getStateAsText() << endl;

	garageFSM.pushButton();

	cout << garageFSM.getStateAsText() << endl;

	garageFSM.motorStopped();

	cout << garageFSM.getStateAsText() << endl;
}
void pushButtonWithTripTest()
{
	cout << garageFSM.getStateAsText() << endl;

	garageFSM.pushButton();

	cout << garageFSM.getStateAsText() << endl;

	garageFSM.tripSensor();

	cout << garageFSM.getStateAsText() << endl;

	garageFSM.motorStopped();

	cout << garageFSM.getStateAsText() << endl;


}
void main()
{
	cout << "1\n";
	pushButtonFullOpeartionTest();
	cout << "2\n";
	pushButtonFullOpeartionTest();
	cout << "3\n";
	pushButtonFullOpeartionTest();
	cout << "4\n";
	pushButtonWithTripTest();

}
