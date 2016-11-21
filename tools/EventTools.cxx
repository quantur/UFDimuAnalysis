// EventTools.cxx

#include <vector>
#include <utility> // pair
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "EventTools.h"
#include "CategorySelection.h"
#include "JetSelectionTools.h"

//////////////////////////////////////////////////////////////////
//---------------------------------------------------------------
//////////////////////////////////////////////////////////////////

void EventTools::loadEventsFromFile(TString filename, std::vector<std::pair<int, long long int>>& v)
{
    std::ifstream file(filename);
    std::string run;
    std::string event;
    int runn; 
    long long int eventn;
    while(std::getline(file, run, ','))
    {
        std::getline(file, event);
        std::stringstream ssrun;
        std::stringstream ssevent;
        ssrun << run;
        ssrun >> runn;
        ssevent << event;
        ssevent >> eventn; 

        v.push_back(std::pair<int, long long int>(runn, eventn)); 
    } 
}

//////////////////////////////////////////////////////////////////
//---------------------------------------------------------------
//////////////////////////////////////////////////////////////////

void EventTools::outputEventsToFile(std::vector<std::pair<int,long long int>>& v, TString filename)
{
    std::cout << "  /// Exporting events to " << filename << " ..." << std::endl;
    std::ofstream file(filename, std::ofstream::out);
    for(auto const &e : v)
    {   
        file << e.first << ", " << e.second << std::endl;
    }   
    file.close();  
}

//////////////////////////////////////////////////////////////////
//---------------------------------------------------------------
//////////////////////////////////////////////////////////////////

bool EventTools::sameRunAndEvent(std::pair<int,long long int> a, std::pair<int,long long int> b)
{
   if(a.first == b.first && a.second == b.second) return true; 
   else return false;
}

//////////////////////////////////////////////////////////////////
//---------------------------------------------------------------
//////////////////////////////////////////////////////////////////

bool EventTools::eventInVector(std::pair<int,long long int> e, std::vector<std::pair<int,long long int>> events)
{
    for(unsigned int i=0; i<events.size(); i++)
    {
        if(sameRunAndEvent(e, events[i])) return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////
//---------------------------------------------------------------
//////////////////////////////////////////////////////////////////

void EventTools::outputEvent(VarSet& vars)
{
         JetSelectionTools js;
         std::cout << "========= RUN: " << vars.eventInfo.run << ", EVENT: " << vars.eventInfo.event << " =============" << std::endl;
         std::cout << std::endl;
         std::cout << "  dimuCand.recoCandMass: " << vars.dimuCand.recoCandMass << std::endl;
         std::cout << "  dimuCand.recoCandMassPF: " << vars.dimuCand.recoCandMassPF << std::endl;
         std::cout << "  dimuCand.recoCandPt: " << vars.dimuCand.recoCandPt << std::endl;
         std::cout << std::endl;
         std::cout << "  recoMuons.pt[0]: " << vars.recoMuons.pt[0] << std::endl;
         std::cout << "  recoMuons.phi[0]: " << vars.recoMuons.phi[0] << std::endl;
         std::cout << "  recoMuons.eta[0]: " << vars.recoMuons.eta[0] << std::endl;
         std::cout << "  recoMuons.isHltMatched[0][0or1]: " << (vars.recoMuons.isHltMatched[0][0] || vars.recoMuons.isHltMatched[1][1]) << std::endl;
         std::cout << std::endl;
         std::cout << "  recoMuons.pt[1]: " << vars.recoMuons.pt[1] << std::endl;
         std::cout << "  recoMuons.phi[1]: " << vars.recoMuons.phi[1] << std::endl;
         std::cout << "  recoMuons.eta[1]: " << vars.recoMuons.eta[1] << std::endl;
         std::cout << "  recoMuons.isHltMatched[1][0or1]: " << (vars.recoMuons.isHltMatched[1][0] || vars.recoMuons.isHltMatched[1][1]) << std::endl;
         std::cout << std::endl;
         std::cout << "  nJets: " << vars.jets.nJets << std::endl;
         std::cout << "  nValidJets: " << vars.validJets.size() << std::endl;
         std::cout << "  nValidBJets: " << vars.validBJets.size() << std::endl;
         std::cout << std::endl;
         std::cout << "  nGenJets: " << vars.genJets.nJets << std::endl;
         std::cout << "  nValidGenJets: " << vars.validGenJets.size() << std::endl;
         std::cout << std::endl;
         std::cout << "  nValidMuons: " << vars.validMuons.size() << std::endl;
         std::cout << "  nValidExtraMuons: " << vars.validExtraMuons.size() << std::endl;
         std::cout << "  nValidElectrons: " << vars.validElectrons.size() << std::endl;
         std::cout << "  nValidExtraLeptons: " << vars.validElectrons.size() + vars.validExtraMuons.size() << std::endl;
         std::cout << std::endl;
         std::cout << "  MET: " << vars.met.pt << std::endl;
         std::cout << std::endl;

         for(unsigned int j=0; j<vars.jets.nJets && j<vars.jets.arraySize; j++)
         {
             std::cout << "  jet" << j << " pt: " <<  vars.jets.pt[j] << std::endl;
             std::cout << "  jet" << j << " phi: " << vars.jets.phi[j] << std::endl;
             std::cout << "  jet" << j << " eta: " << vars.jets.eta[j] << std::endl;
             std::cout << "  jet" << j << " isB: " << vars.jets.isB[j] << std::endl;
             std::cout << "  jet" << j << " dR1: " << js.dR(vars.jets.eta[j], vars.jets.phi[j], vars.recoMuons.eta[0], vars.recoMuons.phi[0]) << std::endl;
             std::cout << "  jet" << j << " dR2: " << js.dR(vars.jets.eta[j], vars.jets.phi[j], vars.recoMuons.eta[1], vars.recoMuons.phi[1]) << std::endl;
             std::cout << std::endl;

         }

         std::cout << std::endl;

         for(unsigned int j=0; j<vars.validJets.size(); j++)
         {
             std::cout << "  validjet" << j << " pt: " <<  vars.validJets[j].Pt() << std::endl;
             std::cout << "  validjet" << j << " phi: " << vars.validJets[j].Phi() << std::endl;
             std::cout << "  validjet" << j << " eta: " << vars.validJets[j].Eta() << std::endl;
             std::cout << "  validjet" << j << " dR1: " << js.dR(vars.validJets[j].Eta(), vars.validJets[j].Phi(), vars.recoMuons.eta[0], vars.recoMuons.phi[0]) << std::endl;
             std::cout << "  validjet" << j << " dR2: " << js.dR(vars.validJets[j].Eta(), vars.validJets[j].Phi(), vars.recoMuons.eta[1], vars.recoMuons.phi[1]) << std::endl;
             std::cout << std::endl;

         }
         std::cout << std::endl;

         for(unsigned int j=0; j<vars.validBJets.size(); j++)
         {
             std::cout << "  validBjet" << j << " pt: " <<  vars.validBJets[j].Pt() << std::endl;
             std::cout << "  validBjet" << j << " phi: " << vars.validBJets[j].Phi() << std::endl;
             std::cout << "  validBjet" << j << " eta: " << vars.validBJets[j].Eta() << std::endl;
             std::cout << "  validBjet" << j << " dR1: " << js.dR(vars.validBJets[j].Eta(), vars.validBJets[j].Phi(), vars.recoMuons.eta[0], vars.recoMuons.phi[0]) << std::endl;
             std::cout << "  validBjet" << j << " dR2: " << js.dR(vars.validBJets[j].Eta(), vars.validBJets[j].Phi(), vars.recoMuons.eta[1], vars.recoMuons.phi[1]) << std::endl;
             std::cout << std::endl;

         }
         std::cout << std::endl;

         //for(unsigned int j=0; j<vars.genJets.nJets && j<vars.genJets.arraySize; j++)
         //{
         //    std::cout << "  genJet" << j << " pt: " <<  vars.genJets.pt[j] << std::endl;
         //    std::cout << "  genJet" << j << " phi: " << vars.genJets.phi[j] << std::endl;
         //    std::cout << "  genJet" << j << " eta: " << vars.genJets.eta[j] << std::endl;
         //    std::cout << "  genJet" << j << " dR1: " << js.dR(vars.genJets.eta[j], vars.genJets.phi[j], vars.recoMuons.eta[0], vars.recoMuons.phi[0]) << std::endl;
         //    std::cout << "  genJet" << j << " dR2: " << js.dR(vars.genJets.eta[j], vars.genJets.phi[j], vars.recoMuons.eta[1], vars.recoMuons.phi[1]) << std::endl;
         //    std::cout << std::endl;

         //}

         std::cout << std::endl;

         //for(unsigned int j=0; j<vars.validGenJets.size(); j++)
         //{
         //    std::cout << "  validGenJet" << j << " pt: " <<  vars.validGenJets[j].Pt() << std::endl;
         //    std::cout << "  validGenJet" << j << " phi: " << vars.validGenJets[j].Phi() << std::endl;
         //    std::cout << "  validGenJet" << j << " eta: " << vars.validGenJets[j].Eta() << std::endl;
         //    std::cout << "  validGenJet" << j << " dR1: " << js.dR(vars.validGenJets[j].Eta(), vars.validGenJets[j].Phi(), vars.recoMuons.eta[0], vars.recoMuons.phi[0]) << std::endl;
         //    std::cout << "  validGenJet" << j << " dR2: " << js.dR(vars.validGenJets[j].Eta(), vars.validGenJets[j].Phi(), vars.recoMuons.eta[1], vars.recoMuons.phi[1]) << std::endl;
         //    std::cout << std::endl;

         //}
         //std::cout << std::endl;

         for(unsigned int j=0; j<vars.validMuons.size(); j++)
         {
             std::cout << "  validMuon" << j << " pt: " <<  vars.validMuons[j].Pt() << std::endl;
             std::cout << "  validMuon" << j << " phi: " << vars.validMuons[j].Phi() << std::endl;
             std::cout << "  validMuon" << j << " eta: " << vars.validMuons[j].Eta() << std::endl;
             std::cout << std::endl;

         }
         std::cout << std::endl;
         for(unsigned int j=0; j<vars.validExtraMuons.size(); j++)
         {
             std::cout << "  validExtraMuon" << j << " pt: " <<  vars.validExtraMuons[j].Pt() << std::endl;
             std::cout << "  validExtraMuon" << j << " phi: " << vars.validExtraMuons[j].Phi() << std::endl;
             std::cout << "  validExtraMuon" << j << " eta: " << vars.validExtraMuons[j].Eta() << std::endl;
             std::cout << std::endl;

         }
         std::cout << std::endl;
         for(unsigned int j=0; j<vars.validElectrons.size(); j++)
         {
             std::cout << "  validElectron" << j << " pt: " <<  vars.validElectrons[j].Pt() << std::endl;
             std::cout << "  validElectron" << j << " phi: " << vars.validElectrons[j].Phi() << std::endl;
             std::cout << "  validElectron" << j << " eta: " << vars.validElectrons[j].Eta() << std::endl;
             std::cout << std::endl;

         }
         std::cout << std::endl;


}

//////////////////////////////////////////////////////////////////
//---------------------------------------------------------------
//////////////////////////////////////////////////////////////////

void EventTools::outputEvent(VarSet& vars, Categorizer& categorizer)
{
         // output standard information about the event
         outputEvent(vars);
         categorizer.outputResults();
}

//////////////////////////////////////////////////////////////////
//---------------------------------------------------------------
//////////////////////////////////////////////////////////////////

void EventTools::cleanByDR(std::vector<TLorentzVector>& v1, std::vector<TLorentzVector>& v2, float dRmin)
{
// clean 4vecs in v1 by dR based upon 4vecs in v2

    for(unsigned int i=0; i<v1.size(); i++)
    {
        for(unsigned int j=0; j<v2.size(); j++)
        {
            if(!(v1[i].DeltaR(v2[j]) > dRmin)) v1.erase(v1.begin()+i); 
            i--;
        }
    }

}
