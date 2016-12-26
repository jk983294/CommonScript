#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

const int K = 4;                            // data count in one block
const int M = 8;                            // memory block count & sub-table content count
const int MEMORY_INPUT_BLOCKS = M - 1;
const int N = 56;                           // disk block count = M * (M - 1)


class Block
{
public:
    Block(vector<int> data) : data(data), currentDataIndex(0) {}
    Block()
    {
        data.resize(K);
        currentDataIndex = 0;
    }
    ~Block() {}

    void load(Block& block)
    {
        copy(begin(block.data), end(block.data), begin(data));
        currentDataIndex = 0;
    }

    int getNextAvailableData()
    {
        return data[currentDataIndex];
    }

public:
    vector<int> data;
    int currentDataIndex;
};

class DiskBlocks
{
public:
    DiskBlocks(){}
    ~DiskBlocks(){}

public:
    vector<Block> blocks;
};

class MemoryBlocks
{
public:
    MemoryBlocks()
    {
        blocks.resize(M);
        wholeMemory.resize(M * K);
    }
    ~MemoryBlocks(){}

    void sortWholeMemoryAndWriteBack2Disk(vector<Block>::iterator from, vector<Block>::iterator to)
    {
        // copy disk M blocks into memory blocks
        mIndex = 0;
        for (auto i = from; i < to; ++i)
        {
            copy(begin(i->data), end(i->data), begin(wholeMemory) + mIndex);
            mIndex += K;
        }
        // in memory sort
        sort(begin(wholeMemory), end(wholeMemory));
        // write back to disk blocks
        mIndex = 0;
        for (auto i = from; i < to; ++i)
        {
            copy(begin(wholeMemory) + mIndex, begin(wholeMemory) + mIndex + K, begin(i->data));
            mIndex += K;
        }
    }

    void secondarySort(DiskBlocks &diskBlocks){
        outputCount = 0;
        vector<int> nextAvailableSubTableBlockIndex(MEMORY_INPUT_BLOCKS, 1);

        // load all sub table's first block into memory, the last memory block is output block
        for (int i = 0; i < MEMORY_INPUT_BLOCKS; i++)
        {
            blocks[i].load(diskBlocks.blocks[i * M]);
        }

        int minValue = numeric_limits<int>::max(), minValueBlockIndex = -1;
        while (true)
        {
            minValue = numeric_limits<int>::max();
            minValueBlockIndex = -1;
            for (int i = 0; i < MEMORY_INPUT_BLOCKS; i++)
            {
                // if sub-table has available block, then load into memory
                if (blocks[i].currentDataIndex >= K)
                {
                    if (nextAvailableSubTableBlockIndex[i] < M)
                    {
                        blocks[i].load(diskBlocks.blocks[i * M + nextAvailableSubTableBlockIndex[i]]);
                        ++nextAvailableSubTableBlockIndex[i];
                    }
                }

                if (blocks[i].currentDataIndex < K && blocks[i].getNextAvailableData() < minValue)
                {
                    minValue = blocks[i].getNextAvailableData();
                    minValueBlockIndex = i;
                }
            }

            if (minValueBlockIndex < 0)
                return;
            else
            {
                ++blocks[minValueBlockIndex].currentDataIndex;
                outputCursorData(minValue);
            }
        }
    }

    void outputCursorData(int value)
    {
        cout << value << "\t";
        ++outputCount;
        if (outputCount % K == 0)
            cout << endl;
    }

public:
    vector<Block> blocks;
    vector<int> wholeMemory;
    int mIndex;
    int outputCount;
};



class TwoPhaseMultiwayMergeSort
{
public:
    static void sort(DiskBlocks &diskBlocks, MemoryBlocks& memoryBlocks)
    {
        // phase I, sort in memory to make all sub-table ordered, [0, M), [M, 2M) ......
        auto blockIter = diskBlocks.blocks.begin();
        while (blockIter + M != diskBlocks.blocks.end())
        {
            memoryBlocks.sortWholeMemoryAndWriteBack2Disk(blockIter, blockIter + M);
            blockIter += M;
        }

        // phase II
        memoryBlocks.secondarySort(diskBlocks);
    }
};


int main()
{
    srand((unsigned)time(nullptr));

    DiskBlocks diskBlocks;
    MemoryBlocks memoryBlocks;

    // prepare disk block data
    for (int i = 0; i < N; i++)
    {
        vector<int> data;
        for (int i = 0; i < K; i++)
        {
            data.push_back(rand());
        }
        diskBlocks.blocks.push_back({ data });
    }

    TwoPhaseMultiwayMergeSort::sort(diskBlocks, memoryBlocks);

    return 0;
}