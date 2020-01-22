//#include "rootheader.h"
#include "femtoDst.cxx"
//#include "somePlots.cxx"
//#include "mathFuncs.cxx"

// NEED TO FIGURE OUT HOW TO LINK FILES FOR A SECOND ATTEMPT

int mainFemto(TString filename,int jobNum,float energy,int runNum,int numJobs)
{
	// femtoDst *femtoTest = new femtoDst("Data/test/run11/test05.root");
	//femtoDst *femtoTest = new femtoDst("Data/test/run11/smallTree01.root");
	//femtoDst *femtoTest = new femtoDst("Data/test/run11/smallTree02.root");
	femtoDst *femtoTest = new femtoDst(filename,jobNum,energy,runNum,false,numJobs);

	// tests to make sure everything works
	cout << femtoTest->ShowNumEvents() << endl;

	// cout << femtoTest->ShowPosPions(2) << endl;


	cout << "Program Ended" << endl;

	return 0;
}
