MPIEventLoop - A distributed parallel histogrammer and event loop for event based data
--
MPIEventLoop is a library for parallel analysis of event based data stored in CERN ROOT trees.
It is built with MPI and thus scalable across large computing clusters. This is an alternative to
PROOF which is ROOT's parallel framework. Unfortunately PROOF is not easily used with PBS/Torque for
submission based jobs at high performance computing centers as it requires system admins to install special
PROOF server software. MPIEventLoop is a simple library built with extreme-scale systems
in mind and thus natively supports distributed parallel ROOT-based analysis in the standard HPC ecosystem.


Author: __[Chris Sullivan]__ email: sullivan at nscl dot msu dot edu

[Chris Sullivan]: https://people.nscl.msu.edu/~sullivan/

License:
----------

See the LICENSE file for licensing and copyright information
