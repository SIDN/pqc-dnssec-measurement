# Custom Performance Test

This code accompanies a research paper currently under review.
In our paper, we discuss to what extend we can apply post-quantum signing algorithms, currently assessed in the NIST competition, to DNSSEC.

The code in this repository runs a very basic speed test for four quantum-safe algorithms. 

- Falcon 512
- RainbowIa
- RedGeMSS128
- LUOV-7-57-197

The results from this tests are used to give an intuition if these algorithms are fast enough for DNSSEC deployments. See our paper for details on the criteria. The results in the paper are based on measurements on a single core Intel Xeon Silver 4110 CPU (2.10GHz), 64GB RAM, running Ubuntu 18.04.3 LTS.

Each subdirectory contains the measurement code and an additional file, describing how to set it up.
Each test require the optimized implementations of the algorithms and their dependencies, as provided on the [NIST homepage](https://csrc.nist.gov/projects/post-quantum-cryptography/round-2-submissions).

