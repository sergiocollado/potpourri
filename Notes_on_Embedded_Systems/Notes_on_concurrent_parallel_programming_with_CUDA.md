# Notes on concurrent/parallel programming

related reference: 
 - [Stanford CS149 I Parallel Computing I 2023](https://www.youtube.com/watch?v=V1tINV2-9p4&list=PLoROMvodv4rMp7MTFr4hQsDEcX7Bx6Odp)
 - https://learn.nvidia.com/en-us/training/resources
 - https://learn.nvidia.com/en-us/training/self-paced-courses#cid=dli01_nv-int-bnr_en-us
 - https://nvdam.widen.net/s/brxsxxtskb/dli-learning-journey-2009000-r5-web/?nvid=nv-int-bnr-827289#cid=dli01_nv-int-bnr_en-us
 - https://learn.nvidia.com/en-us/training/self-paced-courses#cid=dli01_nv-int-bnr_en-us
 - https://developer.nvidia.com/cuda-zone
 - https://agray3.github.io/files/learnCUDApractical.pdf
 - https://www.olcf.ornl.gov/cuda-training-series/
 - https://cuda-tutorial.readthedocs.io/en/latest/
 - https://leimao.github.io/tags/CUDA/



### Paralell programming in C++

There are 4 elements needed: 

References:
- https://cplusplus.com/reference/multithreading/
- https://www.cs.cmu.edu/afs/cs/academic/class/15210-f17/www/pasl.html

```c++
std::thread /join/detach
std::mutex  /lock/try_lock/unlock
std::atomic /atomic_thread_fence/memory_order_acquire/memory_order_release
std::future /std::promise/std::async(wait/get)
```

## Retrieve system GPU info

In linux: `lspci | grep -i --color 'vga|/3d|/2d'`

## nvcc


```
$ nvcc -h

Usage  : nvcc [options] <inputfile>

Options for specifying the compilation phase
============================================
More exactly, this option specifies up to which stage the input files must be compiled,
according to the following compilation trajectories for different input file types:
        .c/.cc/.cpp/.cxx : preprocess, compile, link
        .o               : link
        .i/.ii           : compile, link
        .cu              : preprocess, cuda frontend, PTX assemble,
                           merge with host C code, compile, link
        .gpu             : cicc compile into cubin
        .ptx             : PTX assemble into cubin.

--cuda                                          (-cuda)                         
        Compile all .cu input files to .cu.cpp.ii output.

--cubin                                         (-cubin)                        
        Compile all .cu/.gpu/.ptx input files to device-only .cubin files.  This
        step discards the host code for each .cu input file.

--fatbin                                        (-fatbin)                       
        Compile all .cu/.gpu/.ptx/.cubin input files to device-only .fatbin files.
        This step discards the host code for each .cu input file.

--ptx                                           (-ptx)                          
        Compile all .cu input files to device-only .ptx files.  This step discards
        the host code for each of these input file.

--preprocess                                    (-E)                            
        Preprocess all .c/.cc/.cpp/.cxx/.cu input files.

--generate-dependencies                         (-M)                            
        Generate a dependency file that can be included in a make file for the .c/.cc/.cpp/.cxx/.cu
        input file. If -MF is specified, multiple source files are not supported,
        and the output is written to the specified file, otherwise it is written
        to stdout.

--generate-nonsystem-dependencies               (-MM)                           
        Same as --generate-dependencies but skip header files found in system directories
        (Linux only).

--generate-dependencies-with-compile            (-MD)                           
        Generate a dependency file and compile the input file. The dependency file
        can be included in a make file for the .c/.cc/.cpp/.cxx/.cu input file. 
        This option cannot be specified together with -E. 
        The dependency file name is computed as follows:
        - If -MF is specified, then the specified file is used as the dependency
        file name 
        - If -o is specified, the dependency file name is computed from the specified
        file name by replacing the suffix with '.d'.
        - Otherwise, the dependency file name is computed by replacing the input
        file names's suffix with '.d'
        If the dependency file name is computed based on either -MF or -o, then multiple
        input files are not supported.

--generate-nonsystem-dependencies-with-compile  (-MMD)                          
        Same as --generate-dependencies-with-compile, but skip header files found
        in system directories (Linux only).

--dependency-output                             (-MF)                           
        Specify the output file for the dependency file generated with -M/-MM/-MD/-MMD.
        

--generate-dependency-targets                   (-MP)                           
        Add an empty target for each dependency.

--compile                                       (-c)                            
        Compile each .c/.cc/.cpp/.cxx/.cu input file into an object file.

--device-c                                      (-dc)                           
        Compile each .c/.cc/.cpp/.cxx/.cu input file into an object file that contains
        relocatable device code.  It is equivalent to '--relocatable-device-code=true
        --compile'.

--device-w                                      (-dw)                           
        Compile each .c/.cc/.cpp/.cxx/.cu input file into an object file that contains
        executable device code.  It is equivalent to '--relocatable-device-code=false
        --compile'.

--device-link                                   (-dlink)                        
        Link object files with relocatable device code and .ptx/.cubin/.fatbin files
        into an object file with executable device code, which can be passed to the
        host linker.

--link                                          (-link)                         
        This option specifies the default behavior: compile and link all inputs.

--lib                                           (-lib)                          
        Compile all inputs into object files (if necessary) and add the results to
        the specified output library file.

--run                                           (-run)                          
        This option compiles and links all inputs into an executable, and executes
        it.  Or, when the input is a single executable, it is executed without any
        compilation or linking. This step is intended for developers who do not want
        to be bothered with setting the necessary environment variables; these are
        set temporarily by nvcc).


File and path specifications.
=============================

--output-file <file>                            (-o)                            
        Specify name and location of the output file.  Only a single input file is
        allowed when this option is present in nvcc non-linking/archiving mode.

--pre-include <file>,...                        (-include)                      
        Specify header files that must be preincluded during preprocessing.

--objdir-as-tempdir                             (-objtemp)                      
        Create intermediate files in the same directory as the object file instead
        of in the temporary directory. This option will take effect only if -c, -dc
        or -dw is also used.

--library <library>,...                         (-l)                            
        Specify libraries to be used in the linking stage without the library file
        extension.  The libraries are searched for on the library search paths that
        have been specified using option '--library-path'.

--define-macro <def>,...                        (-D)                            
        Specify macro definitions to define for use during preprocessing or compilation.

--undefine-macro <def>,...                      (-U)                            
        Undefine macro definitions during preprocessing or compilation.

--include-path <path>,...                       (-I)                            
        Specify include search paths.

--system-include <path>,...                     (-isystem)                      
        Specify system include search paths.

--library-path <path>,...                       (-L)                            
        Specify library search paths.

--output-directory <directory>                  (-odir)                         
        Specify the directory of the output file.  This option is intended for letting
        the dependency generation step (see '--generate-dependencies') generate a
        rule that defines the target object file in the proper directory.

--compiler-bindir <path>                        (-ccbin)                        
        Specify the directory in which the host compiler executable resides.  The
        host compiler executable name can be also specified to ensure that the correct
        host compiler is selected.  In addition, driver prefix options ('--input-drive-prefix',
        '--dependency-drive-prefix', or '--drive-prefix') may need to be specified,
        if nvcc is executed in a Cygwin shell or a MinGW shell on Windows.

--allow-unsupported-compiler                    (-allow-unsupported-compiler)   
        Disable nvcc check for supported host compiler versions. Using an unsupported
        host compiler may cause compilation failure or incorrect run time execution.
        Use at your own risk. This option has no effect on MacOS.

--archiver-binary <path>                        (-arbin)                        
        Specify the path of the executable for the archiving tool used to createstatic
        libraries with '--lib'. If unspecified, a platform-specific defaultis used.

--cudart {none|shared|static}                   (-cudart)                       
        Specify the type of CUDA runtime library to be used: no CUDA runtime library,
        shared/dynamic CUDA runtime library, or static CUDA runtime library.
        Allowed values for this option:  'none','shared','static'.
        Default value:  'static'.

--cudadevrt {none|static}                       (-cudadevrt)                    
        Specify the type of CUDA device runtime library to be used: no CUDA device
        runtime library, or static CUDA device runtime library.
        Allowed values for this option:  'none','static'.
        Default value:  'static'.

--libdevice-directory <directory>               (-ldir)                         
        Specify the directory that contains the libdevice library files when option
        '--dont-use-profile' is used.  Libdevice library files are located in the
        'nvvm/libdevice' directory in the CUDA toolkit.

--target-directory <string>                     (-target-dir)                   
        Specify the subfolder name in the targets directory where the default include
        and library paths are located. 

--use-local-env                                 --use-local-env                 
        Specify whether the environment is already set up for the host compiler.


Options for specifying behavior of compiler/linker.
===================================================

--profile                                       (-pg)                           
        Instrument generated code/executable for use by gprof (Linux only).

--debug                                         (-g)                            
        Generate debug information for host code.

--device-debug                                  (-G)                            
        Generate debug information for device code. Turns off all optimizations.
        Don't use for profiling; use -lineinfo instead.

--generate-line-info                            (-lineinfo)                     
        Generate line-number information for device code.

--optimization-info <kind>,...                  (-opt-info)                     
        Provide optimization reports for the specified kind of optimization. The
        following tags are supported:
                inline: Emit remarks related to function inlining. Inlining passmay
        be invoked multiple times by the compiler and a function notinlined in an
        earlier pass may be inlined in a subsequent pass.
        Allowed values for this option:  'inline'.

--optimize <level>                              (-O)                            
        Specify optimization level for host code.

--dlink-time-opt                                (-dlto)                         
        Perform link-time optimization of device code. Link-time optimization must
        be specified at both compile and link time; at compile time it stores high-level
        intermediate code, then at link time it links together and optimizes the
        intermediate code.If that intermediate is not found at link time then nothing
        happens. Intermediate code is also stored at compile time with the --gpu-code='lto_NN'
        target. The options -dlto -arch=sm_NN will add a lto_NN target; if you want
        to only add a lto_NN target and not the compute_NN that -arch=sm_NN usually
        generates, use -arch=lto_NN.

--lto                                           (-lto)                          
        Alias for -dlto.

--ftemplate-backtrace-limit <limit>             (-ftemplate-backtrace-limit)    
        Set the maximum number of template instantiation notes for a single warning
        or error to <limit>. A value of 0 is allowed, and indicates that no limit
        should be enforced. This value is also passed to the host compiler if it
        provides an equivalent flag.

--ftemplate-depth <limit>                       (-ftemplate-depth)              
        Set the maximum instantiation depth for template classes to <limit>. This
        value is also passed to the host compiler if it provides an equivalent flag.

--no-exceptions                                 (-noeh)                         
        Disable exception handling for host code.

--shared                                        (-shared)                       
        Generate a shared library during linking.  Use option '--linker-options'
        when other linker options are required for more control.

--x {c|c++|cu}                                  (-x)                            
        Explicitly specify the language for the input files, rather than letting
        the compiler choose a default based on the file name suffix.
        Allowed values for this option:  'c','c++','cu'.

--std {c++03|c++11|c++14|c++17}                 (-std)                          
        Select a particular C++ dialect.  Note that this flag also turns on the corresponding
        dialect flag for the host compiler.
        Allowed values for this option:  'c++03','c++11','c++14','c++17'.

--no-host-device-initializer-list               (-nohdinitlist)                 
        Do not implicitly consider member functions of std::initializer_list as __host__
        __device__ functions.

--no-host-device-move-forward                   (-nohdmoveforward)              
        Do not implicitly consider std::move and std::forward as __host__ __device__
        function templates.

--expt-relaxed-constexpr                        (-expt-relaxed-constexpr)       
        Experimental flag: Allow host code to invoke __device__ constexpr functions,
        and device code to invoke __host__ constexpr functions.Note that the behavior
        of this flag may change in future compiler releases.

--extended-lambda                               (-extended-lambda)              
        Allow __host__, __device__ annotations in lambda declaration. 

--expt-extended-lambda                          (-expt-extended-lambda)         
        Alias for -extended-lambda.

--machine {32|64}                               (-m)                            
        Specify 32 vs 64 bit architecture.
        Allowed values for this option:  32,64.
        Default value:  64.

--m32                                           (-m32)                          
        Equivalent to --machine=32.

--m64                                           (-m64)                          
        Equivalent to --machine=64.


Options for passing specific phase options
==========================================
These allow for passing options directly to the intended compilation phase.  Using
these, users have the ability to pass options to the lower level compilation tools,
without the need for nvcc to know about each and every such option.

--compiler-options <options>,...                (-Xcompiler)                    
        Specify options directly to the compiler/preprocessor.

--linker-options <options>,...                  (-Xlinker)                      
        Specify options directly to the host linker.

--archive-options <options>,...                 (-Xarchive)                     
        Specify options directly to library manager.

--ptxas-options <options>,...                   (-Xptxas)                       
        Specify options directly to ptxas, the PTX optimizing assembler.

--nvlink-options <options>,...                  (-Xnvlink)                      
        Specify options directly to nvlink.


Miscellaneous options for guiding the compiler driver.
======================================================

--forward-unknown-to-host-compiler              (-forward-unknown-to-host-compiler)
        Forward unknown options to the host compiler. An 'unknown option' is a command
        line argument that starts with '-' followed by another character, and is
        not a recognized nvcc flag or an argument for a recognized nvcc flag.
        Note: If the unknown option is followed by a separate command line argument,
        the argument will not be forwarded, unless it begins with the '-' character.
        E.g.
        'nvcc -forward-unknown-to-host-compiler -foo=bar a.cu' will forward '-foo=bar'
        to host compiler.
        'nvcc -forward-unknown-to-host-compiler -foo bar a.cu' will report an error
        for 'bar' argument.
        'nvcc -forward-unknown-to-host-compiler -foo -bar a.cu' will forward '-foo'
        and '-bar' to host compiler.

--forward-unknown-to-host-linker                (-forward-unknown-to-host-linker)
        Forward unknown options to the host linker. An 'unknown option' is a command
        line argument that starts with '-' followed by another character, and is
        not a recognized nvcc flag or an argument for a recognized nvcc flag.
        Note: If the unknown option is followed by a separate command line argument,
        the argument will not be forwarded, unless it begins with the '-' character.
        E.g.
        'nvcc -forward-unknown-to-host-linker -foo=bar a.cu' will forward '-foo=bar'
        to host linker.
        'nvcc -forward-unknown-to-host-linker -foo bar a.cu' will report an error
        for 'bar' argument.
        'nvcc -forward-unknown-to-host-linker -foo -bar a.cu' will forward '-foo'
        and '-bar' to host linker.

--forward-unknown-opts                          (-forward-unknown-opts)         
        Implies the combination of options: -forward-unknown-to-host-linker and -forward-unknown-to-host-compiler.
        E.g.
        'nvcc -forward-unknown-opts -foo=bar a.cu' will forward '-foo=bar' to the
        host linker and compiler.
        'nvcc -forward-unknown-opts -foo bar a.cu' will report an error for 'bar'
        argument.
        'nvcc -forward-unknown-opts -foo -bar a.cu' will forward '-foo' and '-bar'
        to the host linker and compiler.

--dont-use-profile                              (-noprof)                       
        Nvcc uses the nvcc.profiles file for compilation.  When specifying this option,
        the profile file is not used.

--dryrun                                        (-dryrun)                       
        Do not execute the compilation commands generated by nvcc.  Instead, list
        them.

--verbose                                       (-v)                            
        List the compilation commands generated by this compiler driver, but do not
        suppress their execution.

--threads <number>                              (-t)                            
        Specify the maximum number of threads to be created in parallel when compiling
        for multiple architectures. If <number> is 1 or if compiling for one architecture,
        this option is ignored. If <number> is 0, the number of threads will be the
        number of CPUs on the machine.

--keep                                          (-keep)                         
        Keep all intermediate files that are generated during internal compilation
        steps.

--keep-dir <directory>                          (-keep-dir)                     
        Keep all intermediate files that are generated during internal compilation
        steps in this directory.

--save-temps                                    (-save-temps)                   
        This option is an alias of '--keep'.

--clean-targets                                 (-clean)                        
        This option reverses the behavior of nvcc.  When specified, none of the compilation
        phases will be executed.  Instead, all of the non-temporary files that nvcc
        would otherwise create will be deleted.

--time <file name>                              (-time)                         
        Generate a comma separated value table with the time taken by each compilation
        phase, and append it at the end of the file given as the option argument.
        If the file is empty, the column headings are generated in the first row
        of the table. If the file name is '-', the timing data is generated in stdout.

--run-args <arguments>,...                      (-run-args)                     
        Used in combination with option --run to specify command line arguments for
        the executable.

--input-drive-prefix <prefix>                   (-idp)                          
        On Windows, all command line arguments that refer to file names must be converted
        to the Windows native format before they are passed to pure Windows executables.
        This option specifies how the current development environment represents
        absolute paths.  Use '/cygwin/' as <prefix> for Cygwin build environments,
        and '/' as <prefix> for MinGW.

--dependency-drive-prefix <prefix>              (-ddp)                          
        On Windows, when generating dependency files (see --generate-dependencies),
        all file names must be converted appropriately for the instance of 'make'
        that is used.  Some instances of 'make' have trouble with the colon in absolute
        paths in the native Windows format, which depends on the environment in which
        the 'make' instance has been compiled.  Use '/cygwin/' as <prefix> for a
        Cygwin make, and '/' as <prefix> for MinGW.  Or leave these file names in
        the native Windows format by specifying nothing.

--drive-prefix <prefix>                         (-dp)                           
        Specifies <prefix> as both --input-drive-prefix and --dependency-drive-prefix.

--dependency-target-name <target>               (-MT)                           
        Specify the target name of the generated rule when generating a dependency
        file (see '--generate-dependencies').

--no-align-double                               --no-align-double               
        Specifies that '-malign-double' should not be passed as a compiler argument
        on 32-bit platforms.  WARNING: this makes the ABI incompatible with the cuda's
        kernel ABI for certain 64-bit types.

--no-device-link                                (-nodlink)                      
        Skip the device link step when linking object files.


Options for steering GPU code generation.
=========================================

--gpu-architecture <arch>                       (-arch)                         
        Specify the name of the class of NVIDIA 'virtual' GPU architecture for which
        the CUDA input files must be compiled.
        With the exception as described for the shorthand below, the architecture
        specified with this option must be a 'virtual' architecture (such as compute_50).
        Normally, this option alone does not trigger assembly of the generated PTX
        for a 'real' architecture (that is the role of nvcc option '--gpu-code',
        see below); rather, its purpose is to control preprocessing and compilation
        of the input to PTX.
        For convenience, in case of simple nvcc compilations, the following shorthand
        is supported.  If no value for option '--gpu-code' is specified, then the
        value of this option defaults to the value of '--gpu-architecture'.  In this
        situation, as only exception to the description above, the value specified
        for '--gpu-architecture' may be a 'real' architecture (such as a sm_50),
        in which case nvcc uses the specified 'real' architecture and its closest
        'virtual' architecture as effective architecture values.  For example, 'nvcc
        --gpu-architecture=sm_50' is equivalent to 'nvcc --gpu-architecture=compute_50
        --gpu-code=sm_50,compute_50'.
        Note: the values compute_30, compute_32, compute_35, compute_37, compute_50,
        sm_30, sm_32, sm_35, sm_37 and sm_50 are deprecated and may be removed in
        a future release.
        Allowed values for this option:  'compute_35','compute_37','compute_50',
        'compute_52','compute_53','compute_60','compute_61','compute_62','compute_70',
        'compute_72','compute_75','compute_80','compute_86','lto_35','lto_37','lto_50',
        'lto_52','lto_53','lto_60','lto_61','lto_62','lto_70','lto_72','lto_75',
        'lto_80','lto_86','sm_35','sm_37','sm_50','sm_52','sm_53','sm_60','sm_61',
        'sm_62','sm_70','sm_72','sm_75','sm_80','sm_86'.

--gpu-code <code>,...                           (-code)                         
        Specify the name of the NVIDIA GPU to assemble and optimize PTX for.
        nvcc embeds a compiled code image in the resulting executable for each specified
        <code> architecture, which is a true binary load image for each 'real' architecture
        (such as sm_50), and PTX code for the 'virtual' architecture (such as compute_50).
        During runtime, such embedded PTX code is dynamically compiled by the CUDA
        runtime system if no binary load image is found for the 'current' GPU.
        Architectures specified for options '--gpu-architecture' and '--gpu-code'
        may be 'virtual' as well as 'real', but the <code> architectures must be
        compatible with the <arch> architecture.  When the '--gpu-code' option is
        used, the value for the '--gpu-architecture' option must be a 'virtual' PTX
        architecture.
        For instance, '--gpu-architecture=compute_60' is not compatible with '--gpu-code=sm_52',
        because the earlier compilation stages will assume the availability of 'compute_60'
        features that are not present on 'sm_52'.
        Note: the values compute_30, compute_32, compute_35, compute_37, compute_50,
        sm_30, sm_32, sm_35, sm_37 and sm_50 are deprecated and may be removed in
        a future release.
        Allowed values for this option:  'compute_35','compute_37','compute_50',
        'compute_52','compute_53','compute_60','compute_61','compute_62','compute_70',
        'compute_72','compute_75','compute_80','compute_86','lto_35','lto_37','lto_50',
        'lto_52','lto_53','lto_60','lto_61','lto_62','lto_70','lto_72','lto_75',
        'lto_80','lto_86','sm_35','sm_37','sm_50','sm_52','sm_53','sm_60','sm_61',
        'sm_62','sm_70','sm_72','sm_75','sm_80','sm_86'.

--generate-code <specification>,...             (-gencode)                      
        This option provides a generalization of the '--gpu-architecture=<arch> --gpu-code=<code>,
        ...' option combination for specifying nvcc behavior with respect to code
        generation.  Where use of the previous options generates code for different
        'real' architectures with the PTX for the same 'virtual' architecture, option
        '--generate-code' allows multiple PTX generations for different 'virtual'
        architectures.  In fact, '--gpu-architecture=<arch> --gpu-code=<code>,
        ...' is equivalent to '--generate-code arch=<arch>,code=<code>,...'.
        '--generate-code' options may be repeated for different virtual architectures.
        Allowed keywords for this option:  'arch','code'.

--relocatable-device-code {true|false}          (-rdc)                          
        Enable (disable) the generation of relocatable device code.  If disabled,
        executable device code is generated.  Relocatable device code must be linked
        before it can be executed.
        Default value:  false.

--entries entry,...                             (-e)                            
        Specify the global entry functions for which code must be generated.  By
        default, code will be generated for all entry functions.

--maxrregcount <amount>                         (-maxrregcount)                 
        Specify the maximum amount of registers that GPU functions can use.
        Until a function-specific limit, a higher value will generally increase the
        performance of individual GPU threads that execute this function.  However,
        because thread registers are allocated from a global register pool on each
        GPU, a higher value of this option will also reduce the maximum thread block
        size, thereby reducing the amount of thread parallelism.  Hence, a good maxrregcount
        value is the result of a trade-off.
        If this option is not specified, then no maximum is assumed.
        Value less than the minimum registers required by ABI will be bumped up by
        the compiler to ABI minimum limit.
        User program may not be able to make use of all registers as some registers
        are reserved by compiler.

--use_fast_math                                 (-use_fast_math)                
        Make use of fast math library.  '--use_fast_math' implies '--ftz=true --prec-div=false
        --prec-sqrt=false --fmad=true'.

--ftz {true|false}                              (-ftz)                          
        This option controls single-precision denormals support. '--ftz=true' flushes
        denormal values to zero and '--ftz=false' preserves denormal values. '--use_fast_math'
        implies '--ftz=true'.
        Default value:  false.

--prec-div {true|false}                         (-prec-div)                     
        This option controls single-precision floating-point division and reciprocals.
        '--prec-div=true' enables the IEEE round-to-nearest mode and '--prec-div=false'
        enables the fast approximation mode.  '--use_fast_math' implies '--prec-div=false'.
        Default value:  true.

--prec-sqrt {true|false}                        (-prec-sqrt)                    
        This option controls single-precision floating-point squre root.  '--prec-sqrt=true'
        enables the IEEE round-to-nearest mode and '--prec-sqrt=false' enables the
        fast approximation mode.  '--use_fast_math' implies '--prec-sqrt=false'.
        Default value:  true.

--fmad {true|false}                             (-fmad)                         
        This option enables (disables) the contraction of floating-point multiplies
        and adds/subtracts into floating-point multiply-add operations (FMAD, FFMA,
        or DFMA).  '--use_fast_math' implies '--fmad=true'.
        Default value:  true.

--extra-device-vectorization                    (-extra-device-vectorization)   
        This option enables more aggressive device code vectorization.


Options for steering cuda compilation.
======================================

--default-stream {legacy|null|per-thread}       (-default-stream)               
        Specify the stream that CUDA commands from the compiled program will be sent
        to by default.
                
        legacy
                The CUDA legacy stream (per context, implicitly synchronizes with
                other streams).
                
        per-thread
                A normal CUDA stream (per thread, does not implicitly
                synchronize with other streams).
                
        'null' is a deprecated alias for 'legacy'.
                
        Allowed values for this option:  'legacy','null','per-thread'.
        Default value:  'legacy'.


Generic tool options.
=====================

--disable-warnings                              (-w)                            
        Inhibit all warning messages.

--keep-device-functions                         (-keep-device-functions)        
        In whole program compilation mode, preserve user defined external linkage
        __device__ function definitions up to PTX.

--source-in-ptx                                 (-src-in-ptx)                   
        Interleave source in PTX. May only be used in conjunction with --device-debug
        or --generate-line-info.

--restrict                                      (-restrict)                     
        Programmer assertion that all kernel pointer parameters are restrict pointers.

--Wreorder                                      (-Wreorder)                     
        Generate warnings when member initializers are reordered.

--Wdefault-stream-launch                        (-Wdefault-stream-launch)       
        Generate warning when an explicit stream argument is not provided in the
        <<<...>>> kernel launch syntax.

--Wext-lambda-captures-this                     (-Wext-lambda-captures-this)    
        Generate warning when an extended lambda implicitly captures 'this'.

--Wno-deprecated-declarations                   (-Wno-deprecated-declarations)  
        Suppress warning on use of deprecated entity.

--Wno-deprecated-gpu-targets                    (-Wno-deprecated-gpu-targets)   
        Suppress warnings about deprecated GPU target architectures.

--Werror <kind>,...                             (-Werror)                       
        Make warnings of the specified kinds into errors.  The following is the list
        of warning kinds accepted by this option:
                
        cross-execution-space-call
                Be more strict about unsupported cross execution space calls.
                The compiler will generate an error instead of a warning for a
                call from a __host__ __device__ to a __host__ function.
        reorder
                Generate errors when member initializers are reordered.
        deprecated-declarations
                Generate error on use of a deprecated entity.
        default-stream-launch
                Generate error when an explicit stream argument is not provided in
        the <<<...>>> kernel launch syntax.
        ext-lambda-captures-this
                Generate error when an extended lambda implicitly captures 'this'
        Allowed values for this option:  'all-warnings','cross-execution-space-call',
        'default-stream-launch','deprecated-declarations','ext-lambda-captures-this',
        'reorder'.

--resource-usage                                (-res-usage)                    
        Show resource usage such as registers and memory of the GPU code.
        This option implies '--nvlink-options --verbose' when '--relocatable-device-code=true'
        is set.  Otherwise, it implies '--ptxas-options --verbose'.

--extensible-whole-program                      (-ewp)                          
        Do extensible whole program compilation of device code.

--no-compress                                   (-no-compress)                  
        Do not compress device code in fatbinary.

--qpp-config                                    (-qpp-config)                   
        Specify the configuration ([[compiler/]version,][target]) for the q++ host
        compiler. The argument will be forwarded to the q++ compiler with its -V
        flag.

--compile-as-tools-patch                        (-astoolspatch)                 
        Compile patch code for CUDA tools. Implies --keep-device-functions.

--list-gpu-code                                 (-code-ls)                      
        List the gpu architectures (sm_XX) supported by the compiler and exit. If
        both --list-gpu-code and --list-gpu-arch are set, the list is displayed using
        the same format as the --generate-code value.

--list-gpu-arch                                 (-arch-ls)                      
        List the virtual device architectures (compute_XX) supported by the compiler
        and exit. If both --list-gpu-code and --list-gpu-arch are set, the list is
        displayed using the same format as the --generate-code value.

--version-ident {true|false}                    (-dQ)                           
        This option enables (disables) the generation of compiler tool version identity
        in device code object.
        Default value:  false.

--display-error-number                          (-err-no)                       
        This option displays a diagnostic number for any message generated by the
        CUDA frontend compiler (note: not the host compiler).

--diag-error <error-number>,...                 (-diag-error)                   
        Emit error for specified diagnostic message(s) generated by the CUDA frontend
        compiler (note: does not affect diagnostics generated by the host compiler/preprocessor).

--diag-suppress <error-number>,...              (-diag-suppress)                
        Suppress specified diagnostic message(s) generated by the CUDA frontend compiler
        (note: does not affect diagnostics generated by the host compiler/preprocessor).

--diag-warn <error-number>,...                  (-diag-warn)                    
        Emit warning for specified diagnostic message(s) generated by the CUDA frontend
        compiler (note: does not affect diagnostics generated by the host compiler/preprocessor).

--help                                          (-h)                            
        Print this help information on this tool.

--version                                       (-V)                            
        Print version information on this tool.

--options-file <file>,...                       (-optf)                         
        Include command line options from specified file.
```

## Nvidia programming resources

 - https://developer.nvidia.com/

