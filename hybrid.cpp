#include <fstream>
#include <unordered_map>
#include <string>
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <mpi.h>
#include <queue>

using namespace std;
#define REQUEST 1;
#define ASSIGN 2;

void process_word(string &w) {
    // Remove punctuation at beginning
    while (!w.empty() && ispunct(w[0])) {
        w.erase(0, 1);
    }
    // Remove punctuation at end
    while (!w.empty() && ispunct(w[w.size() - 1])) {
        w.pop_back();
    }
    // Convert all letters to lowercase
    for (size_t i = 0; i < w.length(); ++i) {
        if (isupper(w[i])) {
            w[i] = tolower(w[i]);
        }
    }
}

int hash_str(string s, int R) {
    int sum = 0;
    for (unsigned char c : s) {
        sum  += c;
    }
    return sum % R;
}

void send_intermediate(int sender, int recvr, void* result) {
    /*
    send mapper output 
    */
}

void recv_intermediate(int sender, int recvr, void *dest, void* result) {
/*
reducers listen for messages from mappers 
*/
}

int main(int argc, char** argv) {

    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, 0);
    
    int rank, world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //list of all files to be read
    // master node sends index of this list to workers for reading
    int n_files = argc - 1; 
    vector<string> all_files;
    all_files.reserve(n_files)
    for(int i = 1; i < argc; i++) all_files.emplace_back[argv[i]]

    if(rank == 0) {
        int next = 0;
        int n_workers = world_size - 1;
        int done = 0;
        MPI_Status status;
        
        while(done < n_workers) {
            int signal;

            MPI_Recv(&signal, 1, MPI_INT, 
                MPI_ANY_SOURCE, REQUEST, 
                MPI_COMM_WORLD, status);
            
            int worker = status.MPI_SOURCE:
            int file_index;
            if(next < n_files) file_index = next++;
            else {
                file_index = -1;
                done++;
            }
            
            MPI_Send(&file_index, 1, MPI_INT,
                worker, ASSIGN, MPI_COMM_WORLD);
        }

    }
    else{
    
        # pragma omp parallel {       
            # pragma omp single { 
                while(true){
                    int signal = 0;
                    MPI_send(&signal, 1, MPI_INT,
                        0, REQUEST, MPI_COMM_WORLD);

                    int file_index;
                    MPI_Recv(&file_index, 1, MPI_INT,
                        0, ASSIGN, MPI_COMM_WORLD);
                    
                    if(file_index < 0) break;

                    string filename = all_files[file_index];

                    #pragma omp task firstprivate(filename) {
                        read_file(filename);
                    }
                }
                # pragma omp taskwait
            }
        }


    }






}