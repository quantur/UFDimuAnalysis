// VarSet.h
// Load the variables from the ttree into the structs in this class

#ifndef ADD_VARSET
#define ADD_VARSET

#include "DataFormats.h"

class VarSet
{
    public:
        VarSet(){};
        ~VarSet(){};

        _EventInfo eventInfo;
        _VertexInfo vertices;
        _MuonInfo reco1;
        _MuonInfo reco2;
        _MetInfo met;
        _PFJetInfo jets;
 
        float recoCandMass, recoCandMassPF;
        float recoCandPt, recoCandPtPF;
        int genWeight;
        int nPU;
};

#endif