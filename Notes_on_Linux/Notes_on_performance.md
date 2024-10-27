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
 - https://github.com/iovisor/bcc
 - 20 Terminal Tools To Monitor Linux Resource Usage : https://youtu.be/UvADr3FVhZg


## USE: Utilization, Saturation and Errors

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

### Kprobes

 - https://docs.kernel.org/trace/kprobes.html
 - https://documentation.suse.com/sles/15-SP5/html/SLES-all/cha-tuning-kprobes.html
 - https://github.com/konstantin89/linux-kernel-kprobes-demo
 - https://github.com/konstantin89/linux-kernel-hook

### USDT  - Userspace Static Defined Tracing probes

USDT probes - Userspace Static Defined Tracing probes - act as markers for events of interest in user-space programs and libraries. As with kernel tracepoints, defining important events has huge value when trying to understand system behaviour. It is as if the developer who added these probes has marked the important sites on a map, and now we can use that map to help guide us to an understanding of what the system is doing by extracting the tracing information from those places.

 - https://leezhenghui.github.io/linux/2019/03/05/exploring-usdt-on-linux.html
 - https://www.brendangregg.com/blog/2015-07-03/hacking-linux-usdt-ftrace.html
 - https://lwn.net/Articles/753601/
 - https://blogs.oracle.com/linux/post/usdt-tracing-across-different-runtimes

USDT brings kernel tracepoints to user programs. <br>
Tracepoint information and arguments embedded in the binary and available to tracing tools. <br>
Probes (are literally) nops until enabled. 

## Perf

`perf` is a tool that can instrument CPU performance counters, tracepoints, kprobes, and uprobes (dynamic tracing). It is capable of lightweight profiling. It is also included in the Linux kernel, under tools/perf, and is frequently updated and enhanced.

 Perf is a tool for linux performance investigation. 

references: 
 - https://perf.wiki.kernel.org/index.php/Main_Page
 - perf tutorial: https://perf.wiki.kernel.org/index.php/Tutorial
 - perf examples: https://www.brendangregg.com/perf.html

### one liners

- recerence: https://www.brendangregg.com/perf.html

Record cpu samples with stacks to find CPU hot path
```
perf record -ag -F 97
```

Probe user-space memory allocation failures with stacks 
```
perf probe -x /lib64/lib.so.6 --add 'malloc%return res=$retval'
perf record -e probe:malloc --filter 'res==0' -g -p 188
```
   
collect disk I/O access statistics and pin-point heavy disk consumers
```
perf record -e block:block_rq_insert -a
```

trace syscalls to find missing or excessive file operations 
```
perf trace -e open
```

get number of events over a time interval 
```
perf stat -a -e sched:sched_switch -- sleep 5
```

monitor system performance (like top) on 1000s of metrics
```
perf top
perf top -e block:block_rq_insert
perf top -e page-faults
```

### Recording cpu stacks with perf

To find a CPU bottle neck, record stacks at timed intervals:

```
# system wide
perf record -ag -F 97

# specific process
perf record -p 188 -g -F 97

# specific workload
perf record -g -F -- ./myapp
```

flags:
```
-a: all CPUs
-g: capture all stacks
-p: specific process
--: run workload and capture
-F: frequency samples (Hz) - controlling the frequency you can control the overhead induced by perf.
-c: #of events in each sample - like -F but you requeste 1 sample, every N clock cycles.
```

Perf can be used to record the invocation of any kernel tracepoint, kprobe or uprobe
```
perf record -ag -F 97
perf record -ag -e sched:sched-switch
perf record -p 188 -e block:block_rq_insert
perf record -g -e net:net_dev_start_xmit
```

### top-down and down-top analisys

`perf report` opens an user interface, which is text based, but is better to navigate that the text traces. 

`perf report --stdio` will print a top-down analysis of the program.

`perf annotate --stdio` will report in down-top fashion the places in the code that uses the most cpu time. 

## flame graphs

- reference: https://www.brendangregg.com/flamegraphs.html

A perf report `perf report --stdio | wc -l` can be huge, and difficult to read. 


A flame graph is a visualization method (adjancency graph), very useful for stack traces, invented
by Brendan Gregg.

Turns  millions of stack traces into an interactive graph:
 - indentify CPU hotspots on the system/application.
 - Show stacks that perform heavy disk accesses.
 - Find threads that block for a long time and the stack where they do it. 

The flame graph generator: https://github.com/brendangregg/FlameGraph

To generate the flame graph, you get the perf output and pipe it to one of the flame-graph scripts
```
$ perf script | ~vagrant/src/FlameGraph/stackcollapse-perf.pl
```

then pipe that output into the flamegraph generator:

```
$ perf script | ~vagrant/src/FlameGraph/stackcollapse-perf.pl | vagrant/src/FlameGraph/flamegraph.pl 
```

and that produces the SVG file. 

### FPO and broken stacks

The FPO (frame pointer omission optimization) can be painfull when you are using any stack collection tool,
and lead to broken stacks

 - reference: https://www.brendangregg.com/blog/2024-03-17/the-return-of-the-frame-pointers.html

The compiler is using something known as FPO (Frame Pointer Omission), it is an optimization that doesn't 
link stack frames using the ERB/RBP register. 
 - typical wins are 1-5%
 - can make it hard for profiles and other tools to walk the stack without extra tools (e.g. libunwind or LBR)

For disabling FPO in C/C++: `-fpo-omit-frame-pointer` or artenatively, instruct perf to use `--callgraph=dwarf`, it uses
libunwind, and requieres the debugininfo for all stack frames. 

### Linux system events

#### introduction to Ftrace and Debugfs

Ftrace, originally was the "function tracer" a tool to looking at kernel function execution. But today Ftrace
has been expanded and now is a series of tool for tracing the system and agregating the information. 

 - reference: https://www.kernel.org/doc/html/latest/trace/ftrace.html

Ftrace is an internal tracer designed to help out developers and designers of systems to find what is going on inside the kernel. It can be used for debugging or analyzing latencies and performance issues that take place outside of user-space.

Although ftrace is typically considered the function tracer, it is really a framework of several assorted tracing utilities. There’s latency tracing to examine what occurs between interrupts disabled and enabled, as well as for preemption and from a time a task is woken to the task is actually scheduled in.

One of the most common uses of ftrace is the event tracing. Throughout the kernel is hundreds of static event points that can be enabled via the tracefs file system to see what is going on in certain parts of the kernel.

Ftrace has an interface through Debugfs, that can be mounted in `/sys/kernel/debug` by default, and then 
in `/sys/kernel/debug/tracing` you can use control files to start or stop strace, configure what event to trace,
setup kprobes and uprobes also. And read the output through the `trace` file or `trace_pipe` file. 

Ftrace major features:
 - tracing kernel functions (including call graph)
 - tracing kernel tracepoints, kprobes, uprobes
 - interrupt and wake up latency tracing
 - in-kernel histograms (hist-triggers)

 - reference: https://www.youtube.com/results?search_query=ftrace

There are some frontends like: 
 - https://github.com/rostedt/trace-cmd
 - https://github.com/brendangregg/perf-tools

#### recording and printing events oneliners


record all context switches:
```
trace-cmd record -e sched::sched::switch
```
record all write syscalls where the write was >1K:
```
trace-cmd record -e syscalls::sys_enter_open -f 'count > 1024' 
```
print the trace pipe contents:
```
trace-cmd report
```
print a trace summary:
```
trace-cmd hist
```
function tracing with stacks:
```
trace-cmd record -l tcp_sendmsg -p function --func-stack
```

filtering: find which events are in the trace: 
```
trace-cmd report --events
```

filtering: print only context switches from idle:
```
trace-cmd report -F 'sched_switch: prev_state == 1'
```

filtering: print only onctext switches from a specific process
```
trace-cmd report -F 'sched_switch: prev_pid = 188'
```


#### perf-tools

 - reference: https://github.com/brendangregg/perf-tools

A miscellaneous collection of in-development and unsupported performance analysis tools for Linux ftrace and perf_events (aka the "perf" command). Both ftrace and perf are core Linux tracing tools, included in the kernel source. Your system probably has ftrace already, and perf is often just a package add (see Prerequisites).

These tools are designed to be easy to install (fewest dependencies), provide advanced performance observability, and be simple to use: do one thing and do it well. This collection was created by Brendan Gregg (author of the DTraceToolkit).

Many of these tools employ workarounds so that functionality is possible on existing Linux kernels. Because of this, many tools have caveats (see man pages), and their implementation should be considered a placeholder until future kernel features, or new tracing subsystems, are added.

examples: 
 - opensnoop: trace_open() syscalls with filenames
 - funcslower: trace functions slower than threshold
 - iolatency: summarize I/O latency as a histogram
 - syscount: count system calls

there are also general purpouse tracers:
 - tpoint: enable and trace tracepoints
 - kprobe: place and trace kprobe
 - uprobe: place and trace uprobe









   


