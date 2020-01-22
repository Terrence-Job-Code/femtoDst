#include "rootheader.h"

// class that reads my tree

// EDIT NEEDED!!!!!!!!!!!!!: may need to rethink how I count total pairs
// I am likely overcounting

#ifndef FEMTODST_H_
#define FEMTODST_H_

//gInterpreter->GenerateDictionary("vector<pair<double, double> >","vector");
//gInterpreter->GenerateDictionary("vector<pair<int, int> >","vector");

using namespace std;

class femtoDst
{
  public:

    femtoDst(TString filePath,int jobNum,float energy, int runNum,bool chainExist=false,int numJobs=100); // must be to root files with femtoDst structure
    ~femtoDst();

    // all of these functions should return one number, for simplicity
    // returning arrays is more difficult
    // maybe I'll change it later for fun

    // for reference
    // centrality number and percentage
    // 9: 0-5% (most central collisions)
    // 8: 5-10%
    // 7: 10-20%
    // 6: 20-30%
    // 5: 30-40%
    // 4: 40-50%
    // 3: 50-60%
    // 2: 60-70%
    // 1: 70-80%

    // these are just values read from the femtoDst file
    long ShowNumEvents() {return m_numEvents;}
    long ShowEventNum(int event) {return m_EventNum;}
    int ShowEventId(int event) {return m_EventId;}
    int ShowCent(int event) {return m_femtoCent;}
    int ShowPosPions(int event) {return m_totalPlus;}
    int ShowMinPions(int event) {return m_totalMinus;}
    float ShowVertexX(int event) {return m_femtoVertexX;}
    float ShowVertexY(int event) {return m_femtoVertexY;}
    float ShowVertexZ(int event) {return m_femtoVertexZ;}
    int ShowNumBins() {return m_numEtaBins;}

    int ShowPosInBin(int event, int bin) {return m_nPlus[bin];}
    int ShowMinInBin(int event, int bin) {return m_nMinus[bin];}
    float ShowAvgCosPhiP(int event, int bin) {return m_avgCosPhiP[bin];}
    float ShowAvgCosPhiM(int event, int bin) {return m_avgCosPhiM[bin];}
    float ShowAvgSinPhiP(int event, int bin) {return m_avgSinPhiP[bin];}
    float ShowAvgSinPhiM(int event, int bin) {return m_avgSinPhiM[bin];}
    float ShowAvgCos2PhiP(int event, int bin) {return m_avgCos2PhiP[bin];}
    float ShowAvgCos2PhiM(int event, int bin) {return m_avgCos2PhiM[bin];}
    float ShowAvgSin2PhiP(int event, int bin) {return m_avgSin2PhiP[bin];}
    float ShowAvgSin2PhiM(int event, int bin) {return m_avgSin2PhiM[bin];}
    // end of values being read from the femtoDst file

    void MakeV2Profile();
    void MakeNPlusMinusPlots();
    float CreateGamma();

    void secondRun(); // outdated function
    void DeclareHistograms();

    void v22Calculations();

  private:
    TFile *m_file;
    TTree *m_tree;
    long m_numEvents; // the total number of events
    const static int m_numEtaBins=8;
    const static int m_numCentralities=9;

    int m_jobNum;
    int m_RunNumber;
    float m_Energy;

    long m_EventNum;
    long m_EventId;
    int m_totalPlus;
    int m_totalMinus;
    int m_femtoCent;
    float m_femtoVertexX;
    float m_femtoVertexY;
    float m_femtoVertexZ;

    // particles of interest
    int m_nPlus[m_numEtaBins];
    int m_nMinus[m_numEtaBins];
    float m_avgCosPhiP[m_numEtaBins];
    float m_avgSinPhiP[m_numEtaBins];
    float m_avgCosPhiM[m_numEtaBins];
    float m_avgSinPhiM[m_numEtaBins];
    float m_avgCos2PhiP[m_numEtaBins];
    float m_avgSin2PhiP[m_numEtaBins];
    float m_avgCos2PhiM[m_numEtaBins];
    float m_avgSin2PhiM[m_numEtaBins];
 
    // all reference particles
    int m_nPlusRefAll[m_numEtaBins];
    int m_nMinusRefAll[m_numEtaBins];
    float m_avgCosPhiPRefAll[m_numEtaBins];
    float m_avgSinPhiPRefAll[m_numEtaBins];
    float m_avgCosPhiMRefAll[m_numEtaBins];
    float m_avgSinPhiMRefAll[m_numEtaBins];
    float m_avgCos2PhiPRefAll[m_numEtaBins];
    float m_avgSin2PhiPRefAll[m_numEtaBins];
    float m_avgCos2PhiMRefAll[m_numEtaBins];
    float m_avgSin2PhiMRefAll[m_numEtaBins];

    // reference pions, pions with looser cuts
    int m_nPlusRefPi[m_numEtaBins];
    int m_nMinusRefPi[m_numEtaBins];
    float m_avgCosPhiPRefPi[m_numEtaBins];
    float m_avgSinPhiPRefPi[m_numEtaBins];
    float m_avgCosPhiMRefPi[m_numEtaBins];
    float m_avgSinPhiMRefPi[m_numEtaBins];
    float m_avgCos2PhiPRefPi[m_numEtaBins];
    float m_avgSin2PhiPRefPi[m_numEtaBins];
    float m_avgCos2PhiMRefPi[m_numEtaBins];
    float m_avgSin2PhiMRefPi[m_numEtaBins];

    double m_Ach;

    // event averages for eta bins
    int m_totnPlusPerBin[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    int m_totnMinusPerBin[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};

    int m_totNPlusPairsPerBin[m_numEtaBins]={0,0,0,0,0,0,0,0};
    int m_totNMinusPairsPerBin[m_numEtaBins]={0,0,0,0,0,0,0,0};

    float m_eventNPlusAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    float m_eventNMinusAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};

    // <<Cos#phi>>, had average of each bin, so now it's event average of each bin average
    float m_eventAvgCosPhiPAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    float m_eventAvgCosPhiMAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    float m_eventAvgSinPhiPAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    float m_eventAvgSinPhiMAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    float m_eventAvgCos2PhiPAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    float m_eventAvgCos2PhiMAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    float m_eventAvgSin2PhiPAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    float m_eventAvgSin2PhiMAvg[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};

    float m_v2PlusPerBin[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};
    float m_v2MinusPerBin[m_numEtaBins]={-999,-999,-999,-999,-999,-999,-999,-999};

    // v2 values and extras

    vector<float> m_v2PlusCorrect;
    vector<float> m_v2MinusCorrect; // may need a centrality dependent version of these quantities
    // vector<float> m_Ach;

    vector<vector<float> > m_v2PlusCorrectCent;
    vector<vector<float> > m_v2MinusCorrectCent;
    vector<vector<float> > m_AchCent;

    // event averages split by eta bins and centrality bins
    int m_numEventsPerCent[m_numCentralities] = {0,0,0,0,0,0,0,0,0};
/*
    int m_totnPlusPerBinCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_totnMinusPerBinCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_totNPlusPairsPerBinCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_totNMinusPairsPerBinCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventNPlusAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventNMinusAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventAvgCosPhiPAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventAvgCosPhiMAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventAvgSinPhiPAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventAvgSinPhiMAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventAvgCos2PhiPAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventAvgCos2PhiMAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventAvgSin2PhiPAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_eventAvgSin2PhiMAvgCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_v2PlusPerBinCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    int m_v2MinusPerBinCent[m_numCentralities][m_numEtaBins]{
      {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999},
        {-999,-999,-999,-999,-999,-999,-999,-999}
    };
    // end of event averaged eta and centrality split data
*/
    TH2D *m_v2vsEtaPlus;
    TH2D *m_v2vsEtaMinus;

    TH2D *m_v2vsEtaPlusUnweighted;
    TH2D *m_v2vsEtaMinusUnweighted;

    TH2D *m_v2vsEtaPlusCorrected;
    TH2D *m_v2vsEtaMinusCorrected;

    // v2 wrt and v2 CMW are incorrect
    // I have a macro, v2Profile.cxx that makes the correct plot from v2 Corrected
    TH2D *m_v2vsEtaPlusCorrectedwrt; // this is the actual v2, not the v2^{2}
    TH2D *m_v2vsEtaMinusCorrectedwrt; // this is the actual v2, not the v2^{2}
    
    TH2D *m_nPvsnM;
    TH2D *m_nPminnMvsnPplunM;
    TH2D *m_AchVsnPplunM;
    
    TH2D *m_v2PlusVsAch;
    TH2D *m_v2MinusVsAch;
    
    // Ach wrt and Ach CMW will not be used either
    TH2D *m_v2PlusVsAchwrt;
    TH2D *m_v2MinusVsAchwrt;
    
    TH2D *m_v2PlusVsAchCMW;
    TH2D *m_v2MinusVsAchCMW;
    ///
    
    TH2D *m_v2PlusVsAchWeighted;
    TH2D *m_v2MinusVsAchWeighted;
    
    /////////// not using
    TH2D *m_v2PlusVsAchWeightedwrt; // this is the actual v2, not the v2^{2}
    TH2D *m_v2MinusVsAchWeightedwrt;
    
    TH2D *m_v2PlusVsAchWeightedCMW; // v2 for comparison to CMW paper
    TH2D *m_v2MinusVsAchWeightedCMW;
    /////////
    
    TH1D *m_AchDist;
    
    TH2D *m_gammaLSplus;
    TH2D *m_gammaLSminus;
    TH2D *m_gammaLS; // this one is different because it will add the +/- gamma values
    TH2D *m_gammaUL; // probably need at least 4 other permutations
    
    // centrality split histograms
    
    TH2D *m_v2vsEtaPlusCorrectedCent[m_numCentralities];
    TH2D *m_v2vsEtaMinusCorrectedCent[m_numCentralities];
    
    TH2D *m_nPvsnMCent[m_numCentralities];
    TH2D *m_nPminnMvsnPplunMcent[m_numCentralities];
    TH2D *m_AchVsnPplunMcent[m_numCentralities];
    
    TH2D *m_v2PlusVsAchCent[m_numCentralities];
    TH2D *m_v2MinusVsAchCent[m_numCentralities];
   
    TH2D *m_v2EventPlanePlus[m_numCentralities];
    TH2D *m_v2EventPlaneMinus[m_numCentralities]; 

    // new methods for calculating v2, will try histograms and just numbers

    // these histograms will be weighted
    // x = cos/sine
    // y = Ach
    // z = Eta
    TH3D *m_cosAvgAchEtaP[m_numCentralities];
    TH3D *m_sinAvgAchEtaP[m_numCentralities];
    TH3D *m_cos2AvgAchEtaP[m_numCentralities];
    TH3D *m_sin2AvgAchEtaP[m_numCentralities];

    TH3D *m_cosAvgAchEtaM[m_numCentralities];
    TH3D *m_sinAvgAchEtaM[m_numCentralities];
    TH3D *m_cos2AvgAchEtaM[m_numCentralities];
    TH3D *m_sin2AvgAchEtaM[m_numCentralities];

    // TH3D didn't work the way I wanted it too, so I'm going to produce
    // TH2D for each eta

    // for naming convention, the first M/P corresponds to the (+/-) of the charge
    // the second M/P corresponds to the (+/-) of eta

    TH2D *m_cosAvgPAchEtaP[m_numCentralities];
    TH2D *m_sinAvgPAchEtaP[m_numCentralities];
    TH2D *m_cos2AvgPAchEtaP[m_numCentralities];
    TH2D *m_sin2AvgPAchEtaP[m_numCentralities];

    TH2D *m_cosAvgMAchEtaM[m_numCentralities];
    TH2D *m_sinAvgMAchEtaM[m_numCentralities];
    TH2D *m_cos2AvgMAchEtaM[m_numCentralities];
    TH2D *m_sin2AvgMAchEtaM[m_numCentralities];

    TH2D *m_cosAvgPAchEtaM[m_numCentralities];
    TH2D *m_sinAvgPAchEtaM[m_numCentralities];
    TH2D *m_cos2AvgPAchEtaM[m_numCentralities];
    TH2D *m_sin2AvgPAchEtaM[m_numCentralities];

    TH2D *m_cosAvgMAchEtaP[m_numCentralities];
    TH2D *m_sinAvgMAchEtaP[m_numCentralities];
    TH2D *m_cos2AvgMAchEtaP[m_numCentralities];
    TH2D *m_sin2AvgMAchEtaP[m_numCentralities];

    // unweighted histograms

    TH2D *m_cosAvgPAchEtaPunw[m_numCentralities];
    TH2D *m_sinAvgPAchEtaPunw[m_numCentralities];
    TH2D *m_cos2AvgPAchEtaPunw[m_numCentralities];
    TH2D *m_sin2AvgPAchEtaPunw[m_numCentralities];

    TH2D *m_cosAvgMAchEtaMunw[m_numCentralities];
    TH2D *m_sinAvgMAchEtaMunw[m_numCentralities];
    TH2D *m_cos2AvgMAchEtaMunw[m_numCentralities];
    TH2D *m_sin2AvgMAchEtaMunw[m_numCentralities];

    TH2D *m_cosAvgPAchEtaMunw[m_numCentralities];
    TH2D *m_sinAvgPAchEtaMunw[m_numCentralities];
    TH2D *m_cos2AvgPAchEtaMunw[m_numCentralities];
    TH2D *m_sin2AvgPAchEtaMunw[m_numCentralities];

    TH2D *m_cosAvgMAchEtaPunw[m_numCentralities];
    TH2D *m_sinAvgMAchEtaPunw[m_numCentralities];
    TH2D *m_cos2AvgMAchEtaPunw[m_numCentralities];
    TH2D *m_sin2AvgMAchEtaPunw[m_numCentralities];

    // these variables may be too difficult to form the analysis from
    double m_superCosAvg[m_numCentralities];
    double m_superSinAvg[m_numCentralities];
    double m_superCos2Avg[m_numCentralities];
    double m_superSin2Avg[m_numCentralities];
    double m_superNplusPi[m_numCentralities];
    double m_superNminusPi[m_numCentralities];
    double m_superNplus[m_numCentralities];
    double m_superNminus[m_numCentralities];

    // these histograms are debug histograms
    TH2D *hNpartsSubEvents[m_numCentralities];

    TH2D *hNpluAvsCent;
    TH2D *hNpluCvsCent;
    TH2D *hNminAvsCent;
    TH2D *hNminCvsCent;

    //////// new 2-D histograms for various v2 measurements

    TH2D *m_v22vsAchPlusRefAll[m_numCentralities];
    TH2D *m_v22vsAchMinusRefAll[m_numCentralities];
    TH2D *m_v22vsAchPlusRefPi[m_numCentralities];
    TH2D *m_v22vsAchMinusRefPi[m_numCentralities];
    TH2D *m_v22vsAchPlusPOI[m_numCentralities];
    TH2D *m_v22vsAchMinusPOI[m_numCentralities];

    TH2D *m_v22vsAchRefAll[m_numCentralities];


    // POI is eta<0
    TH2D *m_v22vsAchPlusPOIAll[m_numCentralities]; // this histogram refers to singly charged particles
    TH2D *m_v22vsAchMinusPOIAll[m_numCentralities];
    TH2D *m_v22vsAchPlusPOIPi[m_numCentralities];
    TH2D *m_v22vsAchMinusPOIPi[m_numCentralities];

    // this histogram name below is different from the above POIAll/AllPOI because 
    // it looks at all particles, and not just singly charged particles
    TH2D *m_v22vsAchPlusPOIRefAll[m_numCentralities];
    TH2D *m_v22vsAchMinusPOIRefAll[m_numCentralities];

    // POI is eta>0
    TH2D *m_v22vsAchPlusAllPOI[m_numCentralities];
    TH2D *m_v22vsAchMinusAllPOI[m_numCentralities];
    TH2D *m_v22vsAchPlusPiPOI[m_numCentralities];
    TH2D *m_v22vsAchMinusPiPOI[m_numCentralities];

    TH2D *m_v22vsAchPlusRefAllPOI[m_numCentralities];
    TH2D *m_v22vsAchMinusRefAllPOI[m_numCentralities];

    // unweighted versions of the above histograms
    TH2D *m_v22vsAchPlusRefAllUnw[m_numCentralities];
    TH2D *m_v22vsAchMinusRefAllUnw[m_numCentralities];
    TH2D *m_v22vsAchPlusRefPiUnw[m_numCentralities];
    TH2D *m_v22vsAchMinusRefPiUnw[m_numCentralities];
    TH2D *m_v22vsAchPlusPOIUnw[m_numCentralities];
    TH2D *m_v22vsAchMinusPOIUnw[m_numCentralities];

    TH2D *m_v22vsAchRefAllUnw[m_numCentralities];
    // POI is eta<0
    TH2D *m_v22vsAchPlusPOIAllUnw[m_numCentralities];
    TH2D *m_v22vsAchMinusPOIAllUnw[m_numCentralities];
    TH2D *m_v22vsAchPlusPOIPiUnw[m_numCentralities];
    TH2D *m_v22vsAchMinusPOIPiUnw[m_numCentralities];

    TH2D *m_v22vsAchPlusPOIRefAllUnw[m_numCentralities];
    TH2D *m_v22vsAchMinusPOIRefAllUnw[m_numCentralities];

    // POI is eta>0
    TH2D *m_v22vsAchPlusAllPOIUnw[m_numCentralities];
    TH2D *m_v22vsAchMinusAllPOIUnw[m_numCentralities];
    TH2D *m_v22vsAchPlusPiPOIUnw[m_numCentralities];
    TH2D *m_v22vsAchMinusPiPOIUnw[m_numCentralities];

    TH2D *m_v22vsAchPlusRefAllPOIUnw[m_numCentralities];
    TH2D *m_v22vsAchMinusRefAllPOIUnw[m_numCentralities];

    // end of v22 planes

    TH1D *m_hcentrality;
    TH1D *m_hPNumPairsRefAll;
    TH1D *m_hPNumPairsRefPi;
    TH1D *m_hPNumPairsPOIAll;
    TH1D *m_hPNumPairsPOIPi;

    TH1D *m_hMNumPairsRefAll;
    TH1D *m_hMNumPairsRefPi;
    TH1D *m_hMNumPairsPOIAll;
    TH1D *m_hMNumPairsPOIPi;



    TFile *m_writeFile;
};
#endif
