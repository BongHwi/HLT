class AliAnalysisDataContainer;

AliAnalysisBGMonitorQAHLT* AddTaskBGMonitorQAHLT(Bool_t UseTree = kFALSE)
{
  //
  //This macro configures the task for the Beam Gas Monitoring QA
  //==============================================================================
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
      ::Error("AddTaskMBVeto", "No analysis manager to connect to.");
      return NULL;
    }   
    if (!mgr->GetInputEventHandler()) {
        return 0x0;
    }

    
  if (!mgr->GetInputEventHandler()) {
    ::Error("AddTaskMBVeto", "This task requires an input event handler");
    return NULL;
  }
    
  // Create and configure the task
  AliAnalysisBGMonitorQAHLT* taskBGMonitorQA = new AliAnalysisBGMonitorQAHLT("taskBGMonitorQA");
      if(!taskBGMonitorQA) return 0x0;
  mgr->AddTask(taskBGMonitorQA);
  
  // Create containers for input/output
 // AliAnalysisDataContainer *cinput = mgr->CreateContainer("cchain1",TChain::Class(), AliAnalysisManager::kInputContainer);
//  mgr->ConnectInput(taskBGMonitorQA, 0, mgr->GetCommonInputContainer());
  
  mgr->ConnectInput(taskBGMonitorQA,0,mgr->GetCommonInputContainer());
  mgr->ConnectOutput(taskBGMonitorQA,1,mgr->CreateContainer("cOutputH_CINT7", TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s:BeamGasMon", mgr->GetCommonFileName())));

  mgr->ConnectOutput(taskBGMonitorQA,2,mgr->CreateContainer("cOutputH_V0MandSH2", TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s:BeamGasMon", mgr->GetCommonFileName())));

  mgr->ConnectOutput(taskBGMonitorQA,0,mgr->CreateContainer("cOutputT", TTree::Class(), AliAnalysisManager::kOutputContainer, Form("%s:BeamGasMon", mgr->GetCommonFileName())));
/*
  AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("cOutputH_CINT7", TList::Class(), AliAnalysisManager::kOutputContainer,Form("%s:BeamGasMon", mgr->GetCommonFileName()));
  mgr->ConnectOutput(taskBGMonitorQA, 1, coutput1);
*/
/*    AliAnalysisDataContainer *coutput2 = mgr->CreateContainer("cOutputH_V0MandSH2", TList::Class(), AliAnalysisManager::kOutputContainer, Form("%s:BeamGasMon", mgr->GetCommonFileName()));
    mgr->ConnectOutput(taskBGMonitorQA, 2, coutput2);

    AliAnalysisDataContainer *coutput3 = mgr->CreateContainer("cOutputT", TTree::Class(), AliAnalysisManager::kOutputContainer, Form("%s:BeamGasMon", mgr->GetCommonFileName()));
    mgr->ConnectOutput(taskBGMonitorQA, 0, coutput3);
  */  
  return taskBGMonitorQA;
  
}

