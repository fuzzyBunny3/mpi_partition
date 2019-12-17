#define BOOST_TEST_MODULE mpi_partition tests
#include <boost/test/included/unit_test.hpp>
//#include <boost/test/unit_test.hpp>

#include<stdexcept>
#include "mango.hpp"
#include "mpi.h"

// The test_mpi_partition class exists purely to expose private variables and methods, so they can be tested.
class mango::test_mpi_partition {
public:
  static int rank_world(MPI_Partition mp) {return mp.rank_world;};
};


// https://www.boost.org/doc/libs/1_71_0/libs/test/doc/html/boost_test/tests_organization/fixtures/global.html

struct GlobalFixture {
  GlobalFixture() {
    BOOST_TEST_MESSAGE( "GlobalFixture constructor");
    int err;
    err = MPI_Init(NULL,NULL);
  }
  void setup() {
    BOOST_TEST_MESSAGE( "GlobalFixture setup" );
  }
  void teardown() {
    BOOST_TEST_MESSAGE( "GlobalFixture teardown" );
  }
  ~GlobalFixture() {
    BOOST_TEST_MESSAGE( "GlobalFixture destructor" );
    MPI_Finalize();
  }
};

BOOST_TEST_GLOBAL_FIXTURE(GlobalFixture);

BOOST_AUTO_TEST_CASE(hello_world) {
  BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(verify_get_before_initialized_causes_exception) {
  
  mango::MPI_Partition mpi_partition;
  bool failed = false;
  try {
    mpi_partition.get_comm_world();
  } catch (const std::runtime_error& e) {
    BOOST_TEST_MESSAGE("Intential runtime_error in get_comm_world");
    failed = true;
  }
  BOOST_TEST(failed, "get_comm_world");
  
  BOOST_TEST(true);
}


BOOST_AUTO_TEST_CASE(test_mpi_partition_init) {
  mango::MPI_Partition mpi_partition;
  mpi_partition.set_N_worker_groups(1);
  mpi_partition.init(MPI_COMM_WORLD);
  BOOST_TEST(mpi_partition.get_rank_world() == 0);
}

// Can we access a private variable?
BOOST_AUTO_TEST_CASE(test_mpi_partition_init_private) {
  mango::MPI_Partition mpi_partition;
  mpi_partition.set_N_worker_groups(1);
  mpi_partition.init(MPI_COMM_WORLD);
  int rank_world = mango::test_mpi_partition::rank_world(mpi_partition);
  BOOST_TEST(rank_world == 0);
}
