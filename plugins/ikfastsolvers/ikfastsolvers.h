// -*- coding: utf-8 -*-
// Copyright (C) 2006-2012 Rosen Diankov <rosen.diankov@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef OPENRAVE_PLUGIN_IKFASTSOLVERS_H
#define OPENRAVE_PLUGIN_IKFASTSOLVERS_H

#include "plugindefs.h"
#include <boost/lexical_cast.hpp>
#include <openrave/plugin.h>

//namespace ik_barrettwam { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_pa10 { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_puma { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_pr2_head { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_pr2_head_torso { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_pr2_leftarm { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_pr2_leftarm_torso { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_pr2_rightarm { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_pr2_rightarm_torso { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_schunk_lwa3 { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_katana5d { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }
//namespace ik_katana5d_trans { IkSolverBasePtr CreateIkSolver(EnvironmentBasePtr, std::istream& sinput, const std::vector<dReal>&vfreeinc); }

OpenRAVE::IkSolverBasePtr CreateIkSolverFromName(const string& _name, const std::vector<dReal>& vfreeinc, dReal ikthreshold, OpenRAVE::EnvironmentBasePtr penv);
OpenRAVE::ModuleBasePtr CreateIkFastModule(OpenRAVE::EnvironmentBasePtr penv, std::istream& sinput);
void DestroyIkFastLibraries();

struct IKFastSolversPlugin : public RavePlugin {
    IKFastSolversPlugin()
    {
        _interfaces[PT_Module].push_back("ikfast");
        _interfaces[PT_IkSolver].push_back("ikfast");
        //_interfaces[PT_IkSolver].push_back("wam7ikfast");
        //_interfaces[PT_IkSolver].push_back("pa10ikfast");
        //_interfaces[PT_IkSolver].push_back("pumaikfast");
        //_interfaces[PT_IkSolver].push_back("ikfast_pr2_head");
        //_interfaces[PT_IkSolver].push_back("ikfast_pr2_head_torso");
        //_interfaces[PT_IkSolver].push_back("ikfast_pr2_rightarm");
        //_interfaces[PT_IkSolver].push_back("ikfast_pr2_rightarm_torso");
        //_interfaces[PT_IkSolver].push_back("ikfast_pr2_leftarm");
        //_interfaces[PT_IkSolver].push_back("ikfast_pr2_leftarm_torso");
        //_interfaces[PT_IkSolver].push_back("ikfast_schunk_lwa3");
        //_interfaces[PT_IkSolver].push_back("ikfast_katana5d");
        //_interfaces[PT_IkSolver].push_back("ikfast_katana5d_trans");
    }

    ~IKFastSolversPlugin() override
    {
        Destroy();
    }

    void Destroy() override
    {
        DestroyIkFastLibraries();
    }

    OpenRAVE::InterfaceBasePtr CreateInterface(OpenRAVE::InterfaceType type, const std::string& interfacename, std::istream& sinput, OpenRAVE::EnvironmentBasePtr penv) override
    {
        switch(type) {
        case PT_IkSolver: {
            if( interfacename == "ikfast" ) {
                string ikfastname;
                sinput >> ikfastname;
                if( !!sinput ) {
                    // check if ikthreshold parameter exists
                    dReal ikthreshold=1e-4;
                    std::vector<dReal> vfreeinc;
                    std::string paramname;
                    sinput >> paramname;
                    if( !!sinput ) {
                        if( paramname == "ikthreshold" ) {
                            sinput >> ikthreshold;
                        }
                        else {
                            // most likely a free inc parameter
                            vfreeinc.push_back(boost::lexical_cast<dReal>(paramname));
                        }
                    }
                    // have to append any left over numbers
                    vector<dReal> vfreeinctemp((istream_iterator<dReal>(sinput)), istream_iterator<dReal>());
                    vfreeinc.insert(vfreeinc.end(), vfreeinctemp.begin(), vfreeinctemp.end());

                    // look at all the ikfast problem solvers
                    OpenRAVE::IkSolverBasePtr psolver = CreateIkSolverFromName(ikfastname, vfreeinc, ikthreshold, penv);
                    if( !!psolver ) {
                        return psolver;
                    }
                }
            }
    //        else {
    //            vector<dReal> vfreeinc((istream_iterator<dReal>(sinput)), istream_iterator<dReal>());
    //            if( interfacename == "wam7ikfast" ) {
    //                return ik_barrettwam::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "pa10ikfast" ) {
    //                return ik_pa10::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "pumaikfast" ) {
    //                return ik_puma::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "ikfast_pr2_head" ) {
    //                return ik_pr2_head::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "ikfast_pr2_head_torso" ) {
    //                return ik_pr2_head_torso::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "ikfast_pr2_rightarm" ) {
    //                return ik_pr2_rightarm::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "ikfast_pr2_rightarm_torso" ) {
    //                return ik_pr2_rightarm_torso::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "ikfast_pr2_leftarm" ) {
    //                return ik_pr2_leftarm::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "ikfast_pr2_leftarm_torso" ) {
    //                return ik_pr2_leftarm_torso::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "ikfast_schunk_lwa3" ) {
    //                return ik_schunk_lwa3::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "ikfast_katana5d" ) {
    //                return ik_katana5d::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //            else if( interfacename == "ikfast_katana5d_trans" ) {
    //                return ik_katana5d_trans::CreateIkSolver(penv, sinput, vfreeinc);
    //            }
    //        }
            break;
        }
        case PT_Module:
            if( interfacename == "ikfast") {
                return CreateIkFastModule(penv,sinput);
            }
            break;
        default:
            break;
        }

        return OpenRAVE::InterfaceBasePtr();
    }

    const InterfaceMap& GetInterfaces() const override
    {
        return _interfaces;
    }

    const std::string& GetPluginName() const override
    {
        static std::string pluginname = "IKFastSolversPlugin";
        return pluginname;
    }

private:
    InterfaceMap _interfaces;
};

#endif // OPENRAVE_PLUGIN_IKFASTSOLVERS_H