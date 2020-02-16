#define CATCH_CONFIG_RUNNER
#include "mpi.h"
#include "catch_mpi.hpp"

#include<stdexcept>
#include "mango.hpp"

// main() taken from https://stackoverflow.com/questions/58289895/is-it-possible-to-use-catch2-for-testing-an-mpi-code
int main( int argc, char* argv[] ) {
  MPI_Init(&argc, &argv);
  int result = Catch::Session().run( argc, argv );
  MPI_Finalize();
  return result;
}

// Also taken from https://stackoverflow.com/questions/58289895/is-it-possible-to-use-catch2-for-testing-an-mpi-code
/*
namespace Catch{
  void ConsoleReporter::testRunEnded(TestRunStats const& _testRunStats) {
    int rank_id = -1;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_id);
    if(rank_id != 0 && testRunStats.totals.testCases.allPassed())
      return;
    printTotalsDivider(_testRunStats.totals);
    printTotals(_testRunStats.totals);
    stream << std::endl;
    StreamingReporterBase::testRunEnded(_testRunStats);
  }
}
*/

TEST_CASE("first try", "[firsttry]") {
  CHECK(1+1 == 3);
}

TEST_CASE("silly", "[trivial]") {
  CHECK(true);
}

TEST_CASE("verify_get_before_initialized_causes_exception","[mpi]") {
  
  mango::MPI_Partition mpi_partition;
  bool failed = false;
  try {
    mpi_partition.get_comm_world();
  } catch (const std::runtime_error& e) {
    failed = true;
  }
  REQUIRE(failed);
}

TEST_CASE("verify_get_before_initialized_causes_exception2","[mpi2]") {  
  mango::MPI_Partition mpi_partition;
  CHECK_THROWS(mpi_partition.get_comm_world());
}


TEST_CASE("test_mpi_partition_init","[init]") {
  mango::MPI_Partition mpi_partition;
  mpi_partition.set_N_worker_groups(1);
  mpi_partition.init(MPI_COMM_WORLD);
  CHECK(mpi_partition.get_rank_world() == 0);
}

class mango::MPI_Partition_test {
public:
  static void private_test_1();
};

void mango::MPI_Partition_test::private_test_1() {
  MPI_Partition mp;
  CHECK(mp.initialized == false);
  mp.init(MPI_COMM_WORLD);
  CHECK(mp.initialized);
}

TEST_CASE("private test 1","[private]") {
  mango::MPI_Partition_test::private_test_1();
}

///////////////////////////////////////////////////
// Trying to access private methods using fixtures
///////////////////////////////////////////////////

TEST_CASE_METHOD(mango::MPI_Partition, "private test 2", "[private]") {
  CHECK(!initialized);
  init(MPI_COMM_WORLD);
  CHECK(initialized);
}
