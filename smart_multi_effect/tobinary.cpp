#include "tobinary.h"

//template<typename T>
//size_t VectorToBinary(std::ofstream& fout, std::vector<T> &vec)
//{
//    size_t vecSize = vec.size();
//    fout.write((char*)&vecSize, sizeof (T));
//    fout.write((char*)&vec[0], vecSize * sizeof (T));

//    return vecSize;
//}

//template<typename T>
//void BinaryToVector(std::ifstream &fin, std::vector<T> &vec)
//{
//    size_t vecSize = 0;
//    fin.read((char*)&vecSize, sizeof (size_t));
//    vec.resize(vecSize);
//    fin.read((char*)&vec[0], vecSize * sizeof (T));
//}
