//  OF-extend Revision: $Id: timelineFunctionObject.C 602 2008-04-28 16:13:09Z bgschaid $ 
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright  held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is based on OpenFOAM.

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
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*---------------------------------------------------------------------------*/

#include "timelineFunctionObject.H"
#include "addToRunTimeSelectionTable.H"

#include "polyMesh.H"
#include "IOmanip.H"
#include "Time.H"

#include "OFstream.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(timelineFunctionObject, 0);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

timelineFunctionObject::timelineFunctionObject
(
    const Time& t,
    const dictionary& dict
)
:
    simpleDataFunctionObject(t,dict),
    factor_(
        dict.found("factor")
        ? readScalar(dict.lookup("factor"))
        : 1.
    )
{
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void timelineFunctionObject::flush()
{
    forAllIter(HashPtrTable<OFstream>, filePtrs_, iter)
    {
        (*iter()).flush();
    }
}

bool timelineFunctionObject::start()
{
    simpleDataFunctionObject::start();

    if (Pstream::master())
    {
        wordList names(fileNames());

        // Check if any fieldNames have been removed. If so close
        // the file.

        forAllIter(HashPtrTable<OFstream>, filePtrs_, iter)
        {
            if (findIndex(names, iter.key()) == -1)
            {
                // Field has been removed. Close file
                delete filePtrs_.remove(iter);
            }
        }

        // Open new files for new fields. Keep existing files.

        filePtrs_.resize(2*names.size());

        forAll(names,fileI)
        {
            const word& fldName = names[fileI];

            // Check if added field. If so open a stream for it.

            if (!filePtrs_.found(fldName))
            {
                fileName theDir=dataDir();
                
                OFstream* sPtr = new OFstream(theDir/fldName);

                filePtrs_.insert(fldName, sPtr);

                *sPtr<< '#' << setw(IOstream::defaultPrecision() + 6)
                    << "Time" << token::SPACE << firstLine().c_str() << nl;
            }
        }
    }

    return true;
}


} // namespace Foam

// ************************************************************************* //
