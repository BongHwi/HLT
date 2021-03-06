//#include <Riostream.h>
#include <iostream>
#include"AliAnalysisBGMonitorQAHLT.h"
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH1D.h>
#include"TCanvas.h"
#include"TArrayI.h"
#include"AliAnalysisTaskSE.h"
#include"AliAnalysisManager.h"
#include"AliESD.h"
#include"AliESDEvent.h"
#include"AliESDfriend.h"
#include"AliVEvent.h"
#include"AliESDInputHandler.h"
#include"AliLog.h"
#include"AliAnalysisFilter.h"
#include"AliESDtrackCuts.h"
#include"AliESDVertex.h"
#include"AliESDtrack.h"
#include"AliTriggerAnalysis.h"
#include"AliAnalysisCuts.h"
#include"AliMultiplicity.h"
#include"AliESDVZERO.h"
#include"AliESDVZEROfriend.h"
#include"AliESDTZERO.h"
#include"AliAnalysisUtils.h"
#include"AliESDAD.h"
#include"AliESDADfriend.h"

class AliAnalysisBGMonitorQAHLT;
using namespace std;

ClassImp(AliAnalysisBGMonitorQAHLT)

AliAnalysisBGMonitorQAHLT::AliAnalysisBGMonitorQAHLT() : AliAnalysisTaskSE(),
fESD(0x0),
fESDfriend(0x0),
fTreeTrack2(0),
fList(0),
fList2(0),
fUseTree(kFALSE),
runNumber(0),
fSpdC1(0),
fSpdC2(0),
fSpdT(0),
ntracks(0),
bgID(0),
ntr(0),
nbunch(0),
nV0A(0),
nV0C(0),
nV0ABG(0),
nV0CBG(0)
{
}

//________________________________________________________________________
AliAnalysisBGMonitorQAHLT::AliAnalysisBGMonitorQAHLT(const char *name):
AliAnalysisTaskSE(name),
fESD(0x0),
fESDfriend(0x0),
fTreeTrack2(0),
fList(0),
fList2(0),
fUseTree(kFALSE),
runNumber(0),
fSpdC1(0),
fSpdC2(0),
fSpdT(0),
ntracks(0),
bgID(0),
ntr(0),
nbunch(0),
nV0A(0),
nV0C(0),
nV0ABG(0),
nV0CBG(0)
{
    // Constructor
    DefineInput(0, TChain::Class());
    DefineOutput(1, TList::Class()); //CINT7
    DefineOutput(2, TList::Class()); //V0M, SH2
    DefineOutput(0, TTree::Class()); //RunNumber
}
AliAnalysisBGMonitorQAHLT::~AliAnalysisBGMonitorQAHLT()
{
    // destructor
    if(fList) {
        delete fList;     // at the end of your task, it is deleted from memory by calling this function
    }
    if(fList2) {
        delete fList2;     // at the end of your task, it is deleted from memory by calling this function
    }
}

//________________________________________________________________________
void AliAnalysisBGMonitorQAHLT::UserCreateOutputObjects()
{
    fTreeTrack2 = new TTree("TreeTrack","Track Properties2");
    fTreeTrack2->Branch("runNumber",&runNumber,"runNumber/I"); //run number
    PostData(0, fTreeTrack2);
    fList = new TList();
    fList->SetOwner(kTRUE);
    fList2 = new TList();
    fList2->SetOwner(kTRUE);
    TH2F *hTotalTrkVsClsSPID = new TH2F("hTotalTrkVsClsSPID","; Spd : total",140,0,140,500,0,500);
    hTotalTrkVsClsSPID->GetXaxis()->SetTitle("Tracklet");
    hTotalTrkVsClsSPID->GetYaxis()->SetTitle("Cluster (fspdC1+fspdC2)");
    fList->Add(hTotalTrkVsClsSPID);
    TH2F *hTotalTrkVsClsSPID_PF2 = new TH2F("hTotalTrkVsClsSPID_PF2","; Spd : total",140,0,140,500,0,500);
    hTotalTrkVsClsSPID_PF2->GetXaxis()->SetTitle("Tracklet");
    hTotalTrkVsClsSPID_PF2->GetYaxis()->SetTitle("Cluster (fspdC1+fspdC2)");
    fList->Add(hTotalTrkVsClsSPID_PF2);
    TH2F *hTotalTrkVsClsSPID_PF10 = new TH2F("hTotalTrkVsClsSPID_PF10","; Spd : total",140,0,140,500,0,500);
    hTotalTrkVsClsSPID_PF10->GetXaxis()->SetTitle("Tracklet");
    hTotalTrkVsClsSPID_PF10->GetYaxis()->SetTitle("Cluster (fspdC1+fspdC2)");
    fList->Add(hTotalTrkVsClsSPID_PF10);
    //______________________________
    TH2F *hTotalTrkVsClsSPID_V0M = new TH2F("hTotalTrkVsClsSPID_V0M","; Spd : total",140,0,140,500,0,500);
    hTotalTrkVsClsSPID_V0M->GetXaxis()->SetTitle("Tracklet");
    hTotalTrkVsClsSPID_V0M->GetYaxis()->SetTitle("Cluster (fspdC1+fspdC2)");
    fList2->Add(hTotalTrkVsClsSPID_V0M);
    TH2F *hTotalTrkVsClsSPID_V0M_PF2 = new TH2F("hTotalTrkVsClsSPID_V0M_PF2","; Spd : total",140,0,140,500,0,500);
    hTotalTrkVsClsSPID_V0M_PF2->GetXaxis()->SetTitle("Tracklet");
    hTotalTrkVsClsSPID_V0M_PF2->GetYaxis()->SetTitle("Cluster (fspdC1+fspdC2)");
    fList2->Add(hTotalTrkVsClsSPID_V0M_PF2);
    TH2F *hTotalTrkVsClsSPID_V0M_PF10 = new TH2F("hTotalTrkVsClsSPID_V0M_PF10","; Spd : total",140,0,140,500,0,500);
    hTotalTrkVsClsSPID_V0M_PF10->GetXaxis()->SetTitle("Tracklet");
    hTotalTrkVsClsSPID_V0M_PF10->GetYaxis()->SetTitle("Cluster (fspdC1+fspdC2)");
    fList2->Add(hTotalTrkVsClsSPID_V0M_PF10);
    //______________________________
    TH2F *hTotalTrkVsClsSPID_SH2 = new TH2F("hTotalTrkVsClsSPID_SH2","; Spd : total",140,0,140,500,0,500);
    hTotalTrkVsClsSPID_SH2->GetXaxis()->SetTitle("Tracklet");
    hTotalTrkVsClsSPID_SH2->GetYaxis()->SetTitle("Cluster (fspdC1+fspdC2)");
    fList2->Add(hTotalTrkVsClsSPID_SH2);
    TH2F *hTotalTrkVsClsSPID_SH2_PF2 = new TH2F("hTotalTrkVsClsSPID_SH2_PF2","; Spd : total",140,0,140,500,0,500);
    hTotalTrkVsClsSPID_SH2_PF2->GetXaxis()->SetTitle("Tracklet");
    hTotalTrkVsClsSPID_SH2_PF2->GetYaxis()->SetTitle("Cluster (fspdC1+fspdC2)");
    fList2->Add(hTotalTrkVsClsSPID_SH2_PF2);
    TH2F *hTotalTrkVsClsSPID_SH2_PF10 = new TH2F("hTotalTrkVsClsSPID_SH2_PF10","; Spd : total",140,0,140,500,0,500);
    hTotalTrkVsClsSPID_SH2_PF10->GetXaxis()->SetTitle("Tracklet");
    hTotalTrkVsClsSPID_SH2_PF10->GetYaxis()->SetTitle("Cluster (fspdC1+fspdC2)");
    fList2->Add(hTotalTrkVsClsSPID_SH2_PF10);
    //______________________________
    //histogram for event list(blim)
    TH1F *hNumEvents  = new TH1F("hNumEvents","total event",10,0,10);
    fList->Add(hNumEvents);
    PostData(1, fList);
    PostData(2, fList2);
}

//________________________________________________________________________
void AliAnalysisBGMonitorQAHLT::Exec(Option_t *)
{
    AliESDInputHandler *esdH = dynamic_cast<AliESDInputHandler*> (AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
    if (esdH) {
        fESD = (AliESDEvent*) esdH->GetEvent();
        if(fESD) {
            fESDfriend = (AliESDfriend*)fESD->FindListObject("AliESDfriend");
            if (!fESDfriend){
                AliError("No friend found");
            }
        }
        } else {
        Printf("ERROR: Could not get ESDInputHandler");
    }
    if (!fESD) {
        Printf("ERROR: fESD not available");
        return;
    }
    runNumber = fESD->GetRunNumber();
    ntr = 10;
    nbunch = 21;
    static AliTriggerAnalysis * triggerAnalysis = new AliTriggerAnalysis();
    
    AliVVZERO *vzero = fESD->GetVZEROData();
   
    AliAnalysisUtils *utils = new AliAnalysisUtils();
    bgID = utils->IsSPDClusterVsTrackletBG(fESD);
   
    //--- SPD cluster and tracklets
    const AliMultiplicity* mult = fESD->GetMultiplicity();
    fSpdC1 = 0;
    fSpdC2 = 0;
   
    fSpdC1 = mult->GetNumberOfITSClusters(0);
    fSpdC2 = mult->GetNumberOfITSClusters(1);
    fSpdT = mult->GetNumberOfTracklets();
    
    //"online" V0 flags
    nV0A = 0;
    nV0ABG = 0;
    for (Int_t i = 32; i < 64; ++i) {
        if (vzero->GetBBFlag(i)) nV0A++;
        if (vzero->GetBGFlag(i)) nV0ABG++;
    }
    nV0C = 0;
    nV0CBG = 0;
    for (Int_t i = 0; i < 32; ++i) {
        if (vzero->GetBBFlag(i)) nV0C++;
        if (vzero->GetBGFlag(i)) nV0CBG++;
    }
    memset(BGFlagA, 0, sizeof(Float_t)*nbunch);
    memset(BBFlagA, 0, sizeof(Float_t)*nbunch);
    memset(BGFlagC, 0, sizeof(Float_t)*nbunch);
    memset(BBFlagC, 0, sizeof(Float_t)*nbunch);
    AliESDVZEROfriend *esdV0friend = fESDfriend->GetVZEROfriend();
    if(esdV0friend) {
        for(Int_t j = 0; j < 20; j++){
            for (Int_t i = 32; i < 64; ++i) {
                if(esdV0friend->GetBBFlag(i,j)) BBFlagA[j]++;
                if(esdV0friend->GetBGFlag(i,j)) BGFlagA[j]++;
            }
            for (Int_t i = 0; i < 32; ++i) {
                if(esdV0friend->GetBBFlag(i,j)) BBFlagC[j]++;
                if(esdV0friend->GetBGFlag(i,j)) BGFlagC[j]++;
            }
        }
        } else {
        Printf("No esdV0friend available");
        return;
    }
    ntracks = fESD->GetNumberOfTracks(); // number of tracks (no quality cuts)
    //--- Trigger classes --//
    memset(ftrigger, 0, sizeof(Float_t)*ntr);
    if(fESD->IsTriggerClassFired("CINT7-B-NOPF-ALLNOTRD") || fESD->IsTriggerClassFired("CINT7-S-NOPF-ALLNOTRD") || fESD->IsTriggerClassFired("CINT1-B-NOPF-ALLNOTRD") || fESD->IsTriggerClassFired("CINT1-S-NOPF-ALLNOTRD") || fESD->IsTriggerClassFired("CINT7-A-NOPF-CENT") || fESD->IsTriggerClassFired("CINT7-B-NOPF-CENT") || fESD->IsTriggerClassFired("CINT7-C-NOPF-CENT") || fESD->IsTriggerClassFired("CINT7-E-NOPF-CENT")) ftrigger[0] = 1; // CINT7 trigger
    if(fESD->IsTriggerClassFired("CVHMV0M-A-NOPF-CENT") || fESD->IsTriggerClassFired("CVHMV0M-B-NOPF-CENT") || fESD->IsTriggerClassFired("CVHMV0M-C-NOPF-CENT") || fESD->IsTriggerClassFired("CVHMV0M-E-NOPF-CENT") || fESD->IsTriggerClassFired("CVHMV0M-B-SPD1-CENT") || fESD->IsTriggerClassFired("CVHMV0M-A-NOPF-CENTNOTRD") || fESD->IsTriggerClassFired("CVHMV0M-B-NOPF-CENTNOTRD") || fESD->IsTriggerClassFired("CVHMV0M-C-NOPF-CENTNOTRD") || fESD->IsTriggerClassFired("CVHMV0M-E-NOPF-CENTNOTRD")) ftrigger[1] = 1; // VOM trigger
    if(fESD->IsTriggerClassFired("CVHMSH2-A-NOPF-CENT") || fESD->IsTriggerClassFired("CVHMSH2-B-NOPF-CENT") || fESD->IsTriggerClassFired("CVHMSH2-C-NOPF-CENT") || fESD->IsTriggerClassFired("CVHMSH2-E-NOPF-CENT") || fESD->IsTriggerClassFired("CVHMSH2-B-NOPF-ALL") || fESD->IsTriggerClassFired("CVHMSH2-B-NOPF-CENTNOTRD")) ftrigger[2] = 1; // SH2 trigger
    // count total event number (blim)
    if(ftrigger[0]==1)((TH1F*)fList->FindObject("hNumEvents"))->Fill(1);
    if(ftrigger[1]==1)((TH1F*)fList->FindObject("hNumEvents"))->Fill(2);
    if(ftrigger[2]==1)((TH1F*)fList->FindObject("hNumEvents"))->Fill(3);
    // Bool_t goodEvent;
    static Bool_t SelGoodEvent;

    //-------------------------------------------------------CINT7-------------------------------------------------------
    if(ftrigger[0]) {  // trigger class for MB
        Printf("CINT7 triggred");
        ((TH1F*)fList->FindObject("hTotalTrkVsClsSPID"))->Fill(fSpdT, fSpdC1+fSpdC2);
        for(Int_t ii=1; ii<33; ii++){
            //___________
            SelGoodEvent = BBFlagA[11]<ii  &  BBFlagA[12]<ii  &  BBFlagA[13]<ii  &  BBFlagA[14]<ii  &  BBFlagA[15]<ii  &  BBFlagA[16]<ii  & BBFlagA[17]<ii; //BB-A 11-17
            SelGoodEvent &= BBFlagC[11]<ii  &  BBFlagC[12]<ii  &  BBFlagC[13]<ii  &  BBFlagC[14]<ii  &  BBFlagC[15]<ii  &  BBFlagC[16]<ii  &  BBFlagC[17]<ii; //BB-C 11-17
            SelGoodEvent &= BBFlagA[9]<ii  &  BBFlagA[8]<ii  &  BBFlagA[7]<ii  & BBFlagA[6]<ii  & BBFlagA[5]<ii  & BBFlagA[4]<ii  & BBFlagA[3]<ii; //BB-A 3-9
            SelGoodEvent &= BBFlagC[9]<ii  &  BBFlagC[8]<ii  &  BBFlagC[7]<ii  &  BBFlagC[6]<ii  &  BBFlagC[5]<ii  &  BBFlagC[4]<ii  & BBFlagC[3]<ii; //BB-C 3-9
            //___________
            if(SelGoodEvent) {
                if(ii == 2){
                    ((TH1F*)fList->FindObject("hTotalTrkVsClsSPID_PF2"))->Fill(fSpdT, fSpdC1+fSpdC2);
                }
                if(ii == 10){
                    ((TH1F*)fList->FindObject("hTotalTrkVsClsSPID_PF10"))->Fill(fSpdT, fSpdC1+fSpdC2);
                }
            }
        } // end of V0 flag loop
    } // end of events in trigger loop

    //-------------------------------------------------------V0M-------------------------------------------------------
    if(ftrigger[1]) {  // trigger class for HM // add new List for both result 2015.08.20. (blim)
        Printf("V0M triggred");
        ((TH1F*)fList2->FindObject("hTotalTrkVsClsSPID_V0M"))->Fill(fSpdT, fSpdC1+fSpdC2);
        for(Int_t ii=1; ii<33; ii++){
            //___________
            SelGoodEvent = BBFlagA[11]<ii  &  BBFlagA[12]<ii  &  BBFlagA[13]<ii  &  BBFlagA[14]<ii  &  BBFlagA[15]<ii  &  BBFlagA[16]<ii  & BBFlagA[17]<ii; //BB-A 11-17
            SelGoodEvent &= BBFlagC[11]<ii  &  BBFlagC[12]<ii  &  BBFlagC[13]<ii  &  BBFlagC[14]<ii  &  BBFlagC[15]<ii  &  BBFlagC[16]<ii  &  BBFlagC[17]<ii; //BB-C 11-17
            SelGoodEvent &= BBFlagA[9]<ii  &  BBFlagA[8]<ii  &  BBFlagA[7]<ii  & BBFlagA[6]<ii  & BBFlagA[5]<ii  & BBFlagA[4]<ii  & BBFlagA[3]<ii; //BB-A 3-9
            SelGoodEvent &= BBFlagC[9]<ii  &  BBFlagC[8]<ii  &  BBFlagC[7]<ii  &  BBFlagC[6]<ii  &  BBFlagC[5]<ii  &  BBFlagC[4]<ii  & BBFlagC[3]<ii; //BB-C 3-9
            //___________
            if(SelGoodEvent) {
                if(ii == 2){
                    ((TH1F*)fList2->FindObject("hTotalTrkVsClsSPID_V0M_PF2"))->Fill(fSpdT, fSpdC1+fSpdC2);
                }
                if(ii == 10){
                    ((TH1F*)fList2->FindObject("hTotalTrkVsClsSPID_V0M_PF10"))->Fill(fSpdT, fSpdC1+fSpdC2);
                }
            }
        } // end of V0 flag loop
    } // end of events in trigger loop

    //-------------------------------------------------------SH2-------------------------------------------------------
    if(ftrigger[2]) {  // trigger class for HM // add new List for both result 2015.08.20. (blim)
        Printf("SH2 triggred");
        ((TH1F*)fList2->FindObject("hTotalTrkVsClsSPID_SH2"))->Fill(fSpdT, fSpdC1+fSpdC2);
        for(Int_t ii=1; ii<33; ii++){
            //___________
            SelGoodEvent = BBFlagA[11]<ii  &  BBFlagA[12]<ii  &  BBFlagA[13]<ii  &  BBFlagA[14]<ii  &  BBFlagA[15]<ii  &  BBFlagA[16]<ii  & BBFlagA[17]<ii; //BB-A 11-17
            SelGoodEvent &= BBFlagC[11]<ii  &  BBFlagC[12]<ii  &  BBFlagC[13]<ii  &  BBFlagC[14]<ii  &  BBFlagC[15]<ii  &  BBFlagC[16]<ii  &  BBFlagC[17]<ii; //BB-C 11-17
            SelGoodEvent &= BBFlagA[9]<ii  &  BBFlagA[8]<ii  &  BBFlagA[7]<ii  & BBFlagA[6]<ii  & BBFlagA[5]<ii  & BBFlagA[4]<ii  & BBFlagA[3]<ii; //BB-A 3-9
            SelGoodEvent &= BBFlagC[9]<ii  &  BBFlagC[8]<ii  &  BBFlagC[7]<ii  &  BBFlagC[6]<ii  &  BBFlagC[5]<ii  &  BBFlagC[4]<ii  & BBFlagC[3]<ii; //BB-C 3-9
            //___________
            if(SelGoodEvent) {
                if(ii == 2){
                    ((TH1F*)fList2->FindObject("hTotalTrkVsClsSPID_SH2_PF2"))->Fill(fSpdT, fSpdC1+fSpdC2);
                }
                if(ii == 10){
                    ((TH1F*)fList2->FindObject("hTotalTrkVsClsSPID_SH2_PF10"))->Fill(fSpdT, fSpdC1+fSpdC2);
                }
            }
        } // end of V0 flag loop
    } // end of events in trigger loop
    PostData(1, fList);
    PostData(2, fList2);
    fTreeTrack2->Fill();
    PostData(0, fTreeTrack2);
}
//________________________________________________________________________
void AliAnalysisBGMonitorQAHLT::Terminate(Option_t *)
{
}