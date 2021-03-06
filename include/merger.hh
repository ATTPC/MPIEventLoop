/* Copyright (c) 2016- Chris Sullivan */
/* See the file "LICENSE" for the full license governing this code. */

#include <iostream>
#include <sstream>
#include <string>
#include<stdio.h>

using namespace std;

int merge(const char* path, int outputidx, int level, int* files, size_t size) {

  stringstream cmd; cmd.str(""); cmd << "hadd -f ";
  cmd << path << "/" << level+1 << "_" << outputidx << ".root ";
  for (uint32_t i=0; i<size; i++) {
    cmd << path << "/" << level << "_" << files[i] << ".root ";
  }
  //cout <<"Rank: "<<outputidx << " - " << cmd.str() <<endl;
  system(cmd.str().c_str());
  return 0;
}
int mt_binarytree_merge(const char* outputfile, const char* path, int nmergers, const int& rank, const int& mpisize) {
  if (mpisize <= 1) {
    stringstream cmd; cmd.str(""); cmd << "mv " << path <<"/0_0.root " << outputfile;
    system(cmd.str().c_str());
    return 0;
  }
  if ( rank < nmergers) {
    int nfiles = mpisize;
    int nfilestomerge_perthread = 0;
    int level = 0;
    do {

      if ( rank < nmergers) {

        nfilestomerge_perthread = nfiles/nmergers;
        int remainder = nfiles - nfilestomerge_perthread*nmergers;

        if (remainder != 0 && rank == nmergers-1) {

          int *files = new int[nfilestomerge_perthread+remainder];
          int idxfile = 0;
          for (int i=nfilestomerge_perthread*rank; i < nfilestomerge_perthread*(rank+1)+remainder; i++) {
            files[idxfile]=i;
            idxfile++;
          }
          merge(path,rank,level,files,nfilestomerge_perthread);

          delete[] files;
        } else {

          int *files = new int[nfilestomerge_perthread];
          int idxfile = 0;
          for (int i=nfilestomerge_perthread*rank; i < nfilestomerge_perthread*(rank+1); i++) {
            files[idxfile]=i;
            idxfile++;
          }
          merge(path,rank,level,files,nfilestomerge_perthread);
          delete[] files;
        }

        nfiles = nmergers;
        nmergers /= 2;
        level++;

      } else { break; }

    } while (nmergers > 0);


    if (rank == 0) {
      stringstream cmd; cmd.str(""); cmd << "mv " << path <<"/"<<level-1<<"_0.root " << outputfile;
      system(cmd.str().c_str());
    }
  }

  return 0;
}
