/******************************************************************************
* Copyright (c) 2011, Michael P. Gerlek (mpg@flaxen.com)
*
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in
*       the documentation and/or other materials provided
*       with the distribution.
*     * Neither the name of Hobu, Inc. or Flaxen Geo Consulting nor the
*       names of its contributors may be used to endorse or promote
*       products derived from this software without specific prior
*       written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
****************************************************************************/

#ifndef INCLUDED_DRIVERS_LIBLAS_LIBLASREADER_HPP
#define INCLUDED_DRIVERS_LIBLAS_LIBLASREADER_HPP

#include <libpc/libpc.hpp>

#include <vector>

#include <libpc/Stage.hpp>
#include <libpc/drivers/las/Support.hpp>
#include <libpc/drivers/las/ReaderBase.hpp>

// fwd decls
namespace liblas
{
    class Reader;
}

namespace libpc { namespace drivers { namespace liblas {

class LiblasHeader;

class LIBPC_DLL LiblasReader : public libpc::drivers::las::LasReaderBase
{
public:
    LiblasReader(const std::string& filename);
    ~LiblasReader();

    const std::string& getName() const;

    const std::string& getFileName() const;

    ::libpc::drivers::las::PointFormat getPointFormat() const;
    
    boost::uint8_t getVersionMajor() const;
    boost::uint8_t getVersionMinor() const;

    int getMetadataRecordCount() const;
    const MetadataRecord& getMetadataRecord(int index) const;

    const SpatialReference& getSpatialReference() const;

    bool supportsIterator (StageIteratorType t) const
    {   
        if (t == StageIterator_Sequential ) return true;
        if (t == StageIterator_Random ) return true;
        
        return false;
    }

    libpc::SequentialIterator* createSequentialIterator() const;
    libpc::RandomIterator* createRandomIterator() const;

private:
    void processExternalHeader(::liblas::Reader& externalReader);
    void registerFields(::liblas::Reader& externalReader);
    MetadataRecord& getMetadataRecordRef(int index);

    std::string m_filename;

    // LAS header properties of interest to us
    boost::uint8_t m_versionMajor;
    boost::uint8_t m_versionMinor;
    double m_scaleX;
    double m_scaleY;
    double m_scaleZ;
    double m_offsetX;
    double m_offsetY;
    double m_offsetZ;
    bool m_isCompressed;
    
    ::libpc::drivers::las::PointFormat m_pointFormat;

    std::vector<MetadataRecord> m_metadataRecords;

    LiblasReader& operator=(const LiblasReader&); // not implemented
    LiblasReader(const LiblasReader&); // not implemented
};


} } } // namespaces

#endif
