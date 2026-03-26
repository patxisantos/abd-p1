#ifndef FILERECORD_H
#define FILERECORD_H

#include <vector>

enum campType : int {
    LOGICO = 0,
    CARACTER = 1,
    ENTERO = 2,
    REAL = 3,
    CADENA = 4
};

class fileRecord {
private:
    // Nota: el esquema del registro se mantiene en fileASF.fileHeader.
    // La copia de recordStructure aquí es opcional y puede omitirse en
    // implementaciones optimizadas para evitar duplicación de información.
    std::vector<char> recordStructure;
    std::vector<char> recordData;

public:
    fileRecord();
    fileRecord(const std::vector<char>& structure, const std::vector<char>& data);

    void setRecordStructure(const std::vector<char>& structure);
    void setRecordData(const std::vector<char>& data);

    const std::vector<char>& getRecordStructure() const;
    const std::vector<char>& getRecordData() const;
};

#endif
