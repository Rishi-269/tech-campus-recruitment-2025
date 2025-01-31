# Discussion

## Compilation

To compile the C++ program using `g++` and c++ 17, run the following command inside the `src` directory:

```bash
g++ -o extract_logs extract_logs.cpp
```

This will generate an executable file named `extract_logs`.

## Running the C++ Program

To execute the log extraction program, navigate to the `src` directory and run one of the following commands:

### If specifying a log file:

```bash
cd src
./extract_logs <filename> <YYYY-MM-DD>
```

Here, `<filename>` is the name of the log file inside the `src` folder.

### If using the default log file (`test_logs.log`):

```bash
cd src
./extract_logs <YYYY-MM-DD>
```

The program will assume the file is named `test_logs.log` and is located inside the `src` folder.

## Output Location

The extracted logs will be saved in the `output` folder. If this folder does not exist, it will be created automatically.

## Solution Overview

This solution utilizes **binary search** to find the lower bound of the given date in a sorted log file. Since the log entries are sorted by date, binary search allows us to quickly locate the first occurrence of the specified date.

If not sorted we can sort the file once if we need to query fromm that file again and again as it will be one time effort to sort the file

### Time Complexity

- **Binary Search:** `O(log n)`, where `n` is the total number of log entries.

## Handling Unsorted Logs

If the log file is **not sorted**, binary search cannot be used. Instead, a **linear search** must be performed, which has a time complexity of `O(n)`.

### Optimization with Multithreading

For large unsorted log files, **multithreading** can be used to distribute the workload across multiple CPU cores. However, the efficiency of this approach depends on the hardware capabilities and the structure of the log file.

