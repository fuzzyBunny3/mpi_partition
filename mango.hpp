#ifndef MANGO_H
#define MANGO_H

#include<mpi.h>

namespace mango {

  //////////////////////////////////////////////////////////////////////////////////////
  // Items related to partitioning the processors into worker groups:

  class MPI_Partition_test;

  class MPI_Partition {
    friend class MPI_Partition_test;

  protected: // Must be protected rather than private so unit testing can access non-public variables.
    MPI_Comm comm_world;
    MPI_Comm comm_worker_groups;
    MPI_Comm comm_group_leaders;
    int N_procs_world;
    int rank_world;
    int N_procs_worker_groups;
    int rank_worker_groups;
    int N_procs_group_leaders;
    int rank_group_leaders;
    int worker_group;
    bool proc0_world;
    bool proc0_worker_groups;
    int N_worker_groups;
    bool initialized;

    void verify_initialized();
    void print();

  public:
    int verbose;

    MPI_Partition();
    ~MPI_Partition();
    void init(MPI_Comm);
    void set_custom(MPI_Comm, MPI_Comm, MPI_Comm);
    MPI_Comm get_comm_world();
    MPI_Comm get_comm_worker_groups();
    MPI_Comm get_comm_group_leaders();
    bool get_proc0_world();
    bool get_proc0_worker_groups();
    int get_rank_world();
    int get_rank_worker_groups();
    int get_rank_group_leaders();
    int get_N_procs_world();
    int get_N_procs_worker_groups();
    int get_N_procs_group_leaders();
    int get_worker_group();
    int get_N_worker_groups();
    void set_N_worker_groups(int);
  };

}

#endif
