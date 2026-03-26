#ifndef FILEASF_H
#define FILEASF_H

#include <string>
#include <vector>
#include <fstream>
#include "fileRecord.h"

enum recordState : int {
    BORRADO = 0,
    ACTIVO = 1
};

class fileASF {
private:
    // Almacenamiento en bloques de bytes (byte-level) para garantizar
    // la correspondencia exacta con el disco sin recodificación.
    std::string diskFilename;
    std::fstream diskFile;
    std::vector<char> fileHeader;
    std::vector<char> blockInMemory;
    bool hasHeaderChanged;
    bool hasBlockChanged;
    int loadedBlockId;
    int currentBlockId;
    int currentRecordIndex;

    int getHeaderSize();
    int getBlockCount();
    int getRecordCount();
    int getBlockSize();
    int getBlockHeaderSize();
    int getRecordHeaderSize();
    int getAttributeCount();
    int getRecordDataSize();
    int getRecordSize();
    int getRecordsPerBlock();

    std::vector<char> buildRecordStructure();

    void readBlockFromDisk(int blockId);
    void writeBlockToDisk();
    void readFileHeaderFromDisk();
    void writeFileHeaderToDisk();

    int readInt(const std::vector<char>& buffer, int offset);
    void writeInt(std::vector<char>& buffer, int offset, int value);

public:
    fileASF();

    void create(const std::string& filename,
                int blockSize,
                int blockHeaderSize,
                int recordHeaderSize,
                const std::vector<campType>& types,
                const std::vector<int>& lengths);
    void open(const std::string& filename);
    void close();

    void insertRecord(const fileRecord& record);
    bool readNextRecord(fileRecord& record);
    bool findRecord(int recordId, fileRecord& record);
    bool deleteRecord(int recordId);
    bool modifyRecord(int recordId, const fileRecord& record);
    void resetRead();
};

#endif
