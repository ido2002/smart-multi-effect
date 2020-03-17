#ifndef TOBINARY_H
#define TOBINARY_H

#include <vector>
#include <fstream>

template<typename T>
size_t VectorToBinary(std::ofstream& fout, std::vector<T> &vec)
{
    uint64_t vecSize = vec.size();
    fout.write((char*)&vecSize, sizeof (uint64_t));
    fout.write((char*)&vec[0], vecSize * sizeof (T));

    return vecSize;
}

template<typename T>
void BinaryToVector(std::ifstream &fin, std::vector<T> &vec)
{
    uint64_t vecSize = 0;
    fin.read((char*)&vecSize, sizeof (uint64_t));
    vec.resize(vecSize);
    fin.read((char*)&vec[0], vecSize * sizeof (T));
}

#endif // TOBINARY_H
