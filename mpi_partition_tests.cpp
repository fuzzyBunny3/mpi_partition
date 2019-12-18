#define BOOST_TEST_MODULE mpi_partition tests
#include <boost/test/included/unit_test.hpp>
//#include <boost/test/unit_test.hpp>

#include<stdexcept>
#include "mango.hpp"
#include "mpi.h"

// See the discussion of Boost towards the end of here: https://stackoverflow.com/questions/3676664/unit-testing-of-private-methods
namespace mango {
  class MPI_Partition_test: public MPI_Partition {};
}

BOOST_FIXTURE_TEST_SUITE(SomeTests, mango::MPI_Partition_test)

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
  set_N_worker_groups(1);
  init(MPI_COMM_WORLD);
  BOOST_TEST(rank_world == 0);
}

BOOST_AUTO_TEST_CASE(test_mpi_partition_init_private2) {
  set_N_worker_groups(2);
  init(MPI_COMM_WORLD);
  BOOST_TEST(rank_world == 0);
}

BOOST_AUTO_TEST_SUITE_END()
