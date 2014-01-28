/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright Hydro-Quebec - IREQ, 2008
     \\/     M anipulation  |
-------------------------------------------------------------------------------
  License
  This file is part of OpenFOAM.

  OpenFOAM is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFOAM; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

Authors
  Robert Magnan,  Hydro-Quebec - IREQ, 2007

\*---------------------------------------------------------------------------*/
//------------------------------------------------------------------------------
//
// Local class encapsulating some conversion requests
// on a CGNS element type
//
//------------------------------------------------------------------------------
#include "libcgnsoo3/cgnsoo.H"

#include "cellModeller.H"
#include "cellModel.H"
#include "string.H"

class CGNSElementType
{
public:
	static int getNumberOfNodesPerElement( CGNSOO::ElementType_t etype )
	{
		using namespace CGNSOO;
		switch( etype )
		{
		case NODE:
			return 1;
		case BAR_2:
			return 2;
		case BAR_3:
			return 3;
		case TRI_3:
			return 3;
		case TRI_6:
			return 6;
		case QUAD_4:
			return 4;
		case QUAD_8:
			return 8;
		case QUAD_9:
			return 9;
		case TETRA_4:
			return 4;
		case TETRA_10:
			return 10;
		case PYRA_5:
			return 5;
		case PYRA_14:
			return 14;
		case PENTA_6:
			return 6;
		case PENTA_15:
			return 15;
		case PENTA_18:
			return 18;
		case HEXA_8:
			return 8;
		case HEXA_20:
			return 20;
		case HEXA_27:
			return 27;
		case ElementTypeNull:
		case ElementTypeUserDefined:
		case NGON_n:
		case MIXED:
			return -1;
		}
		return -1;
	}
	static std::string enumToString( CGNSOO::ElementType_t etype )
	{
		using namespace CGNSOO;
		switch( etype )
		{
		case NODE:
			return "NODE";
		case BAR_2:
			return "BAR_2";
		case BAR_3:
			return "BAR_3";
		case TRI_3:
			return "TRI_3";
		case TRI_6:
			return "TRI_6";
		case QUAD_4:
			return "QUAD_4";
		case QUAD_8:
			return "QUAD_8";
		case QUAD_9:
			return "QUAD_9";
		case TETRA_4:
			return "TETRA_4";
		case TETRA_10:
			return "TETRA_10";
		case PYRA_5:
			return "PYRA_5";
		case PYRA_14:
			return "PYRA_14";
		case PENTA_6:
			return "PENTA_6";
		case PENTA_15:
			return "PENTA_15";
		case PENTA_18:
			return "PENTA_18";
		case HEXA_8:
			return "HEXA_8";
		case HEXA_20:
			return "HEXA_20";
		case HEXA_27:
			return "HEXA_27";
		case ElementTypeNull:
			return "Null";
		case ElementTypeUserDefined:
			return "UserDefined";
		case NGON_n:
			return "NGON_n";
		case MIXED:
			return "MIXED";
		}
		return "Error - Unknown";
	}
	static const Foam::cellModel& getFoamCellModel( CGNSOO::ElementType_t etype )
	{
		using namespace CGNSOO;
		Foam::string dictEntry = "unknown";
		switch ( etype )
		{
        	case TETRA_4:
                	dictEntry = "tet"; break;
        	case PYRA_5:
                	dictEntry = "pyr"; break;
        	case PENTA_6:
                	dictEntry = "prism"; break;
        	case HEXA_8:
                	dictEntry = "hex"; break;
		default:
			break;
		}
     
		return *(Foam::cellModeller::lookup(dictEntry));
	}
	static bool is2D( CGNSOO::ElementType_t etype )
	{
		using namespace CGNSOO;
		switch ( etype )
		{
        	case TETRA_4:
        	case PYRA_5:
        	case PENTA_6:
        	case HEXA_8:
                	return false;
		default:
			break;
		}
		return true;
 	}
};
