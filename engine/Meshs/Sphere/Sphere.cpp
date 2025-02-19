#include "Sphere.h"

Sphere::Sphere() : Mesh()
{
    CreateSphere();
}

Sphere::Sphere(const bool _generatePos, const bool _generateUV, const bool _generateIndices, const bool _generateNormales) : Mesh(), mNbVertexAzimut(20), mNbVertexElevation(20)
{
    CreateSphere(_generatePos, _generateUV, _generateIndices, _generateNormales);
}

Sphere::Sphere(const int _nbVertexAzimut, const int _nbVertexElevation) : mNbVertexAzimut(_nbVertexAzimut), mNbVertexElevation(_nbVertexElevation)
{
    CreateSphere();
}

void Sphere::CreateSphere(const bool _generatePos, const bool _generateUV, const bool _generateIndices, const bool _generateNormales)
{
    if(_generatePos)
    {
        CreateVerticesPositions();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);
    }

    if(_generateUV)
    {
        CreateVerticesUVs();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_UVS);
    }

    if(_generateIndices)
    {
        CreateIndices();
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);
    }

    if(_generateNormales)
    {
        CreateVerticesNormales(mPositions);
        RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_NORMALE);
    }
}

vec3 Sphere::SphericalCoordinatesToEuclidean(const float _azimut , const float _elevation) {
    return vec3(cos(_azimut) * cos(_elevation), sin(_elevation), sin(_azimut) * cos(_elevation));
}

void Sphere::CreateVerticesPositions()
{
    float _stepAzimut = 2*M_PI/(float)(mNbVertexAzimut-1);
    float _stepElevation = M_PI/(float)(mNbVertexElevation-1);

    mPositions.clear();
    mPositions.resize(mNbVertexAzimut * mNbVertexElevation);
    
    for(int _azimutIndex = 0; _azimutIndex < mNbVertexAzimut; ++_azimutIndex)
        for(int _elevationIndex = 0; _elevationIndex < mNbVertexElevation; ++_elevationIndex)
            mPositions[_azimutIndex * mNbVertexElevation + _elevationIndex] = SphericalCoordinatesToEuclidean(_azimutIndex * _stepAzimut, -(_elevationIndex -(mNbVertexElevation-1)/2.)  * _stepElevation);
}

void Sphere::CreateVerticesUVs()
{
    mUVs.clear();
    mUVs.resize(mNbVertexAzimut * mNbVertexElevation);
    
    for(int _azimutIndex = 0; _azimutIndex < mNbVertexAzimut; ++_azimutIndex)
        for(int _elevationIndex = 0; _elevationIndex < mNbVertexElevation; ++_elevationIndex)
            mUVs[_azimutIndex * mNbVertexElevation + _elevationIndex] = vec2(_azimutIndex/(float)(mNbVertexAzimut-1), _elevationIndex/(float)(mNbVertexElevation-1));
}

void Sphere::CreateIndices()
{
    mIndices.clear();
    
    for(int _azimutIndex = 0; _azimutIndex < mNbVertexAzimut; ++_azimutIndex)
        for(int _elevationIndex = 0; _elevationIndex < mNbVertexElevation-1; ++_elevationIndex)
        {
            int _nextOnAzimut = _azimutIndex+1 >= mNbVertexAzimut ? 0 : _azimutIndex+1;
            mIndices.push_back(_azimutIndex*mNbVertexElevation + _elevationIndex);
            mIndices.push_back(_azimutIndex*mNbVertexElevation + _elevationIndex+1);
            mIndices.push_back(_nextOnAzimut*mNbVertexElevation + _elevationIndex+1);

            mIndices.push_back(_azimutIndex*mNbVertexElevation + _elevationIndex);
            mIndices.push_back(_nextOnAzimut*mNbVertexElevation + _elevationIndex+1);
            mIndices.push_back(_nextOnAzimut*mNbVertexElevation + _elevationIndex);
        }
}

void Sphere::CreateVerticesNormales(const vector<vec3>& _positions)
{
    mNormales.clear();
    mNormales.resize(mNbVertexAzimut * mNbVertexElevation);

    vector<unsigned int> _neighboors = vector<unsigned int>(mPositions.size());
    unsigned int _nbIndices = mIndices.size();
    for(int i = 0; i < _nbIndices; i+=3)
    {   
        //Get Indices
        unsigned int _index0 = mIndices[i];
        unsigned int _index1 = mIndices[i+1];
        unsigned int _index2 = mIndices[i+2];

        //Increm. neighboors
        ++_neighboors[_index0];
        ++_neighboors[_index1];
        ++_neighboors[_index2];

        //Normale triangle
        vec3 _pos0 = mPositions[_index0];
        vec3 _pos1 = mPositions[_index1];
        vec3 _pos2 = mPositions[_index2];
        vec3 _triangleNormales = normalize(cross(_pos2-_pos0, _pos1-_pos0));

        //Add normal triangle
        mNormales[_index0] += _triangleNormales;
        mNormales[_index1] += _triangleNormales;
        mNormales[_index2] += _triangleNormales;
    }

    //Get Normale per vertex
    unsigned int _nbVertex = mNormales.size();
    for(int i = 0; i < _nbVertex; ++i)
    {   
        mNormales[i] /= (float)_neighboors[i];
        mNormales[i] = normalize(mNormales[i]);
    }
}