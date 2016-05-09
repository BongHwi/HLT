#ifndef AliAnalysisBGMonitorQAHLT_H
#define AliAnalysisBGMonitorQAHLT_H

#include "AliAnalysisTaskSE.h"


class AliESDEvent;
class AliESDfriend;
class AliAnalysisCuts;
class TH1D;
class TH1F;
class TH2F;
class TH2D;

class AliAnalysisBGMonitorQAHLT : public AliAnalysisTaskSE {
 public:
                                        AliAnalysisBGMonitorQAHLT();
                                        AliAnalysisBGMonitorQAHLT(const char* name);
  virtual                            ~AliAnalysisBGMonitorQAHLT();

  virtual void                    UserCreateOutputObjects();
  virtual void                    Exec(Option_t* option);
  virtual void                    Terminate(Option_t* option);

 // virtual void   Terminate(Option_t *);
    
 private: 
  AliESDEvent* fESD;        //! ESD event
  AliESDfriend* fESDfriend; //! ESDfriend   
  TTree *fTreeTrack;        //! tree
  TTree *fTreeTrack2;        //! tree
  TList *fList;             //! list
  TList *fList2;           //! list

  Int_t fUseTree;


  Int_t runNumber;
  Int_t ftrigger[kMaxUShort]; 
  Double_t fvertZ;
  Double_t fvertX;
  Double_t fvertY;
  Double_t fvertTPCZ;
  Double_t fvertTPCX;
  Double_t fvertTPCY;
  Double_t fvertZ2;
  Double_t fvertX2;
  Double_t fvertY2;
  Double_t fvertTPCZ2;
  Double_t fvertTPCX2;
  Double_t fvertTPCY2;
  Float_t fv0a;
  Float_t fv0c;
  Float_t fad0a;
  Float_t fad0c;
  Float_t fMulta;
  Float_t fMultc;
  Float_t fTriCha;
  Float_t fTriChc;
  Float_t fV0M;
  
  Int_t fbx;
  Int_t ftime;
  Int_t fSpdC1;
  Int_t fSpdC2;
  Int_t fSpdT;
  Int_t ntracks;
  Int_t V0A;
  Int_t V0C;
  Int_t V0ABG;
  Int_t V0CBG;
  Int_t nV0A;
  Int_t nV0C;
  Int_t nV0ABG;
  Int_t nV0CBG;
  Int_t VBA;
  Int_t VBC;
  Int_t VGA;
  Int_t VGC;
  Int_t VTX;
  Int_t bgID;
  Int_t t0PileUp;
  Int_t spdPileUp;
  Int_t spdPileUpOutOfBunch;
  Int_t triMask; 
  Int_t fastORHW;  
  Int_t SPD1;
  Int_t SPD2;
  Int_t SPDHw1;
  Int_t SPDHw2; 
  Int_t BGFlagA[kMaxUShort];
  Int_t BGFlagC[kMaxUShort];
  Int_t BBFlagA[kMaxUShort];
  Int_t BBFlagC[kMaxUShort];
  Int_t ADBGFlagA[kMaxUShort];
  Int_t ADBGFlagC[kMaxUShort];
  Int_t ADBBFlagA[kMaxUShort];
  Int_t ADBBFlagC[kMaxUShort];
  
  UShort_t ntr;
  UShort_t nbunch;

  AliAnalysisBGMonitorQAHLT(const AliAnalysisBGMonitorQAHLT&); // not implemented
  AliAnalysisBGMonitorQAHLT &operator=(const AliAnalysisBGMonitorQAHLT&); // not implemented
  ClassDef(AliAnalysisBGMonitorQAHLT,2);// example of analysis
};

#endif
