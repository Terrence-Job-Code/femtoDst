//#include "rootheader.h"
#include "femtoDst.h"

using namespace std;


// centrality note
// most central collisions are 0-5%

// EDIT : search for EDIT to find areas that I want to improve

femtoDst::femtoDst(TString filePath,int jobNum, float energy, int runNum,bool chainExist=false,int numJobs=100)
{
	m_jobNum = jobNum;
	m_Energy = energy;
	m_RunNumber = runNum;
	int m_numJobs = numJobs;

    ///////////////////////////// routine for skipping some files
    //
    //not entirely necessary, as the program seems to skip zombie files without too much of a problem

    bool skipVals[6000];
    for(int i = 0; i < 5217; i++)
    {
        skipVals[i] = false;
    }

    for(int i = 5217; i <6000; i++)
    {
        skipVals[i] = true;
    }

    char skiplist[256];
    sprintf(skiplist,"skip.list");

    ifstream skipOpen(skiplist);
    int safety = 0;
    int skipEvent;
    
    // doesn't seem to do anything
    //while(safety<6000)
    //{
    //    skipOpen >> skipEvent;
    //    skipVals[skipEvent] = true;
    //    if(skipOpen.eof()) break;
    //    safety++;
    //}

    ///////////////////////////////////// end of skipping file setup

	m_file = new TFile(filePath); 

	// input strings here for output


    int numFiles = 40; // number of files being chained together

	char outputDir[256];
	sprintf(outputDir,"/scratch/halstead/t/tedmonds/Data/femtoAnalysis/%.1fGeV_Run%i/output/output%i.root",m_Energy,m_RunNumber,m_jobNum);
	// sprintf(outputDir,"/home/tedmonds/Analysis/CME/femtoTreeAnalysis/output%i.root",m_jobNum);

	m_writeFile = new TFile(outputDir,"RECREATE");

	TChain *m_Chain = new TChain("femtoDstTree");

	m_file->GetObject("femtoDstTree",m_tree);

    DeclareHistograms();

    int addPos = jobNum*numFiles; // starting position

	char chainList[512];
	// for(int i = 0; i < 1000; i++)
	// for(int i = 0; i < numJobs; i++)
	for(addPos; addPos < (jobNum+1)*numFiles; addPos++)
	{
    //if(addPos>=numJobs) continue;
		// sprintf(chainList,"/scratch/halstead/t/tedmonds/Data/femtoDst/%.1fGeV_Run%i/femtoDst%.1f_%i.root",energy,runNum,energy,addPos);
		// sprintf(chainList,"/scratch/halstead/t/tedmonds/Data/femtoDst/%.1fGeV_Run%iv2/%.1fGeV_Run%i/femtoDst%.1f_%i.root",energy,runNum,energy,runNum,energy,addPos);
		sprintf(chainList,"/scratch/halstead/t/tedmonds/Data/femtoDst/%.1fGeV_Run%i/output/femtoDst%.1f_%i.root",energy,runNum,energy,addPos);

        if(skipVals[addPos]) continue;
        
        cout << chainList << endl;
        TFile *tfTemp = new TFile(chainList);
		if(!tfTemp->IsZombie() ) m_Chain->Add(chainList);
        delete tfTemp;    
	}
    chainExist = true;

	cout << "chain created"<< endl;

	int nPlus;
	int nMinus;
	int nfemCen;
	float nfVx;
	float nfVy;
	float nfVz;
	int nPeta[m_numEtaBins]; // old variable naming that I no longer like due to later discussions
	int nMeta[m_numEtaBins];
	float nCosPhiP[m_numEtaBins];
	float nCosPhiM[m_numEtaBins];
	float nSinPhiP[m_numEtaBins];
	float nSinPhiM[m_numEtaBins];
	float nCos2PhiP[m_numEtaBins];
	float nCos2PhiM[m_numEtaBins];
	float nSin2PhiP[m_numEtaBins];
	float nSin2PhiM[m_numEtaBins];

    int nPlusAll[m_numEtaBins];
    int nMinusAll[m_numEtaBins];
	float nCosPhiPAll[m_numEtaBins];
	float nCosPhiMAll[m_numEtaBins];
	float nSinPhiPAll[m_numEtaBins];
	float nSinPhiMAll[m_numEtaBins];
	float nCos2PhiPAll[m_numEtaBins];
	float nCos2PhiMAll[m_numEtaBins];
	float nSin2PhiPAll[m_numEtaBins];
	float nSin2PhiMAll[m_numEtaBins];

    int nPlusPi[m_numEtaBins];
    int nMinusPi[m_numEtaBins];
	float nCosPhiPPi[m_numEtaBins];
	float nCosPhiMPi[m_numEtaBins];
	float nSinPhiPPi[m_numEtaBins];
	float nSinPhiMPi[m_numEtaBins];
	float nCos2PhiPPi[m_numEtaBins];
	float nCos2PhiMPi[m_numEtaBins];
	float nSin2PhiPPi[m_numEtaBins];
	float nSin2PhiMPi[m_numEtaBins];

	if(chainExist) //m_tree = (TTree*)m_Chain->Get("femtoDstTree"); 
	{
		m_Chain->SetBranchAddress("totalPlus",&nPlus);
		m_Chain->SetBranchAddress("totalMinus",&nMinus);
		m_Chain->SetBranchAddress("femtoCent",&nfemCen);
		m_Chain->SetBranchAddress("femtoVertexX",&nfVx);
		m_Chain->SetBranchAddress("femtoVertexY",&nfVy);
		m_Chain->SetBranchAddress("femtoVertexZ",&nfVz);

        m_Chain->SetBranchAddress("nPlus",nPeta);
		m_Chain->SetBranchAddress("nMinus",nMeta);
		m_Chain->SetBranchAddress("avgCosPhiP",nCosPhiP);
		m_Chain->SetBranchAddress("avgCosPhiM",nCosPhiM);
		m_Chain->SetBranchAddress("avgSinPhiP",nSinPhiP);
		m_Chain->SetBranchAddress("avgSinPhiM",nSinPhiM);
		m_Chain->SetBranchAddress("avgCos2PhiP",nCos2PhiP);
		m_Chain->SetBranchAddress("avgCos2PhiM",nCos2PhiM);
		m_Chain->SetBranchAddress("avgSin2PhiP",nSin2PhiP);
		m_Chain->SetBranchAddress("avgSin2PhiM",nSin2PhiM);

        m_Chain->SetBranchAddress("nPlusRefAll",nPlusAll);
		m_Chain->SetBranchAddress("nMinusRefAll",nMinusAll);
		m_Chain->SetBranchAddress("avgCosPhiPRefAll",nCosPhiPAll);
		m_Chain->SetBranchAddress("avgCosPhiMRefAll",nCosPhiMAll);
		m_Chain->SetBranchAddress("avgSinPhiPRefAll",nSinPhiPAll);
		m_Chain->SetBranchAddress("avgSinPhiMRefAll",nSinPhiMAll);
		m_Chain->SetBranchAddress("avgCos2PhiPRefAll",nCos2PhiPAll);
		m_Chain->SetBranchAddress("avgCos2PhiMRefAll",nCos2PhiMAll);
		m_Chain->SetBranchAddress("avgSin2PhiPRefAll",nSin2PhiPAll);
		m_Chain->SetBranchAddress("avgSin2PhiMRefAll",nSin2PhiMAll);

        m_Chain->SetBranchAddress("nPlusRefPi",nPlusPi);
		m_Chain->SetBranchAddress("nMinusRefPi",nMinusPi);
		m_Chain->SetBranchAddress("avgCosPhiPRefPi",nCosPhiPPi);
		m_Chain->SetBranchAddress("avgCosPhiMRefPi",nCosPhiMPi);
		m_Chain->SetBranchAddress("avgSinPhiPRefPi",nSinPhiPPi);
		m_Chain->SetBranchAddress("avgSinPhiMRefPi",nSinPhiMPi);
		m_Chain->SetBranchAddress("avgCos2PhiPRefPi",nCos2PhiPPi);
		m_Chain->SetBranchAddress("avgCos2PhiMRefPi",nCos2PhiMPi);
		m_Chain->SetBranchAddress("avgSin2PhiPRefPi",nSin2PhiPPi);
		m_Chain->SetBranchAddress("avgSin2PhiMRefPi",nSin2PhiMPi);

	}

	if(!chainExist)// m_tree = (TTree*)m_file->Get("femtoDstTree");
	{
		m_tree->SetBranchAddress("totalPlus",&nPlus);
		m_tree->SetBranchAddress("totalMinus",&nMinus);
		m_tree->SetBranchAddress("femtoCent",&nfemCen);
		m_tree->SetBranchAddress("femtoVertexX",&nfVx);
		m_tree->SetBranchAddress("femtoVertexY",&nfVy);
		m_tree->SetBranchAddress("femtoVertexZ",&nfVz);
		m_tree->SetBranchAddress("nPlus",nPeta);
		m_tree->SetBranchAddress("nMinus",nMeta);
		m_tree->SetBranchAddress("avgCosPhiP",nCosPhiP);
		m_tree->SetBranchAddress("avgCosPhiM",nCosPhiM);
		m_tree->SetBranchAddress("avgSinPhiP",nSinPhiP);
		m_tree->SetBranchAddress("avgSinPhiM",nSinPhiM);
		m_tree->SetBranchAddress("avgCos2PhiP",nCos2PhiP);
		m_tree->SetBranchAddress("avgCos2PhiM",nCos2PhiM);
		m_tree->SetBranchAddress("avgSin2PhiP",nSin2PhiP);
		m_tree->SetBranchAddress("avgSin2PhiM",nSin2PhiM);
	}
	
	cout << "branches set"<< endl;

	vector<int> pushInt;
	vector<float> pushDouble;

	// declaration of variables for filling values on initial comb through of the tree

	int allPlus = 0;
	int allMinus = 0;

    // don't feel the need for these anymore, as I don't think this is an appropriate way to calculate v2
    // maybe it was for delta gamma

	// event averaged for each bin
	//float nPlusAvg[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//float nMinusAvg[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//int nPlusTotal[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//int nMinusTotal[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//float cosPavg[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//float cosMavg[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//float sinPavg[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//float sinMavg[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//float cos2Pavg[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//float cos2Mavg[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//float sin2Pavg[m_numEtaBins] = {0,0,0,0,0,0,0,0};
	//float sin2Mavg[m_numEtaBins] = {0,0,0,0,0,0,0,0};

	int fillNum;
	int numEventsInFile;
	cout << "chain creation" << endl;
	if(chainExist)
	{
		cout << "chain exists" << endl;
		numEventsInFile = m_Chain->GetEntries();	
	}
	else
	{
		numEventsInFile = m_tree->GetEntries();
	}

	//int i = 0;

	cout << numEventsInFile << endl;
	
    if(numEventsInFile == 0) 
    {
        cout << "No events in file. Ending program" << endl;
        return;
    }

	// while(m_Reader.Next())
	for(int i = 0; i < numEventsInFile; i++)
	{
		if(chainExist)
		{ 
			m_Chain->GetEntry(i);
		}
		else 
		{
			m_tree->GetEntry(i);
		}
		m_EventNum = i;
		m_totalPlus = nPlus;
		m_totalMinus = nMinus;
		m_femtoCent = nfemCen;
		m_femtoVertexX = nfVx;
		m_femtoVertexY = nfVy;
		m_femtoVertexZ = nfVz;

		//fillNum = *nfemCen-1;
		fillNum = nfemCen-1;

		m_numEventsPerCent[fillNum] += 1;

		if(fillNum<0) cerr << "ERROR IN STORING CENTRALITY NUMBER" << endl;

		for(int j = 0; j < m_numEtaBins; j++)
		{
			// these top few variables are mostly for book keeping purposes
			m_nPlus[j] = nPeta[j];
			m_nMinus[j] = nMeta[j];

			m_avgCosPhiP[j] = nCosPhiP[j];
			m_avgCosPhiM[j] = nCosPhiM[j];
			m_avgSinPhiP[j] = nSinPhiP[j];
			m_avgSinPhiM[j] = nSinPhiM[j];
			m_avgCos2PhiP[j] = nCos2PhiP[j];
			m_avgCos2PhiM[j] = nCos2PhiM[j];
			m_avgSin2PhiP[j] = nSin2PhiP[j];
			m_avgSin2PhiM[j] = nSin2PhiM[j];

			m_nPlusRefAll[j] = nPlusAll[j];
			m_nMinusRefAll[j] = nMinusAll[j];
			
            m_avgCosPhiPRefAll[j] = nCosPhiPAll[j];
			m_avgCosPhiMRefAll[j] = nCosPhiMAll[j];
			m_avgSinPhiPRefAll[j] = nSinPhiPAll[j];
			m_avgSinPhiMRefAll[j] = nSinPhiMAll[j];
			m_avgCos2PhiPRefAll[j] = nCos2PhiPAll[j];
			m_avgCos2PhiMRefAll[j] = nCos2PhiMAll[j];
			m_avgSin2PhiPRefAll[j] = nSin2PhiPAll[j];
			m_avgSin2PhiMRefAll[j] = nSin2PhiMAll[j];

			m_nPlusRefPi[j] = nPlusPi[j];
			m_nMinusRefPi[j] = nMinusPi[j];
			
            m_avgCosPhiPRefPi[j] = nCosPhiPPi[j];
			m_avgCosPhiMRefPi[j] = nCosPhiMPi[j];
			m_avgSinPhiPRefPi[j] = nSinPhiPPi[j];
			m_avgSinPhiMRefPi[j] = nSinPhiMPi[j];
			m_avgCos2PhiPRefPi[j] = nCos2PhiPPi[j];
			m_avgCos2PhiMRefPi[j] = nCos2PhiMPi[j];
			m_avgSin2PhiPRefPi[j] = nSin2PhiPPi[j];
			m_avgSin2PhiMRefPi[j] = nSin2PhiMPi[j];

            // 
            
			// fill event averaged values for each bin

			//nPlusTotal[j] += nPeta[j];
			//nMinusTotal[j] += nMeta[j];
			//cosPavg[j] += nCosPhiP[j]*nPeta[j];
			//cosMavg[j] += nCosPhiM[j]*nMeta[j];
			//sinPavg[j] += nSinPhiP[j]*nPeta[j];
			//sinMavg[j] += nSinPhiM[j]*nMeta[j];
			//cos2Pavg[j] += nCos2PhiP[j]*nPeta[j];
			//cos2Mavg[j] += nCos2PhiM[j]*nMeta[j];
			//sin2Pavg[j] += nSin2PhiP[j]*nPeta[j];
			//sin2Mavg[j] += nSin2PhiM[j]*nMeta[j];

			// centrality cut variables
			//nPlusTotalCent[*nfemCen][j] += nPeta[j];
			//nPlusTotalCent[fillNum][j] += nPeta[j];
			////nMinusTotalCent[*nfemCen][j] += nMeta[j];
			//nMinusTotalCent[fillNum][j] += nMeta[j];

			//cosPavgCent[fillNum][j] += nCosPhiP[j]*nPeta[j];
			//cosMavgCent[fillNum][j] += nCosPhiM[j]*nMeta[j];
			//sinPavgCent[fillNum][j] += nSinPhiP[j]*nPeta[j];
			//sinMavgCent[fillNum][j] += nSinPhiM[j]*nMeta[j];
			//cos2PavgCent[fillNum][j] += nCos2PhiP[j]*nPeta[j];
			//cos2MavgCent[fillNum][j] += nCos2PhiM[j]*nMeta[j];
			//sin2PavgCent[fillNum][j] += nSin2PhiP[j]*nPeta[j];
			//sin2MavgCent[fillNum][j] += nSin2PhiM[j]*nMeta[j];
			// end centrality cut variables
		}


		// faux progress bar

		if(i%50000==0) printf("num of events so far == %i \n",i);

		// i++;

        v22Calculations();

	} // end of event loop


	m_numEvents = numEventsInFile;

	m_writeFile->Write();

	return;
}

femtoDst::~femtoDst()
{

}

void femtoDst::v22Calculations()
{
    // calculating and filling v22 histograms
    // this is done per event

    double v22PlusRefAll = 0;
    double v22MinusRefAll = 0;
    double v22PlusRefPi = 0;
    double v22MinusRefPi = 0;
    double v22PlusPOI = 0;
    double v22MinusPOI = 0;
    double v22PlusPOIAll = 0;
    double v22MinusPOIAll = 0;
    double v22PlusPOIPi = 0;
    double v22MinusPOIPi = 0;
    double v22PlusAllPOI = 0;
    double v22MinusAllPOI = 0;
    double v22PlusPiPOI = 0;
    double v22MinusPiPOI = 0;

    double v22RefAll = 0;
    double v22RefAllPOIPlus = 0;
    double v22RefAllPOIMinus = 0;
    double v22POIRefAllPlus = 0;
    double v22POIRefAllMinus = 0;

    int nPlusRefAllWest = 0;
    int nMinusRefAllWest = 0;
    int nPlusRefPiWest = 0;
    int nMinusRefPiWest = 0;
    int nPlusPOIWest = 0;
    int nMinusPOIWest = 0;    

    int nPlusRefAllEast = 0;
    int nMinusRefAllEast = 0;
    int nPlusRefPiEast = 0;
    int nMinusRefPiEast = 0;
    int nPlusPOIEast = 0;
    int nMinusPOIEast = 0;

    int nRefAllWest = 0;
    int nRefAllEast = 0;

    double cos2PlusRefAllWest = 0;
    double cos2PlusRefAllEast = 0;
    double cos2MinusRefAllWest = 0;
    double cos2MinusRefAllEast = 0;

    double sin2PlusRefAllWest = 0;
    double sin2PlusRefAllEast = 0;
    double sin2MinusRefAllWest = 0;
    double sin2MinusRefAllEast = 0;

    double cos2PlusRefPiWest = 0;
    double cos2PlusRefPiEast = 0;
    double cos2MinusRefPiWest = 0;
    double cos2MinusRefPiEast = 0;

    double sin2PlusRefPiWest = 0;
    double sin2PlusRefPiEast = 0;
    double sin2MinusRefPiWest = 0;
    double sin2MinusRefPiEast = 0;

    double cos2PlusPOIWest = 0;
    double cos2PlusPOIEast = 0;
    double cos2MinusPOIWest = 0;
    double cos2MinusPOIEast = 0;

    double sin2PlusPOIWest = 0;
    double sin2PlusPOIEast = 0;
    double sin2MinusPOIWest = 0;
    double sin2MinusPOIEast = 0;
    
    double cos2RefAllWest = 0;
    double sin2RefAllWest = 0;
    double cos2RefAllEast = 0;
    double sin2RefAllEast = 0;

    double Ach = 0;
    double nP = 0;
    double nM = 0;
    double sum = 0;
    double diff = 0;

    int currentCent = m_femtoCent - 1;

    // Ach variables
	nP = m_totalPlus;
	nM = m_totalMinus;
	sum = nP + nM;
	diff = nP - nM;
	m_nPvsnM->Fill(nM,nP);
	m_nPminnMvsnPplunM->Fill(sum,diff);

	Ach = diff/(double)sum;

	m_AchVsnPplunM->Fill(sum,Ach);

    m_Ach = Ach;

    for(int i = 0; i < m_numEtaBins; i++)
    {
        if(i == 3 || i == 4) continue;

            // sub event plane 1 (west)
            if(i<=3)
            {
  
                // variables for v22 calculation mixing the planes 
                nPlusRefAllWest += m_nPlusRefAll[i];
                nMinusRefAllWest += m_nMinusRefAll[i];
                nPlusRefPiWest += m_nPlusRefPi[i];
                nMinusRefPiWest += m_nMinusRefPi[i];
                nPlusPOIWest += m_nPlus[i];
                nMinusPOIWest += m_nMinus[i];

                cos2PlusRefAllWest += m_nPlusRefAll[i]*m_avgCos2PhiPRefAll[i];
                cos2MinusRefAllWest += m_nMinusRefAll[i]*m_avgCos2PhiMRefAll[i];
                sin2PlusRefAllWest += m_nPlusRefAll[i]*m_avgSin2PhiPRefAll[i];
                sin2MinusRefAllWest += m_nMinusRefAll[i]*m_avgSin2PhiMRefAll[i];

                cos2PlusRefPiWest += m_nPlusRefPi[i]*m_avgCos2PhiPRefPi[i];
                cos2MinusRefPiWest += m_nMinusRefPi[i]*m_avgCos2PhiMRefPi[i];
                sin2PlusRefPiWest += m_nPlusRefPi[i]*m_avgSin2PhiPRefPi[i];
                sin2MinusRefPiWest += m_nMinusRefPi[i]*m_avgSin2PhiMRefPi[i];

                cos2PlusPOIWest += m_nPlus[i]*m_avgCos2PhiP[i];
                cos2MinusPOIWest += m_nMinus[i]*m_avgCos2PhiM[i];
                sin2PlusPOIWest += m_nPlus[i]*m_avgSin2PhiP[i];
                sin2MinusPOIWest += m_nMinus[i]*m_avgSin2PhiM[i];

                nRefAllWest += m_nPlusRefAll[i];
                nRefAllWest += m_nMinusRefAll[i];

                cos2RefAllWest += m_nPlusRefAll[i]*m_avgCos2PhiP[i];
                cos2RefAllWest += m_nMinusRefAll[i]*m_avgCos2PhiM[i];
                sin2RefAllWest += m_nPlusRefAll[i]*m_avgSin2PhiP[i];
                sin2RefAllWest += m_nMinusRefAll[i]*m_avgSin2PhiM[i];
                 

            }
            // sub event plane 2 (east)
            if(i>3)
            {
                // variables for v22 calculation mixing the planes 
                nPlusRefAllEast += m_nPlusRefAll[i];
                nMinusRefAllEast += m_nMinusRefAll[i];
                nPlusRefPiEast += m_nPlusRefPi[i];
                nMinusRefPiEast += m_nMinusRefPi[i];
                nPlusPOIEast += m_nPlus[i];
                nMinusPOIEast += m_nMinus[i];

                cos2PlusRefAllEast += m_nPlusRefAll[i]*m_avgCos2PhiPRefAll[i];
                cos2MinusRefAllEast += m_nMinusRefAll[i]*m_avgCos2PhiMRefAll[i];
                sin2PlusRefAllEast += m_nPlusRefAll[i]*m_avgSin2PhiPRefAll[i];
                sin2MinusRefAllEast += m_nMinusRefAll[i]*m_avgSin2PhiMRefAll[i];

                cos2PlusRefPiEast += m_nPlusRefPi[i]*m_avgCos2PhiPRefPi[i];
                cos2MinusRefPiEast += m_nMinusRefPi[i]*m_avgCos2PhiMRefPi[i];
                sin2PlusRefPiEast += m_nPlusRefPi[i]*m_avgSin2PhiPRefPi[i];
                sin2MinusRefPiEast += m_nMinusRefPi[i]*m_avgSin2PhiMRefPi[i];

                cos2PlusPOIEast += m_nPlus[i]*m_avgCos2PhiP[i];
                cos2MinusPOIEast += m_nMinus[i]*m_avgCos2PhiM[i];
                sin2PlusPOIEast += m_nPlus[i]*m_avgSin2PhiP[i];
                sin2MinusPOIEast += m_nMinus[i]*m_avgSin2PhiM[i];

                nRefAllEast += m_nPlusRefAll[i];
                nRefAllEast += m_nMinusRefAll[i];

                cos2RefAllEast += m_nPlusRefAll[i]*m_avgCos2PhiP[i];
                cos2RefAllEast += m_nMinusRefAll[i]*m_avgCos2PhiM[i];
                sin2RefAllEast += m_nPlusRefAll[i]*m_avgSin2PhiP[i];
                sin2RefAllEast += m_nMinusRefAll[i]*m_avgSin2PhiM[i];
 
            }


    }// eta bin loop

    // this v22 does not have any corrections
    v22PlusRefAll = cos2PlusRefAllWest*cos2PlusRefAllEast + sin2PlusRefAllWest*sin2PlusRefAllEast;
    v22MinusRefAll = cos2MinusRefAllWest*cos2MinusRefAllEast + sin2MinusRefAllWest*sin2MinusRefAllEast;
    v22PlusRefPi = cos2PlusRefPiWest*cos2PlusRefPiEast + sin2PlusRefPiWest*sin2PlusRefPiEast;
    v22MinusRefPi = cos2MinusRefPiWest*cos2MinusRefPiEast + sin2MinusRefPiWest*sin2MinusRefPiEast;
    v22PlusPOI = cos2PlusPOIWest*cos2PlusPOIEast + sin2PlusPOIWest*sin2PlusPOIEast;
    v22MinusPOI = cos2MinusPOIWest*cos2MinusPOIEast + sin2MinusPOIWest*sin2MinusPOIEast;
    v22RefAll = cos2RefAllWest*cos2RefAllEast + sin2RefAllWest*sin2RefAllEast;
    // west POI
    v22PlusPOIAll = cos2PlusPOIWest*cos2PlusRefAllEast + sin2PlusPOIWest*sin2PlusRefAllEast;
    v22MinusPOIAll = cos2MinusPOIWest*cos2MinusRefAllEast + sin2MinusPOIWest*sin2MinusRefAllEast;
    v22PlusPOIPi = cos2PlusPOIWest*cos2PlusRefPiEast + sin2PlusPOIWest*sin2PlusRefPiEast;
    v22MinusPOIPi = cos2MinusPOIWest*cos2MinusRefPiEast + sin2MinusPOIWest*sin2MinusRefPiEast;

    v22POIRefAllPlus = cos2PlusPOIWest*cos2RefAllEast + sin2PlusPOIWest*sin2RefAllEast;
    v22POIRefAllMinus = cos2MinusPOIWest*cos2RefAllEast + sin2MinusPOIWest*sin2RefAllEast;
    // East POI
    v22PlusAllPOI = cos2PlusRefAllWest*cos2PlusPOIEast + sin2PlusRefAllWest*sin2PlusPOIEast;
    v22MinusAllPOI = cos2MinusRefAllWest*cos2MinusPOIEast + sin2MinusRefAllWest*sin2MinusPOIEast;
    v22PlusPiPOI = cos2PlusRefPiWest*cos2PlusPOIEast + sin2PlusRefPiWest*sin2PlusPOIEast;
    v22MinusPiPOI = cos2MinusRefPiWest*cos2MinusPOIEast + sin2MinusRefPiWest*sin2MinusPOIEast;

    v22RefAllPOIPlus = cos2RefAllWest*cos2PlusPOIEast + sin2RefAllWest*sin2PlusPOIEast;
    v22RefAllPOIMinus = cos2RefAllWest*cos2MinusPOIEast + sin2RefAllWest*sin2MinusPOIEast;
    // normalizing v22
    if( nPlusRefAllWest != 0 && nPlusRefAllEast != 0) v22PlusRefAll = v22PlusRefAll/(nPlusRefAllWest*nPlusRefAllEast); 
    if( nMinusRefAllWest != 0 && nMinusRefAllEast != 0 ) v22MinusRefAll = v22MinusRefAll/(nMinusRefAllWest*nMinusRefAllEast);
    if( nPlusRefPiWest != 0 && nPlusRefPiEast != 0 ) v22PlusRefPi = v22PlusRefPi/(nPlusRefPiWest*nPlusRefPiEast);
    if( nMinusRefPiWest != 0 && nMinusRefPiEast != 0 ) v22MinusRefPi = v22MinusRefPi/(nMinusRefPiWest*nMinusRefPiEast);
    if( nPlusPOIWest != 0 && nPlusPOIEast != 0 ) v22PlusPOI = v22PlusPOI/(nPlusPOIWest*nPlusPOIEast);
    if( nMinusPOIWest != 0 && nMinusPOIEast != 0 ) v22MinusPOI = v22MinusPOI/(nMinusPOIWest*nMinusPOIEast);
    if( nRefAllEast != 0 && nRefAllWest != 0 ) v22RefAll = v22RefAll/(nRefAllEast*nRefAllWest);
    // west POI
    if( nPlusPOIWest != 0 && nPlusRefAllEast != 0 ) v22PlusPOIAll = v22PlusPOIAll/(nPlusPOIWest*nPlusRefAllEast); 
    if( nMinusPOIWest != 0 && nMinusRefAllEast != 0 ) v22MinusPOIAll = v22MinusPOIAll/(nMinusPOIWest*nMinusRefAllEast);
    if( nPlusPOIWest != 0 && nPlusRefPiEast != 0 ) v22PlusPOIPi = v22PlusPOIPi/(nPlusPOIWest*nPlusRefPiEast);
    if( nMinusPOIWest != 0 && nMinusRefPiEast != 0 ) v22MinusPOIPi = v22MinusPOIPi/(nMinusPOIWest*nMinusRefPiEast);
    if( nPlusPOIWest != 0 && nRefAllEast != 0 ) v22POIRefAllPlus = v22POIRefAllPlus/(nPlusPOIWest*nRefAllEast);
    if( nMinusPOIWest != 0 && nRefAllEast != 0 ) v22POIRefAllMinus = v22POIRefAllMinus/(nMinusPOIWest*nRefAllEast);
    // East POI
    if( nPlusRefAllWest != 0 && nPlusPOIEast != 0 ) v22PlusAllPOI = v22PlusAllPOI/(nPlusRefAllWest*nPlusPOIEast);
    if( nMinusRefAllWest != 0 && nMinusPOIEast != 0 ) v22MinusAllPOI = v22MinusAllPOI/(nMinusRefAllWest*nMinusPOIEast);
    if( nPlusRefPiWest != 0 && nPlusPOIEast != 0 ) v22PlusPiPOI = v22PlusPiPOI/(nPlusRefPiWest*nPlusPOIEast);
    if( nMinusRefPiWest != 0 && nMinusPOIEast != 0 ) v22MinusPiPOI = v22MinusPiPOI/(nMinusRefPiWest*nMinusPOIEast);
    if( nRefAllWest != 0 && nPlusPOIEast != 0 ) v22RefAllPOIPlus = v22RefAllPOIPlus/(nRefAllWest*nPlusPOIEast);
    if( nRefAllWest != 0 && nMinusPOIEast != 0 ) v22RefAllPOIMinus = v22RefAllPOIMinus/(nRefAllWest*nMinusPOIEast);
    // v22 filling, reference planes and POI
    m_v22vsAchPlusRefAll[currentCent]->Fill(m_Ach,v22PlusRefAll,nPlusRefAllWest*nPlusRefAllEast);
    m_v22vsAchPlusRefAllUnw[currentCent]->Fill(m_Ach,v22PlusRefAll,1);
    m_v22vsAchMinusRefAll[currentCent]->Fill(m_Ach,v22MinusRefAll,nMinusRefAllWest*nMinusRefAllEast);
    m_v22vsAchMinusRefAllUnw[currentCent]->Fill(m_Ach,v22MinusRefAll,1);
    m_v22vsAchPlusRefPi[currentCent]->Fill(m_Ach,v22PlusRefPi,nPlusRefPiWest*nPlusRefPiEast);
    m_v22vsAchPlusRefPiUnw[currentCent]->Fill(m_Ach,v22PlusRefPi,1);
    m_v22vsAchMinusRefPi[currentCent]->Fill(m_Ach,v22MinusRefPi,nMinusRefPiWest*nMinusRefPiEast);
    m_v22vsAchMinusRefPiUnw[currentCent]->Fill(m_Ach,v22MinusRefPi,1);
    m_v22vsAchPlusPOI[currentCent]->Fill(m_Ach,v22PlusPiPOI,nPlusPOIWest*nPlusPOIEast); 
    m_v22vsAchPlusPOIUnw[currentCent]->Fill(m_Ach,v22PlusPOI,1);
    m_v22vsAchMinusPOI[currentCent]->Fill(m_Ach,v22MinusPOI,nMinusPOIWest*nMinusPOIEast);
    m_v22vsAchMinusPOIUnw[currentCent]->Fill(m_Ach,v22MinusPOI,1);

    m_v22vsAchRefAll[currentCent]->Fill(m_Ach,v22RefAll,nRefAllWest*nRefAllEast);
    m_v22vsAchRefAllUnw[currentCent]->Fill(m_Ach,v22RefAll,1);

    // v22 filling for mixed planes, west interest plane
    m_v22vsAchPlusPOIAll[currentCent]->Fill(m_Ach,v22PlusPOIAll,nPlusPOIWest*nPlusRefAllEast);
    m_v22vsAchPlusPOIAllUnw[currentCent]->Fill(m_Ach,v22PlusPOIAll,1);
    m_v22vsAchMinusPOIAll[currentCent]->Fill(m_Ach,v22MinusPOIAll,nMinusPOIWest*nMinusRefAllEast);
    m_v22vsAchMinusPOIAllUnw[currentCent]->Fill(m_Ach,v22MinusPOIAll,1);
    
    m_v22vsAchPlusPOIPi[currentCent]->Fill(m_Ach,v22PlusPOIPi,nPlusPOIWest*nPlusRefPiEast);
    m_v22vsAchPlusPOIPiUnw[currentCent]->Fill(m_Ach,v22PlusPOIPi,1);
    m_v22vsAchMinusPOIPi[currentCent]->Fill(m_Ach,v22MinusPOIPi,nMinusPOIWest*nMinusRefPiEast);
    m_v22vsAchMinusPOIPiUnw[currentCent]->Fill(m_Ach,v22MinusPOIPi,1);

    m_v22vsAchPlusPOIRefAll[currentCent]->Fill(m_Ach,v22POIRefAllPlus,nPlusPOIWest*nRefAllEast);
    m_v22vsAchPlusPOIRefAllUnw[currentCent]->Fill(m_Ach,v22POIRefAllPlus,1);
    m_v22vsAchMinusPOIRefAll[currentCent]->Fill(m_Ach,v22POIRefAllMinus,nMinusPOIWest*nRefAllEast);
    m_v22vsAchMinusPOIRefAllUnw[currentCent]->Fill(m_Ach,v22POIRefAllMinus,1);

    // v22 fillining for mixed planes, east interest plane
    m_v22vsAchPlusAllPOI[currentCent]->Fill(m_Ach,v22PlusAllPOI,nPlusRefPiWest*nPlusPOIEast);
    m_v22vsAchPlusAllPOIUnw[currentCent]->Fill(m_Ach,v22PlusAllPOI,1);
    m_v22vsAchMinusAllPOI[currentCent]->Fill(m_Ach,v22MinusAllPOI,nMinusRefAllWest*nMinusPOIEast);
    m_v22vsAchMinusAllPOIUnw[currentCent]->Fill(m_Ach,v22MinusAllPOI,1);
    
    m_v22vsAchPlusPiPOI[currentCent]->Fill(m_Ach,v22PlusPiPOI,nPlusRefPiWest*nPlusPOIEast);
    m_v22vsAchPlusPiPOIUnw[currentCent]->Fill(m_Ach,v22PlusPiPOI,1);
    m_v22vsAchMinusPiPOI[currentCent]->Fill(m_Ach,v22MinusPiPOI,nMinusRefPiWest*nMinusPOIEast);
    m_v22vsAchMinusPiPOIUnw[currentCent]->Fill(m_Ach,v22MinusPiPOI,1);

    m_v22vsAchPlusRefAllPOI[currentCent]->Fill(m_Ach,v22RefAllPOIPlus,nPlusPOIEast*nRefAllWest);
    m_v22vsAchPlusRefAllPOIUnw[currentCent]->Fill(m_Ach,v22RefAllPOIPlus,1);
    m_v22vsAchMinusRefAllPOI[currentCent]->Fill(m_Ach,v22RefAllPOIMinus,nMinusPOIEast*nRefAllWest);
    m_v22vsAchMinusRefAllPOIUnw[currentCent]->Fill(m_Ach,v22RefAllPOIMinus,1);

    // end of v22 plane mixing

    m_hPNumPairsRefAll->Fill(nPlusRefAllWest*nPlusRefAllEast);
    m_hPNumPairsRefPi->Fill(nPlusRefPiWest*nPlusRefPiEast);

    m_hPNumPairsPOIAll->Fill(nPlusRefAllWest*nPlusPOIEast);
    m_hPNumPairsPOIAll->Fill(nPlusPOIWest*nPlusRefAllEast);

    m_hPNumPairsPOIPi->Fill(nPlusRefPiWest*nPlusPOIEast);
    m_hPNumPairsPOIPi->Fill(nPlusPOIWest*nPlusRefPiEast);

    m_hMNumPairsRefAll->Fill(nMinusRefAllWest*nMinusRefAllEast);
    m_hMNumPairsRefPi->Fill(nMinusRefPiWest*nMinusRefPiEast);

    m_hMNumPairsPOIAll->Fill(nMinusRefAllWest*nMinusPOIEast);
    m_hMNumPairsPOIAll->Fill(nMinusPOIWest*nMinusRefAllEast);

    m_hMNumPairsPOIPi->Fill(nMinusRefPiWest*nMinusPOIEast);
    m_hMNumPairsPOIPi->Fill(nMinusPOIWest*nMinusRefPiEast);

    // m_hcentrality->Fill(-1);
    // m_hcentrality->Fill(0);
    m_hcentrality->Fill(m_femtoCent);


    return;
}

void femtoDst::DeclareHistograms()
{
    // many of these might be unused now
    char centralities[m_numCentralities][256] = {
        {"70 - 80%"},
        {"60 - 70%"},
        {"50 - 60%"},
        {"40 - 50%"},
        {"30 - 40%"},
        {"20 - 30%"},
        {"10 - 20%"},
        {"5 - 10%"},
        {"0 - 5%"},
    };

    cout << "declaring hists" << endl;

    m_hcentrality = new TH1D("hCent","Events in centralites",60,-1,10);

    m_hPNumPairsRefAll = new TH1D("hPNumPairsAll","Number of (+) pairs of all reference particles",40001,0,40000);
    m_hPNumPairsRefPi = new TH1D("hPNumPairsPi","Number of (+) pairs of pion reference particles",40001,0,40000);
    m_hPNumPairsPOIAll = new TH1D("hPNumPairsPOIAll","Number of (+) pairs between poi and all",40001,0,40000);
    m_hPNumPairsPOIPi = new TH1D("hPNumPairsPi","Number of (+) pairs between poi and #pi",40001,0,40000);

    m_hMNumPairsRefAll = new TH1D("hMNumPairsAll","Number of (-) pairs of all reference particles",40001,0,40000);
    m_hMNumPairsRefPi = new TH1D("hMNumPairsPi","Number of (-) pairs of pion reference particles",40001,0,40000);
    m_hMNumPairsPOIAll = new TH1D("hMNumPairsPOIAll","Number of (-) pairs between poi and all",40001,0,40000);
    m_hMNumPairsPOIPi = new TH1D("hMNumPairsPi","Number of (-) pairs between poi and #pi",40001,0,40000);


    // need to mess with the binning of v2 a bit more
	m_v2vsEtaPlus = new TH2D("hist1","v2^{2}_{+}{2} vs Eta",8,-1,1,500,-1,1); // y bins are v2, will likely need much more work
	m_v2vsEtaMinus = new TH2D("hist2","v2^{2}_{-}{2} vs Eta",8,-1,1,500,-1,1); 
	m_v2vsEtaPlusUnweighted = new TH2D("hist3","v2^{2}_{+}{2} unweighted vs Eta",8,-1,1,500,-1,1); 
	m_v2vsEtaMinusUnweighted = new TH2D("hist4","v2^{2}_{-}{2} unweighted vs Eta",8,-1,1,500,-1,1); 
	m_v2vsEtaPlusCorrected = new TH2D("hist5","v2^{2}_{+}{2} vs Eta corrected",8,-1,1,500,-1,1);
	m_v2vsEtaMinusCorrected = new TH2D("hist6","v2^{2}_{-}{2} vs Eta corrected",8,-1,1,500,-1,1);

	m_nPvsnM = new TH2D("nPvsnM","N_{+} vs N_{-}",100,0,100,100,0,100);
	m_nPminnMvsnPplunM = new TH2D("mnPminnM","N_{+} - N_{-} vs N_{+} + N_{-}",200,0,200,200,-100,100); 
	m_AchVsnPplunM = new TH2D("achvsnpnm","A_{ch} vs (N_{+} + N_{-})",200,0,200,50,-0.5,0.5);

	m_v2PlusVsAch = new TH2D("hist7","v2^{2}_{+}{2} vs Ach",50,-0.5,0.5,500,-1,1);
	m_v2MinusVsAch = new TH2D("hist8","v2^{2}_{-}{2} vs Ach",50,-0.5,0.5,500,-1,1);

	m_v2PlusVsAchWeighted = new TH2D("hist10","v2^{2}_{+}{2} vs Ach Weighted",50,-0.5,0.5,500,-1,1); 
	m_v2MinusVsAchWeighted = new TH2D("hist11","v2^{2}_{-}{2} vs Ach Weighted",50,-0.5,0.5,500,-1,1);

	// v2 wrt and CMW aren't being used because they are incorrect 
	m_v2PlusVsAchwrt = new TH2D("hist12","v2_{+}{2} vs Ach",50,-0.5,0.5,500,-1,1); // Ach for v2 and not v2^2
	m_v2MinusVsAchwrt = new TH2D("hist13","v2_{-}{2} vs Ach",50,-0.5,0.5,500,-1,1);

	m_v2PlusVsAchCMW = new TH2D("hist14","v2_{+}{2} vs Ach CMW comparison",5,-0.1,0.1,500,-1,1); // Ach binned to compare with CMW paper
	m_v2MinusVsAchCMW = new TH2D("hist15","v2_{-}{2} vs Ach CMW comparison",5,-0.1,0.1,500,-1,1);

	m_AchDist = new TH1D("hist9","A_{ch}",50,-0.5,0.5);

	// I'll automate this before I make the rest of the plots
	m_AchVsnPplunMcent[0] = new TH2D("achvsnpnmC1","A_{ch} vs (N_{+} + N_{-}) cent = 70 - 80%",200,0,200,50,-0.5,0.5);
	m_AchVsnPplunMcent[1] = new TH2D("achvsnpnmC2","A_{ch} vs (N_{+} + N_{-}) cent = 60 - 70%",200,0,200,50,-0.5,0.5);
	m_AchVsnPplunMcent[2] = new TH2D("achvsnpnmC3","A_{ch} vs (N_{+} + N_{-}) cent = 50 - 60%",200,0,200,50,-0.5,0.5);
	m_AchVsnPplunMcent[3] = new TH2D("achvsnpnmC4","A_{ch} vs (N_{+} + N_{-}) cent = 40 - 50%",200,0,200,50,-0.5,0.5);
	m_AchVsnPplunMcent[4] = new TH2D("achvsnpnmC5","A_{ch} vs (N_{+} + N_{-}) cent = 30 - 40%",200,0,200,50,-0.5,0.5);
	m_AchVsnPplunMcent[5] = new TH2D("achvsnpnmC6","A_{ch} vs (N_{+} + N_{-}) cent = 20 - 30%",200,0,200,50,-0.5,0.5);
	m_AchVsnPplunMcent[6] = new TH2D("achvsnpnmC7","A_{ch} vs (N_{+} + N_{-}) cent = 10 - 20%",200,0,200,50,-0.5,0.5);
	m_AchVsnPplunMcent[7] = new TH2D("achvsnpnmC8","A_{ch} vs (N_{+} + N_{-}) cent = 5 - 10%",200,0,200,50,-0.5,0.5);
	m_AchVsnPplunMcent[8] = new TH2D("achvsnpnmC9","A_{ch} vs (N_{+} + N_{-}) cent = 0 - 5%",200,0,200,50,-0.5,0.5);
    

    char histoName[256];
    char histoTitle[512];

    for(int i = 0; i < m_numCentralities; i++)
    {
        sprintf(histoName,"v22EPplu%i",i);
        sprintf(histoTitle,"v2^{2}_{+}{2} vs Ach cent = %s",centralities[i]);
        m_v2EventPlanePlus[i] = new TH2D(histoName,histoTitle,50,-0.5,0.5,500,-1,1);

        sprintf(histoName,"v22EPmin%i",i);
        sprintf(histoTitle,"v2^{2}_{-}{2} vs Ach cent = %s",centralities[i]);
        m_v2EventPlaneMinus[i] = new TH2D(histoName,histoTitle,50,-0.5,0.5,500,-1,1);

        sprintf(histoName,"npartsC%i",i+1);
        sprintf(histoTitle,"n particles sub event C vs sub event A at centrality = %s",centralities[i]);
        hNpartsSubEvents[i] = new TH2D(histoName,histoTitle,101,-1,100,101,-1,100);
    }

    hNpluAvsCent = new TH2D("hAnpluCent","N_{+} vs Centrality subevent A",101,0,100,102,-1,100);
    hNpluCvsCent = new TH2D("hCnpluCent","N_{+} vs Centrality subevent C",101,0,100,102,-1,100);
    hNminAvsCent = new TH2D("hAnminCent","N_{-} vs Centrality subevent A",101,0,100,102,-1,100);
    hNminCvsCent = new TH2D("hCnminCent","N_{-} vs Centrality subevent C",101,0,100,102,-1,100);

    char hv22Name[256];
    char hv22Title[256];

    int AchBins = 400;
    double AchMin = -0.5;
    double AchMax = 0.5;
    int v22Bins = 20000;
    double v22Min = -2;
    double v22Max = 2;
    for(int i = 0; i < m_numCentralities; i++)
    {
        sprintf(hv22Name,"hv22RefAllPC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{All +}{2} vs A_{ch} at centrality = %s",centralities[i]);

        m_v22vsAchPlusRefAll[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22RefAllMC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{All -}{2} vs A_{ch} at centrality = %s",centralities[i]);

        m_v22vsAchMinusRefAll[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22RefPiPC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{#pi +}{2} vs A_{ch} at centrality = %s",centralities[i]);

        m_v22vsAchPlusRefPi[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22RefPiMC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{#pi -}{2} vs A_{ch} at centrality = %s",centralities[i]);

        m_v22vsAchMinusRefPi[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22POIPC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{POI +}{2} vs A_{ch} at centrality = %s",centralities[i]);

        m_v22vsAchPlusPOI[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22POIMC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{POI -}{2} vs A_{ch} at centrality = %s",centralities[i]);

        m_v22vsAchMinusPOI[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        // ref and poi mixing
        sprintf(hv22Name,"hv22POIAllPC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s , POI in #eta<0 , Ref has all same sign particles",centralities[i]);

        m_v22vsAchPlusPOIAll[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22POIAllMC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s , POI in #eta<0, Ref has all same sign particles",centralities[i]);

        m_v22vsAchMinusPOIAll[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22POIPiPC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s , POI in #eta<0 , Ref are same sign pions",centralities[i]);

        m_v22vsAchPlusPOIPi[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22POIPiMC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s , POI in #eta<0, Ref are same sign pions",centralities[i]);

        m_v22vsAchMinusPOIPi[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22poirefallPC%i",i+1);
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s POI in #eta<0, Ref are all particles",centralities[i]);
        m_v22vsAchPlusPOIRefAll[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22poirefallMC%i",i+1);
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s POI in #eta<0, Ref are all particles",centralities[i]);
        m_v22vsAchMinusPOIRefAll[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        // flipped poi and ref planes
        sprintf(hv22Name,"hv22AllPOIPC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s , POI in #eta>0 , Ref has all same sign particles",centralities[i]);

        m_v22vsAchPlusAllPOI[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22AllPOIMC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s , POI in #eta>0, Ref has all same sign particles",centralities[i]);

        m_v22vsAchMinusAllPOI[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22PiPOIPC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s , POI in #eta>0 , Ref are same sign pions",centralities[i]);

        m_v22vsAchPlusPiPOI[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22PiPOIMC%i",i+1);     
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s , POI in #eta>0, Ref are same sign pions",centralities[i]);

        m_v22vsAchMinusPiPOI[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
        
        sprintf(hv22Name,"hv22refAllC%i",i+1);
        sprintf(hv22Title,"v^{2}_{All}{2} vs A_{ch} at centrality = %s",centralities[i]);
        m_v22vsAchRefAll[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22refallpoiPC%i",i+1);
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s POI in #eta>0, Ref are all particles",centralities[i]);
        m_v22vsAchPlusRefAllPOI[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22refallpoiMC%i",i+1);
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s POI in #eta>0, Ref are all particles",centralities[i]);
        m_v22vsAchMinusRefAllPOI[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);


        // unweighted versions of the histogram
        sprintf(hv22Name,"hv22RefAllPC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{All +}{2} vs A_{ch} at centrality = %s unweighted",centralities[i]);

        m_v22vsAchPlusRefAllUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22RefAllMC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{All -}{2} vs A_{ch} at centrality = %s unweighted",centralities[i]);

        m_v22vsAchMinusRefAllUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22RefPiPC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{#pi +}{2} vs A_{ch} at centrality = %s unweighted",centralities[i]);

        m_v22vsAchPlusRefPiUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22RefPiMC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{#pi -}{2} vs A_{ch} at centrality = %s unweighted",centralities[i]);

        m_v22vsAchMinusRefPiUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22POIPC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{POI +}{2} vs A_{ch} at centrality = %s unweighted",centralities[i]);

        m_v22vsAchPlusPOIUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22POIMC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{POI -}{2} vs A_{ch} at centrality = %s unweighted",centralities[i]);

        m_v22vsAchMinusPOIUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        // ref and poi mixing
        sprintf(hv22Name,"hv22POIAllPC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s , POI in #eta<0 , Ref has all same sign particles unweighted",centralities[i]);

        m_v22vsAchPlusPOIAllUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22POIAllMC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s , POI in #eta<0, Ref has all same sign particles unweighted",centralities[i]);

        m_v22vsAchMinusPOIAllUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22POIPiPC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s , POI in #eta<0 , Ref are same sign pions unweighted",centralities[i]);

        m_v22vsAchPlusPOIPiUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22POIPiMC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s , POI in #eta<0, Ref are same sign pions unweighted",centralities[i]);

        m_v22vsAchMinusPOIPiUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        // flipped poi and ref planes
        sprintf(hv22Name,"hv22AllPOIPC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s , POI in #eta>0 , Ref has all same sign particles unweighted",centralities[i]);

        m_v22vsAchPlusAllPOIUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22AllPOIMC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s , POI in #eta>0, Ref has all same sign particles unweighted",centralities[i]);

        m_v22vsAchMinusAllPOIUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22PiPOIPC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s , POI in #eta>0 , Ref are same sign pions unweighted",centralities[i]);

        m_v22vsAchPlusPiPOIUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);
 
        sprintf(hv22Name,"hv22PiPOIMC%iu",i+1);     
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s , POI in #eta>0, Ref are same sign pions unweighted",centralities[i]);

        m_v22vsAchMinusPiPOIUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22refAllC%iu",i+1);
        sprintf(hv22Title,"v^{2}_{All}{2} vs A_{ch} at centrality = %s unweighted",centralities[i]);
        m_v22vsAchRefAllUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22poirefallPC%iu",i+1);
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s POI in #eta<0, Ref are all particles unweighted",centralities[i]);
        m_v22vsAchPlusPOIRefAllUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22poirefallMC%iu",i+1);
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s POI in #eta<0, Ref are all particles unweighted",centralities[i]);
        m_v22vsAchMinusPOIRefAllUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22refallpoiPC%iu",i+1);
        sprintf(hv22Title,"v^{2}_{+}{2} vs A_{ch} at centrality = %s POI in #eta>0, Ref are all particles unweighted",centralities[i]);
        m_v22vsAchPlusRefAllPOIUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        sprintf(hv22Name,"hv22refallpoiMC%iu",i+1);
        sprintf(hv22Title,"v^{2}_{-}{2} vs A_{ch} at centrality = %s POI in #eta>0, Ref are all particles unweighted",centralities[i]);
        m_v22vsAchMinusRefAllPOIUnw[i] = new TH2D(hv22Name,hv22Title,AchBins,AchMin,AchMax,v22Bins,v22Min,v22Max);

        // EDIT: upon recommendation from FQ, should book directly the TProfile instead of TH2D

    } 

    cout << "histograms declared!" << endl;

    return;
}
