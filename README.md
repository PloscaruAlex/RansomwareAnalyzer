# RansomwareAnalyzer

This project implements a custom tool to be used together with a DBI framework, Intel Pin, to observe the runtime behavior of ransomware samples.

The pintool, RansomwareAnalyzer.dll, generates logs containing Windows API call sequences for different operations that the ransomware sample may perform, like file operations, registry modifications, network and crypto activity and the process tree of the samples together with threads information for each process, as well as the DLLs used by the sample. 

The RansomwareAnalyzer pintool consists of a main file that orchestrates all the modules, together with six modules that instrument different operations performed by the sample, four of them instrumenting different Windows APIs, one monitoring the ILS of the program, and the last one tracking the process tree created by the sample. A logger component timestamps and stores the API calls in log files separated by module. The structural outline of the developed RansomwareAnalyzer custom pintool can be observed in the diagram.

![alt text](https://github.com/PloscaruAlex/RansomwareAnalyzer/blob/main/RansomwareAnalyzerCode.png)

The pintool was tested and developed for Intel Pin 4.2, along with Microsoft Visual Studio 2026.


**This project is the implementation used for my thesis:**  
*"Ransomware family classification using Machine Learning algorithms based on DBI analysis"* by Alexandru Ploscaru, [UNIVERSITY POLITEHNICA OF BUCHAREST], [2026]

The code is licensed under the MIT License (see [LICENSE](LICENSE) file)

