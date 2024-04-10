#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#ifndef CacheSimulator_hpp
#define CacheSimulator_hpp
using namespace std;

struct CacheBlock {
      int tag;
      int index; 
      // ideally I should have allocated 64bytes of memory data[]
      bool valid;
      int lru;
      int fifo;
      CacheBlock() : tag(0), index(0), valid(false), lru(0), fifo(0) {}
    };
    struct Set{
        vector<CacheBlock> blocks;
        int accessNum=0;
        Set(int associativity){
            blocks.resize(associativity);
            for(auto b: blocks){
                b.valid=false;
            }
        }
    };

class CacheSimulator {
  public:
    std::vector<Set> cache;
    int cacheSize;
    int blockSize;
    int numBlocks;
    int associativity;
    int numSets;
    int policy;

    std::pair<int, int> splitAddress(int address) 
    {
      // variable address if for byte
      int num_bits_offset = std::log2(blockSize);
      address = address >> num_bits_offset;
      int index = address & ((1 << (int)log2(numSets)) - 1);
      int tag = address >> (int)log2(numSets);
      return std::make_pair(tag, index);
    }

    int hits = 0, misses = 0;
    void set(int _cacheSize, int _blockSize, int _associativity,int _policy) 
      {
        cacheSize = _cacheSize;
        blockSize = _blockSize;
        associativity = _associativity;
        policy=_policy;
        assert (cacheSize % blockSize == 0);
        numBlocks = cacheSize / blockSize;
        numSets= numBlocks / associativity;
        cache.resize(numSets, Set(associativity));
      }

    bool access (int address) {
      // split the address: |---------tag --------------| --index---| --offset---|
      auto a = splitAddress(address);
      int index = a.second;
      int tag = a.first;
      cache[index].accessNum++;
      for (auto &b : cache[index].blocks) {
        if (b.valid && b.tag == tag) {
          b.lru=cache[index].accessNum;
          hits++;
          return true;
        }
      }
      misses++;
      for(auto &b: cache[index].blocks){
          if(!b.valid){
              b.valid=true;
              b.tag=tag;
              b.lru=cache[index].accessNum;
              return false;
          }
      }
      // if no block is free, evict one
      if(policy==0){
          // LRU
          int min=INT_MAX;
          int minIndex=-1;
          for(int i=0;i<cache[index].blocks.size();i++){
              if(cache[index].blocks[i].lru<min){
                  min=cache[index].blocks[i].lru;
                  minIndex=i;
              }
          }
          cache[index].blocks[minIndex].tag=tag;
          cache[index].blocks[minIndex].lru=cache[index].accessNum;
      }
      else if(policy==1){
        //Random
        int randomIndex=rand()%cache[index].blocks.size();
        cache[index].blocks[randomIndex].tag=tag;
        cache[index].blocks[randomIndex].lru=cache[index].accessNum;
          
      }
      return false;
    }
};
#endif //CacheSimulator_hpp














