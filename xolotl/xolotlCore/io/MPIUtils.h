#ifndef MPIBROADCASTER_H
#define MPIBROADCASTER_H

#include <mpi.h>
#include <memory>
#include <iostream>


namespace xolotlCore {

namespace MPIUtils {
<<<<<<< HEAD

=======
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
	/**
	 * Sends the input buffer from the master task to all the slaves
	 *
	 * This method blocks until it is called by all processes.
	 * The root process must have a valid network stream, but the streams
	 * of worker tasks are ignored.
<<<<<<< HEAD
	 *
	 * @param stream The stream to broadcast
	 * @param root The rank of the master process
	 * @return The buffer
	 */
	std::shared_ptr<std::istream> broadcastStream(
		std::shared_ptr<std::istream> stream, int root);
}
=======
	 */
	std::shared_ptr<std::istream> broadcastStream(
		std::shared_ptr<std::istream> stream, int root, MPI_Comm comm);
};
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520

} /* namespace xolotlCore */
#endif
