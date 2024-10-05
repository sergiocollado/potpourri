# NOTES ON PROGRAMS PERFORMACE & PROFILING

References:
 - https://www.brendangregg.com/blog/2020-07-15/systems-performance-2nd-edition.html
 - http://euccas.github.io/blog/20170827/cpu-profiling-tools-on-linux.html
 - https://johnnysswlab.com/
 - http://www.pixelbeat.org/programming/profiling/
 - https://www.cs.princeton.edu/picasso/mats/mats_S07/Lucifredi_Lecture_Feb07.pdf
 - https://docs.kernel.org/admin-guide/workload-tracing.html
 - https://man7.org/linux/man-pages/man1/top.1.html
 - https://www.man7.org/linux/man-pages/man1/htop.1.html
 - https://blogs.oracle.com/linux/post/usdt-tracing-across-different-runtimes
 - https://leezhenghui.github.io/linux/2019/03/05/exploring-usdt-on-linux.html


## USE: Utilization, Saturation and errors

references:
 - https://www.brendangregg.com/usemethod.html
 - https://www.brendangregg.com/USEmethod/use-linux.html

In the previous link there is a list of simple tools to measure the utilization, saturiation and errors of the different systems. 

### Different types of performance tools
 
classiffication by tools by amount of information: 
 - counting tools: count events, like: `top` or `ifconfig`
 - latency tools: how long? `iolatency`, `fileslower`, `dbslower`.
 - stack aggreagators: where this comes from in my code? like: `perf`, `stackcount`
 - tracers: report events as those happens: logs, `perf`, `trace`

classification by data processing: 
 - Real time:
     - output as events arrive
     - no long-term aggregation
     - lower overhead
 - Later analysis
     - aggregated or raw data written to a file
     - post-processing required
     - can go back and investigate
  
 ### Tracing vs sampling 

 - Sampling: sometimes some events happen to often to count them, so the strategy is to get an snapshot or a call stack every N occurrences of an interesting event. For most events implemented in the PMU (Processor Monitoring Unit) using overflow counters and interrupts.
 - Tracing: is for lower frequency events, and it works by getting a message or a call stack at every occurrence of an interesting event.
    
When you use tracing you get every occurrence of an event, when you use sampling you only get every N event, but with more sampling you get a better probability acurracy to the full picture. 

### Some tracing and sampling tools:

 - perf
 - ftrace
 - SystemTap
 - SysDig
 - LTTng
 - ply/BPF
 - bcc/BPF
 - C/BPF
 - custom.ko

### Kernel tracepoints

- reference: https://docs.kernel.org/trace/tracepoints.html

Kernel tracepoints are one of the most importat resources for assessing the kernel performance. 
These are embedded on the kernel at compile time.

What it means is that there are some functions in the kernel code that tipically don't do 
anything but can be instrumented in such a way that if they are enabled the trace points, 
they report real-time information from the system. 

One notable area where there are no trace points is in the TCP IP subsystem, other tools
have to be used to retrieve information from that subsystem. 

scenarios for using tracepoints: 
 - summary of block device utilization and latency
 - blocked process wait times and timeline
 - kernel memory allocation patterns
 - hardware interrupt handling and distribution
 - application workload characterization through syscalls


   


