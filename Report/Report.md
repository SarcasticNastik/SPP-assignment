# Assignment 1

<p style="text-align:right;"> Aman Rojjha 2019111018</p>

## Performance Tools and Analyzers
To benchmark and test the performance of code, several analyzers have been used and the optimizations applied.

### Perf
**Perf** is a performance analysis tool (also known as *perf_tools*)  which gives access to Performance Monitoring Unit of CPU. It can instrument CPU performance counters, tracepoints, kprobes and uprobes (for dynamic tracing). 

Example interface commands:
```bash
perf stat
perf record
perf report
perf annotate
perf top
perf bench
```

### Cache Grind


## Question 1 - Efficient Matrix Multiplication



## Question 2 - Floyd Warshall

1. Dynamic array allocation way slower than static (takes about `4x` time)
2. Bitwise `min` taking way more time than simple function min
3. Theoretically if statement and then assignment should take less time than a simple min function of both. (correct)



